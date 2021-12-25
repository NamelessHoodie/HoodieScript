#include "pch.h"
#include "GameFlags.h"

uintptr_t* GameFlags::GetInstancePtr()
{
	return *(uintptr_t**)0x14473BE28;
}

bool GameFlags::IsLoaded()
{
	return *(uintptr_t**)0x14473BE28 != nullptr;
}

void GameFlags::SetFlagState(uint32_t flagId, bool newFlagState)
{
	if (!IsLoaded())
		return;
	call(0x1404C5060, GetInstancePtr(), flagId, newFlagState);
}

bool GameFlags::GetFlagState(uint32_t flagID)
{
	if (!IsLoaded())
		return false;
	return (bool)(call(0x1404C4590, GetInstancePtr(), flagID) & 1);
}