#pragma once

namespace hoodie_script
{
	class LuaMemory
	{
	public:
		static uintptr_t MultiLevelPointer(uintptr_t base, sol::variadic_args vargs);
		static uintptr_t DereferencePointer(uintptr_t address);
		static uintptr_t Allocate(size_t size);
		static uintptr_t AllocateBytes(std::vector<byte> bytes);
		static uintptr_t AllocateNear(uintptr_t address, size_t size);
		static uintptr_t AllocateBytesNear(uintptr_t address, std::vector<uint8_t> bytes);
		static void Deallocate(uintptr_t address);
		static bool IsPtrValid(uintptr_t address);
		static int8_t ReadInt8(uintptr_t address);
		static int16_t ReadInt16(uintptr_t address);
		static int32_t ReadInt32(uintptr_t address);
		static int64_t ReadInt64(uintptr_t address);
		static uint8_t ReadUint8(uintptr_t address);
		static uint16_t ReadUint16(uintptr_t address);
		static uint32_t ReadUint32(uintptr_t address);
		static uint64_t ReadUint64(uintptr_t address);
		static float ReadFloat(uintptr_t address);
		static double ReadDouble(uintptr_t address);
		static std::string ReadString(uintptr_t address);
		static std::vector<byte> ReadBytes(uintptr_t address, size_t size);
		static void WriteInt8(uintptr_t address, int8_t newValue);
		static void WriteInt16(uintptr_t address, int16_t newValue);
		static void WriteInt32(uintptr_t address, int32_t newValue);
		static void WriteInt64(uintptr_t address, int64_t newValue);
		static void WriteUint8(uintptr_t address, uint8_t newValue);
		static void WriteUint16(uintptr_t address, uint16_t newValue);
		static void WriteUint32(uintptr_t address, uint32_t newValue);
		static void WriteUint64(uintptr_t address, uint64_t newValue);
		static void WriteFloat(uintptr_t address, float newValue);
		static void WriteDouble(uintptr_t address, double newValue);
		static void WriteString(uintptr_t address, std::string newValue);
		static void WriteBytes(uintptr_t address, std::vector<byte> bytes);
	private:

	};
}