#include "pch.h"
#include "LuaMemory.h"
namespace hoodie_script
{
	uintptr_t LuaMemory::GetPtrLua(uintptr_t base, sol::variadic_args vargs) {
		for (auto v : vargs) {
			if (v.is<uintptr_t>())
			{
				if (*(uintptr_t*)base == 0) {
					return (uintptr_t)nullptr;
				}
				else {
					base = (uintptr_t)(*(uintptr_t*)base + (uintptr_t)v);
				}
			}
		}
		return (uintptr_t)base;
	}
	uintptr_t DereferencePointer(uintptr_t address)
	{
		return *(uintptr_t*)address;
	}
	bool LuaMemory::IsPtrValid(uintptr_t address)
	{
		return true;
	}
	int8_t ReadInt8(uintptr_t address)
	{
		return address != NULL ? *(int8_t*)address : NULL;
	}
	int16_t ReadInt16(uintptr_t address)
	{
		return address != NULL ? *(int16_t*)address : NULL;
	}
	int32_t ReadInt32(uintptr_t address)
	{
		return address != NULL ? *(int32_t*)address : NULL;
	}
	int64_t ReadInt64(uintptr_t address)
	{
		return address != NULL ? *(int64_t*)address : NULL;
	}
}