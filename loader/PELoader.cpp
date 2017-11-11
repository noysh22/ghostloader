#include "PELoader.h"
#include <iostream>

HLOADEDMODULE WINAPI Load()
{
	try
	{
		const auto loaded_mod = new LoadedModule(10);

		return static_cast<HLOADEDMODULE>(loaded_mod);
	}
	catch (...)
	{
		std::wcout << L"Failed creating loaded module" << std::endl;
		return nullptr;
	}

	
}

DWORD WINAPI Print(const HLOADEDMODULE mod)
{
	const auto loaded_mod = static_cast<LoadedModule*>(mod);

	if (nullptr == loaded_mod)
	{
		std::wcout << L"Failed casting to cpp class" << std::endl;
		return DWORD(-1);
	}
	
	loaded_mod->print_me();

	return ERROR_SUCCESS;
}

DWORD WINAPI FreeLoadedModule(const HLOADEDMODULE mod)
{
	const auto loaded_mod = static_cast<LoadedModule*>(mod);

	if (nullptr == loaded_mod)
	{
		std::wcout << L"Failed casting to cpp class" << std::endl;
		return DWORD(-1);
	}

	delete loaded_mod;

	return ERROR_SUCCESS;
}