// PELoader.cpp : Defines the entry point for the console application.
//

#include <Windows.h>

#include <cstdio>
#include <iostream>
//#include <tchar.h>
//#include <PELoader.h>
#include "MemoryMappedFile.hpp"

#ifdef __cplusplus
extern "C" {
#endif
//#include "PELoader.h"
#include <PELoader.h>
#ifdef __cplusplus
}
#endif


typedef DWORD (WINAPI* FUNC)(DWORD, DWORD);

int main()
{
	/*const std::wstring file(L"C:\\Windows\\System32\\user32.dll");*/
	const std::wstring file(L"Z:\\projects\\peloader\\Output\\Win32\\Debug\\TestDlls\\TestDLLNoReloc.dll");

	MemoryMappedFile mem_mapped_file(file);

	const auto size = mem_mapped_file.get_file_buffer_size();

	std::wcout << L"File size: " << size << std::endl;

	const auto mod = Load(static_cast<PBYTE>(mem_mapped_file.get_file_buffer()), size);

	Print(mod);

	FreeLoadedModule(mod);

	/*HMODULE mod = LoadLibrary(L"Z:\\projects\\peloader\\Output\\x64\\Debug\\TestDlls\\TestDLLNoReloc.dll");

	FUNC f = (FUNC)GetProcAddress(mod, "Add");

	DWORD val = f(1, 2);

	std::wcout << val << std::endl;*/


    return 0;
}
