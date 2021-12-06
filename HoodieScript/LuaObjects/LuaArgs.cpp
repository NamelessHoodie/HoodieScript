#include "pch.h"
#include "LuaArgs.h"

namespace hoodie_script
{
	LuaArgs::LuaArgs(uintptr_t hkbInternalPtr)
	{
		this->_hkbInternalPtr = hkbInternalPtr;
	}
	std::string LuaArgs::GetString1(uint32_t index)
	{
		return std::string((const char*)call(0x1410e48f0, _hkbInternalPtr, index));
	}
	std::string LuaArgs::GetString0(uint32_t index)
	{
		return std::string((const char*)call(0x140d9cd00, _hkbInternalPtr, index));
	}
	bool LuaArgs::HasUint64(uint32_t index)
	{
		return call(0x14112b7f0, _hkbInternalPtr, index) != false;
	}
	uint64_t LuaArgs::GetUint64(uint32_t index)
	{
		//return call(0x140d9cca0, _hkbInternalPtr, index);
		return call(0x14112df50, _hkbInternalPtr, index);
	}
}