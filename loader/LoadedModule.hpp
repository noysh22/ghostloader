#pragma once

#include <Windows.h>
#include "Statuses.hpp"

//typedef struct _LOADERMODULE {
//
//} LOADEDMODULE, *PLOADERMODULE;
//

typedef PVOID HLOADEDMODULE;

class LoadedModule
{
public:
	LoadedModule(PBYTE pbBuffer, size_t buffer_size, PIMAGE_DOS_HEADER ptDosHeader, PIMAGE_NT_HEADERS ptNTHeader);
	//LoadedModule(PBYTE pbBuffer, size_t buffer_size);
	~LoadedModule();

	void print_me() const;

private:
	//LsOADEDMODULE tLoadedModule;
	IMAGE_DOS_HEADER m_tDosHeader;
	IMAGE_NT_HEADERS m_tNtHeader;
	size_t m_LoadedImageSize;
	PBYTE m_image_address;

	void load(PBYTE pbBuffer, size_t buffer_size);
	void copy_headers();
	void map_sections(PBYTE pbBuffer, size_t buffer_size) const;

	LOADERSTATUS free() const;
};
