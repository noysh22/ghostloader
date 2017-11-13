#include "MemoryMappedFile.hpp"
#include <iostream>
#include "Exceptions.hpp"


MemoryMappedFile::MemoryMappedFile(const std::wstring& file)
	: File(file), m_hMappedFile(create_file_mapping(m_hFile))
{
	const uint32_t desired_access = FILE_MAP_READ;
	const uint32_t file_offset_high = 0;
	const uint32_t file_offset_low = 0;
	const size_t num_of_bytes_to_map = 0;

	m_pFileBuffer = MapViewOfFile(m_hMappedFile, desired_access, file_offset_high, file_offset_low, num_of_bytes_to_map);

	if (nullptr == m_pFileBuffer)
	{
		std::wcout << L"MapViewOfFile failed with error_code: " << GetLastError()
			<< std::endl;
		throw Exception(L"MapViewOfFile failed", GetLastError());
	}
}

HANDLE MemoryMappedFile::create_file_mapping(const HANDLE file_handle)
{
	std::wcout << L"MemoryMappedFile::create_file_mapping" << std::endl;

	const LPSECURITY_ATTRIBUTES security_attributes = nullptr;
	const uint32_t protect = PAGE_READONLY;
	const uint32_t max_size_high = 0;
	const uint32_t max_size_low = 0;
	const LPCWSTR name = nullptr;

	const HANDLE handle = CreateFileMapping(file_handle, security_attributes, protect, max_size_high, max_size_low, name);

	uint32_t last_error = GetLastError();

	if (nullptr != handle && ERROR_ALREADY_EXISTS == last_error)
	{
		std::wcout << L"File mapping already exists" << std::endl;
	}

	if(nullptr == handle)
	{
		std::wcout << L"CreateFileMapping failed with error_code: " << last_error
			<< std::endl;
		throw Exception(L"CreateFileMapping failed", last_error);
	}

	return handle;
}

MemoryMappedFile::~MemoryMappedFile()
{
	try
	{
		std::wcout << L"MemoryMappedFile::~MemoryMappedFile" << std::endl;

		// Unmap view of file
		if (!UnmapViewOfFile(m_pFileBuffer))
		{
			std::wcout << L"Failed unmapping view of file error_code: " << GetLastError()
				<< std::endl;
		}

		if (!CloseHandle(m_hMappedFile))
		{
			std::wcout << L"Failed closing mapped file handle with error_code: " << GetLastError()
				<< std::endl;
		}
	}
	catch (...)
	{
		std::wcout << L"Exception throws in MemoryMappedFile destructor: " << GetLastError()
			<< std::endl;
	}
}

PVOID MemoryMappedFile::get_file_buffer() const
{
	return m_pFileBuffer;
}

size_t MemoryMappedFile::get_file_buffer_size() const
{
	LARGE_INTEGER size = { 0 };
	
	if (0 == GetFileSizeEx(m_hFile, &size))
	{
		std::wcout << L"GetFileSizeEx failed with error_code: " << GetLastError()
			<< std::endl;
		throw Exception(L"GetFileSizeEx failed", GetLastError());
	}

	return static_cast<size_t>(size.QuadPart);
}




