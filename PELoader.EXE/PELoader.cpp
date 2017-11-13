// PELoader.cpp : Defines the entry point for the console application.
//

#include <Windows.h>

#include <cstdio>
#include <iostream>
//#include <tchar.h>
#include <PELoader.h>

int main()
{
	
	const std::wstring file(L"C:\\Windows\\System32\\user32.dll");
	
	HANDLE h = CreateFile(
		file.c_str(),
		GENERIC_READ,
		FILE_SHARE_READ,
		nullptr,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		nullptr);



	/*std::wcout << L"Hello" << std::endl;

	HLOADEDMODULE mod = Load();

	Print(mod);

	FreeLoadedModule(mod);*/

    return 0;
}