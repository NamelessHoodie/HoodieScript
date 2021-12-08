#include "pch.h"
#include "LuaMemory.h"
namespace hoodie_script
{
	uintptr_t LuaMemory::MultiLevelPointer(uintptr_t base, sol::variadic_args vargs) {
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
	uintptr_t LuaMemory::DereferencePointer(uintptr_t address)
	{
		return *(uintptr_t*)address;
	}
	bool LuaMemory::IsPtrValid(uintptr_t address)
	{
		return !(address < 65536 || IsBadReadPtr((void*)(address), sizeof(void*)));
	}
	int8_t LuaMemory::ReadInt8(uintptr_t address)
	{
		return *(int8_t*)address;
	}
	int16_t LuaMemory::ReadInt16(uintptr_t address)
	{
		return *(int16_t*)address;
	}
	int32_t LuaMemory::ReadInt32(uintptr_t address)
	{
		return *(int32_t*)address;
	}
	int64_t LuaMemory::ReadInt64(uintptr_t address)
	{
		return *(int64_t*)address;
	}
	uint8_t LuaMemory::ReadUint8(uintptr_t address)
	{
		return *(uint8_t*)address;
	}
	uint16_t LuaMemory::ReadUint16(uintptr_t address)
	{
		return *(uint16_t*)address;
	}
	uint32_t LuaMemory::ReadUint32(uintptr_t address)
	{
		return *(uint32_t*)address;
	}
	uint64_t LuaMemory::ReadUint64(uintptr_t address)
	{
		return *(uint64_t*)address;
	}
	float LuaMemory::ReadFloat(uintptr_t address)
	{
		return *(float*)address;
	}
	double LuaMemory::ReadDouble(uintptr_t address)
	{
		return *(double*)address;
	}
	std::string LuaMemory::ReadString(uintptr_t address)
	{
		return std::string((const char*)address);
	}
	void LuaMemory::WriteInt8(uintptr_t address, int8_t newValue)
	{
		*(int8_t*)address = newValue;
	}
	void LuaMemory::WriteInt16(uintptr_t address, int16_t newValue)
	{
		*(int16_t*)address = newValue;
	}
	void LuaMemory::WriteInt32(uintptr_t address, int32_t newValue)
	{
		*(int32_t*)address = newValue;
	}
	void LuaMemory::WriteInt64(uintptr_t address, int64_t newValue)
	{
		*(int64_t*)address = newValue;
	}
	void LuaMemory::WriteUint8(uintptr_t address, uint8_t newValue)
	{
		*(int8_t*)address = newValue;
	}
	void LuaMemory::WriteUint16(uintptr_t address, uint16_t newValue)
	{
		*(int16_t*)address = newValue;
	}
	void LuaMemory::WriteUint32(uintptr_t address, uint32_t newValue)
	{
		*(int32_t*)address = newValue;
	}
	void LuaMemory::WriteUint64(uintptr_t address, uint64_t newValue)
	{
		*(int64_t*)address = newValue;
	}
	void LuaMemory::WriteFloat(uintptr_t address, float newValue)
	{
		*(float*)address = newValue;
	}
	void LuaMemory::WriteDouble(uintptr_t address, double newValue)
	{
		*(double*)address = newValue;
	}
	void LuaMemory::WriteString(uintptr_t address, std::string newValue)
	{
		memcpy((void*)address, (void*)newValue.c_str(), newValue.size());
	}
}