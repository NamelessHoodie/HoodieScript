#pragma once

namespace hoodie_script
{
	class LuaArgs
	{
	public:
		LuaArgs(uintptr_t hkbInternalPtr);
		std::string GetString0(uint32_t index);
		std::string GetString1(uint32_t index);
		bool HasUint64(uint32_t index);
		uint64_t GetUint64(uint32_t index);
		uintptr_t _hkbInternalPtr;
	private:
	};
}