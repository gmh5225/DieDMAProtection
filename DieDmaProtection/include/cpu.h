#pragma once
#include "print.h"
#include "Arch/Cpuid.h"

#include <ntddk.h>
#include <intrin.h>

namespace CPU {
	extern bool bIntelCPU;

	bool IsIntelCPU();
	void Init();

    VOID* WriteBackDataCacheRange(VOID* Address, SIZE_T Length);

    template<typename T>
    T MmIoRead(DWORD64 pMmio) {
        PHYSICAL_ADDRESS pa = { 0 };
        pa.QuadPart = pMmio;
        PVOID pRegister = MmMapIoSpace(pa, sizeof(T), MEMORY_CACHING_TYPE::MmNonCached);

        T ret = *(T*)pRegister;

        MmUnmapIoSpace(pRegister, sizeof(T));

        return ret;
    }
}