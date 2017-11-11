#pragma once

#include <Windows.h>

//typedef struct _LOADERMODULE {
//
//} LOADEDMODULE, *PLOADERMODULE;
//

typedef PVOID HLOADEDMODULE;

class LoadedModule
{
public:
	LoadedModule(UINT num);
	~LoadedModule();

	VOID print_me() const;

private:
	//LOADEDMODULE tLoadedModule;
	UINT m_uNum;
};
