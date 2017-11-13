#pragma once

#include <Windows.h>
#include <string>

class File
{
public:
	File(const std::wstring& file_name);
	File(const std::wstring& file_name,
		uint32_t desired_access,
		uint32_t share_mode,
		LPSECURITY_ATTRIBUTES security_attributes,
		uint32_t creation_deposition,
		uint32_t flags_and_attr,
		HANDLE template_file);
	~File();

	static HANDLE create_file(
		__in const std::wstring& file_name,
		__in uint32_t desired_access,
		__in uint32_t share_mode,
		__in_opt LPSECURITY_ATTRIBUTES security_attributes,
		__in uint32_t creation_deposition,
		__in uint32_t flags_and_attr,
		__in_opt HANDLE template_file);

protected:
	HANDLE m_hFile;
};
