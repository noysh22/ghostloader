#pragma once

#include <Windows.h>
#include "LoadedModule.hpp"

//typedef LoadedModule *HLOADEDMODULE;

#ifdef __cplusplus
extern "C"  {
#endif

/**

*/
//PBYTE pbModuleBuffer
HLOADEDMODULE WINAPI Load(PVOID pvBuffer, SIZE_T cbBufferSize);

DWORD WINAPI Print(HLOADEDMODULE mod);

DWORD WINAPI FreeLoadedModule(HLOADEDMODULE mod);

#ifdef __cplusplus
}
#endif

