#pragma once

class GameFlags
{
public:
	static void SetFlagState(uint32_t flagId, bool newFlagState);
	static bool GetFlagState(uint32_t flagID);
private:
	static uintptr_t* GetInstancePtr();
	static bool IsLoaded();
};