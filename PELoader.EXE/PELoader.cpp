// PELoader.cpp : Defines the entry point for the console application.
//

#include <cstdio>
#include <iostream>
//#include <tchar.h>
#include <PELoader.h>

int main()
{
	std::wcout << L"Hello" << std::endl;

	HLOADEDMODULE mod = Load();

	Print(mod);

	FreeLoadedModule(mod);

    return 0;
}