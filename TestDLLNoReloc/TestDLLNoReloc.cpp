// TestDLLNoReloc.cpp : Defines the exported functions for the DLL application.
//

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>
#include <iostream>

DWORD WINAPI Add(DWORD a, DWORD b)
{
	return a + b;
}


