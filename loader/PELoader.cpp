#include "PELoader.h"
#include <iostream>

HLOADEDMODULE WINAPI Load(PVOID pvBuffer, SIZE_T cbBufferSize)
{
	try
	{
		const auto ptDosHeader = static_cast<PIMAGE_DOS_HEADER>(pvBuffer);
		const auto ptNtHeader = reinterpret_cast<PIMAGE_NT_HEADERS>(static_cast<PBYTE>(pvBuffer) + ptDosHeader->e_lfanew);

		const auto loaded_mod = new LoadedModule(
			static_cast<PBYTE>(pvBuffer),
			cbBufferSize,
			ptDosHeader,
			ptNtHeader);

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