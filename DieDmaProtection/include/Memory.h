#pragma once
#include "print.h"

#include <ntddk.h>

namespace Memory {
	UINT64 VirtToPhy(PVOID Va);
	UINT64 PhyToVirt(UINT64 Pa);
}