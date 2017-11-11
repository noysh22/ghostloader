#include <Windows.h>
#include "LoadedModule.hpp"
#include <iostream>

LoadedModule::LoadedModule(UINT num)
{
	std::wcout << L"Constructor" << std::endl;

	m_uNum = num;
}

LoadedModule::~LoadedModule()
{
	std::wcout << L"Destructor" << std::endl;
}

void LoadedModule::print_me() const
{
	std::wcout << L"The number is:" << m_uNum << std::endl;
}
