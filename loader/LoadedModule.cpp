#include <Windows.h>
#include <iostream>

#include "Exceptions.hpp"
#include "Statuses.hpp"
#include "LoadedModule.hpp"


LoadedModule::LoadedModule(
	PBYTE pbBuffer,
	size_t buffer_size,
	PIMAGE_DOS_HEADER ptDosHeader,
	PIMAGE_NT_HEADERS ptNTHeader)
{
	std::wcout << L"Constructor" << std::endl;

	CopyMemory(&m_tDosHeader, ptDosHeader, sizeof(*ptDosHeader));
	// Validate we have the dos magic in the DOS header copy
	if (IMAGE_DOS_SIGNATURE != m_tDosHeader.e_magic)
	{
		throw LoaderException(L"Could not find DOS image magic", LoaderStatus::LOADERSTATUS_DOS_MAGIC_NOT_FOUND);
	}

	CopyMemory(&m_tNtHeader, ptNTHeader, sizeof(*ptNTHeader));

	load(pbBuffer, buffer_size);
}

LoadedModule::~LoadedModule()
{
	std::wcout << L"Destructor" << std::endl;
}

void LoadedModule::print_me() const
{
	std::wcout << L"DOS magic is: 0x" << std::hex << m_tDosHeader.e_magic << std::endl;
}

void LoadedModule::load(PBYTE pbBuffer, size_t buffer_size)
{
	const uint32_t ALLOCATION_TYPE = MEM_RESERVE;
	const uint32_t PAGE_PROTECTION = PAGE_READWRITE;

	// Virtual allocate space for the executable buffer
	auto const image_address = VirtualAlloc(
		reinterpret_cast<LPVOID>(m_tNtHeader.OptionalHeader.ImageBase),
		static_cast<SIZE_T>(m_tNtHeader.OptionalHeader.SizeOfImage),
		ALLOCATION_TYPE,
		PAGE_PROTECTION);
	if (nullptr == image_address)
	{
		throw LoaderException(L"Failed reserving image memory", GetLastError());
	}

	// Log if the base address mapped is different from the PE header image address
	if (m_tNtHeader.OptionalHeader.ImageBase != reinterpret_cast<DWORD>(image_address))
	{
		std::wcout << L"Image address not mapped to header address: 0x" << std::hex << m_tNtHeader.OptionalHeader.ImageBase <<
			std::endl << L"New address: 0x" << std::hex << image_address << std::endl;
	}

	m_image_address = static_cast<PBYTE>(image_address);
	// Copy the headers to the virtual allocated memory
	copy_headers();
	

	// TODO: check return value and continue mapping to memory
	// TODO: remmeber to change page protection to readonly after copying all section
	map_sections(pbBuffer, buffer_size);
}

void LoadedModule::copy_headers() 
{
	const uint32_t ALLOCATION_TYPE = MEM_COMMIT;
	const uint32_t PAGE_PROTECTION = PAGE_READWRITE;

	auto alloc_res = VirtualAlloc(m_image_address, sizeof(m_tDosHeader), ALLOCATION_TYPE, PAGE_PROTECTION);
	if (nullptr == alloc_res)
	{
		throw LoaderException(L"Failed committing DOS header memory", GetLastError());
	}
	CopyMemory(m_image_address, &m_tDosHeader, sizeof(m_tDosHeader));
	std::wcout << L"Copied dos headers to address: 0x" << std::hex << m_image_address << std::endl;

	auto nt_header_address = m_image_address + m_tDosHeader.e_lfanew;
	alloc_res = VirtualAlloc(nt_header_address, sizeof(m_tNtHeader), ALLOCATION_TYPE, PAGE_PROTECTION);
	if (nullptr == alloc_res)
	{
		throw LoaderException(L"Failed committing NT header memory", GetLastError());
	}
	CopyMemory(nt_header_address, &m_tNtHeader, sizeof(m_tNtHeader));
	std::wcout << L"Copied NT headers to address: 0x" << std::hex << nt_header_address << std::endl;

	// TODO: change headers address space to READONLY.
	// TODO: Delete / do not copy the DOS header at all.
}

void LoadedModule::map_sections(PBYTE pbBuffer, size_t buffer_size) const
{
	// Jump to the sections table in the buffer
	auto sections_ptr = reinterpret_cast<PIMAGE_SECTION_HEADER>(pbBuffer + m_tDosHeader.e_lfanew + sizeof(m_tNtHeader));

	for (auto i = 0; i < m_tNtHeader.FileHeader.NumberOfSections; ++i)
	{
		// TODO: map the section using virtual alloc and also virtual protect.
		PIMAGE_SECTION_HEADER section = sections_ptr + i;
		std::wcout << L"Section no."<< i << " size: " << section->SizeOfRawData << std::endl;
	}
}

