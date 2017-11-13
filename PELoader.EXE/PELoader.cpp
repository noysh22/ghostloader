// PELoader.cpp : Defines the entry point for the console application.
//

#include <Windows.h>

#include <cstdio>
#include <iostream>
//#include <tchar.h>
#include <PELoader.h>
#include "MemoryMappedFile.hpp"

int main()
{
	
	const std::wstring file(L"C:\\Windows\\System32\\user32.dll");

	MemoryMappedFile mem_mapped_file(file);

	const auto size = mem_mapped_file.get_file_buffer_size();

	std::wcout << L"File size: " << size << std::endl;

	/*HLOADEDMODULE mod = Load();

	Print(mod);

	FreeLoadedModule(mod);*/

    return 0;
}
