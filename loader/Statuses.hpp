#pragma once
#include <cstdint>

class LoaderStatus
{
public:
	static const uint32_t LOADEDSTATUS_SUCCESS = 0x0;
	static const uint32_t LOADERSTATUS_DOS_MAGIC_NOT_FOUND = 0x1;
};

using LOADERSTATUS = uint32_t;