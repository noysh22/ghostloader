#pragma once
#include <string>

#include <Windows.h>

#include "File.hpp"

class MemoryMappedFile : public File
{
public:
	MemoryMappedFile(const std::wstring& file);
	~MemoryMappedFile();

	static HANDLE create_file_mapping(const HANDLE file_handle);

	PVOID get_file_buffer() const;
	size_t get_file_buffer_size() const;

private:
	const HANDLE m_hMappedFile;
	PVOID m_pFileBuffer;
};
