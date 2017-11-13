#include <exception>
#include <iostream>

#include "File.hpp"
#include "Exceptions.hpp"

File::File(const std::wstring& file_name) :	
	m_hFile(create_file(file_name,
		GENERIC_READ,
		FILE_SHARE_READ,
		nullptr,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		nullptr)) 
{ }

File::File(const std::wstring& file_name, uint32_t desired_access, uint32_t share_mode, LPSECURITY_ATTRIBUTES security_attributes, uint32_t creation_deposition, uint32_t flags_and_attr, HANDLE template_file) :
	m_hFile(create_file(file_name, desired_access, share_mode, security_attributes, creation_deposition, flags_and_attr, template_file))
{ }

HANDLE File::create_file(const std::wstring& file_name, uint32_t desired_access, uint32_t share_mode, LPSECURITY_ATTRIBUTES security_attributes, uint32_t creation_deposition, uint32_t flags_and_attr, HANDLE template_file)
{
	std::wcout << L"File::create_file" << std::endl;

	const HANDLE file = CreateFile(file_name.c_str(),
		desired_access,
		share_mode,
		security_attributes,
		creation_deposition,
		flags_and_attr,
		template_file);

	if (INVALID_HANDLE_VALUE == file)
	{
		std::wcout << L"CreateFile failed with error_code: " << GetLastError()
			<< std::endl;
		throw Exception(L"CreateFile failed", GetLastError());
	}

	return file;
}

File::~File()
{
	try
	{
		std::wcout << L"File::~File" << std::endl;

		if(!CloseHandle(m_hFile))
		{
			std::wcout << L"Failed closing handle with error_code: " << GetLastError()
				<< std::endl;
		}
	}
	catch (...)
	{
		std::wcout << L"Exception throws in File destructor: " << GetLastError()
			<< std::endl;
	}
}


