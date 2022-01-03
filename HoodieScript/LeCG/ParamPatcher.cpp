#include "pch.h"
#include "LeCG/ParamPatcher.h"

namespace hoodie_script {
	//uintptr_t StandardPlayerBoss::GetParamPtr(ParamBaseOffset Offset)
	//{
	//	var ParamPtr = IntPtr.Add(Memory.BaseAddress, 0x4782838);
	//	ParamPtr = new IntPtr(Memory.ReadInt64(ParamPtr));
	//	ParamPtr = IntPtr.Add(ParamPtr, (int)Offset);
	//	ParamPtr = new IntPtr(Memory.ReadInt64(ParamPtr));
	//	ParamPtr = IntPtr.Add(ParamPtr, 0x68);
	//	ParamPtr = new IntPtr(Memory.ReadInt64(ParamPtr));
	//	ParamPtr = IntPtr.Add(ParamPtr, 0x68);
	//	ParamPtr = new IntPtr(Memory.ReadInt64(ParamPtr));
	//
	//	return accessMultilevelPointer<uintptr_t>((uintptr_t)((byte)DataBaseAddress::BASEExecutable + (byte)0x4782838), Offset, 0x68, 0x68);
	//}
	//uintptr_t* StandardPlayerBoss::GetRowAddressInParam(int RowID, uintptr_t paramPtr) { //this is not good, make sure to fix it if you use it.
	//	int num = 0;
	//	byte* param = (byte*)paramPtr;
	//	byte* DataOffset = param + (byte)0x40;
	//	if (*(unsigned int*)DataOffset == RowID) {
	//		return (uintptr_t*)(param + *(unsigned int*)(DataOffset + (byte)0x8));
	//	}
	//	while (true) {
	//		num += 1;
	//		DataOffset += (byte)0x18;
	//		if (*(unsigned int*)DataOffset == 0) {
	//			std::cout << "Row ID: " << std::dec << RowID << " Was Not Found" << std::endl;
	//			return nullptr;
	//		}
	//		else if (*(unsigned int*)DataOffset == RowID) {
	//			return (uintptr_t*)(param + *(unsigned int*)(DataOffset + (byte)0x8));
	//		}
	//	}
	//}
	ParamPatcher::ParamPatcher()
	{
		while (!hasGameLoaded()) { Sleep(100); }
		Sleep(1000);
		std::uint64_t ParamPatch = (*(std::uint64_t*)PARAMBASE) + 0x10;
		std::uint64_t ParamStart = *(std::uint64_t*)ParamPatch;
		std::uint64_t ParamEnd = *(std::uint64_t*)(ParamPatch + 0x8);
		std::uint64_t ParamCount = (ParamEnd - ParamStart) / 0x8;
		std::uint64_t targetParam = 0;
		std::wstring paramName;
		std::vector<std::wstring*> allParamNames;
		for (std::uint64_t i = 0; i < ParamCount; i++) {
			while (targetParam == NULL) {
				targetParam = *(std::uint64_t*)(ParamStart + (i * 0x8));
				if (targetParam == NULL) {
					Sleep(10);
					continue;
				}
			}
			paramName.reserve(90);
			if (*(std::uint32_t*)(targetParam + 0x20) > 7) {
				wcscpy_s((wchar_t*)paramName.data(), 90, (wchar_t*)*(std::uint64_t*)(targetParam + 0x10));
			}
			else {
				wcscpy_s((wchar_t*)paramName.data(), 90, (wchar_t*)(targetParam + 0x10));
			}
			allParamNames.push_back(new std::wstring(paramName.c_str()));
			std::thread* worker = new std::thread([&](std::wstring* ParamName, std::uint64_t ParamAddress) {
				std::uint64_t ParamAddr = *(std::uint64_t*)(*(std::uint64_t*)(ParamAddress + 0x68) + 0x68);
				std::uint32_t NumEntries = *(std::uint16_t*)(ParamAddr + 0xA);
				std::uint32_t PID, IDO;
				for (std::uint32_t i = 0; i < NumEntries; i++) {
					PID = *(std::uint32_t*)(ParamAddr + 0x40 + (0x18 * i));
					IDO = *(std::uint32_t*)(ParamAddr + 0x48 + (0x18 * i));
					AllParamEntries[(*ParamName)][PID] = (ParamAddr + IDO);
				}
				}, allParamNames.back(), targetParam);
			ParamWorkers.push_back(worker);
			targetParam = NULL;
		}
		for (auto it = ParamWorkers.begin(); it != ParamWorkers.end(); it++) {
			(*it)->join();
			delete (*it);
		}
		ParamWorkers.clear();
		for (auto it = allParamNames.begin(); it != allParamNames.end(); it++) {
			delete (*it);
		}
		allParamNames.clear();
	}

	ParamPatcher::~ParamPatcher()
	{
		for (auto it = NamedPatches.begin(); it != NamedPatches.end(); it++)
		{
			DestroyPatchGroup(it->first);
		}
	}

	std::vector<std::uint32_t> ParamPatcher::GetAllIDsInParam(std::wstring ParamName) {
		auto param = AllParamEntries[ParamName];
		std::vector<std::uint32_t> data;
		for (auto it = param.begin(); it != param.end(); it++) {
			data.push_back(it->first);
		}
		return data;
	}

	bool ParamPatcher::hasGameLoaded() {
		std::uint64_t SoloParamRepo = *(std::uint64_t*)0x144782838;
		return SoloParamRepo && (call(0x140e2ffd0, SoloParamRepo, 0x5F, 0) != NULL);
	}

	void ParamPatcher::writeByteVector(std::uint64_t Address, std::vector<std::uint8_t>* data) {
		memcpy((void*)Address, data->data(), data->size());
	}

	void  ParamPatcher::EnablePatchGroup(std::string PatchGroup) {
		auto group = &NamedPatches[PatchGroup];
		for (auto Param = group->begin(); Param != group->end(); Param++) {
			for (auto ParamEntryID = Param->second.begin(); ParamEntryID != Param->second.end(); ParamEntryID++) {
				for (auto EntryOffset = ParamEntryID->second.begin(); EntryOffset != ParamEntryID->second.end(); EntryOffset++) {
					writeByteVector(AllParamEntries[Param->first][ParamEntryID->first] + EntryOffset->first, &EntryOffset->second);
				}
			}
		}
	}
	void  ParamPatcher::DisablePatchGroup(std::string PatchGroup) {
		auto group = &NamedPatches[PatchGroup];
		for (auto Param = group->begin(); Param != group->end(); Param++) {
			for (auto ParamEntryID = Param->second.begin(); ParamEntryID != Param->second.end(); ParamEntryID++) {
				for (auto EntryOffset = ParamEntryID->second.begin(); EntryOffset != ParamEntryID->second.end(); EntryOffset++) {
					RestoreParamIdMember(Param->first, ParamEntryID->first, EntryOffset->first);
				}
			}
		}
	}
	void  ParamPatcher::DestroyPatchGroup(std::string PatchGroup) {

		DisablePatchGroup(PatchGroup);

		auto group = &NamedPatches[PatchGroup];
		for (auto Param = group->begin(); Param != group->end(); Param++) {
			for (auto ParamEntryID = Param->second.begin(); ParamEntryID != Param->second.end(); ParamEntryID++) {
				for (auto EntryOffset = ParamEntryID->second.begin(); EntryOffset != ParamEntryID->second.end(); EntryOffset++) {
					EntryOffset->second.clear();
				}
				ParamEntryID->second.clear();
			}
			Param->second.clear();
		}
		group->clear();
	}

	void ParamPatcher::RestoreAll() {
		auto elements = &Restore;
		for (auto it = elements->begin(); it != elements->end(); it++) {
			RestoreParam(it->first);
		}
	}
	void ParamPatcher::RestoreParam(std::wstring ParamName) {
		auto elements = &Restore[ParamName];
		for (auto it = elements->begin(); it != elements->end(); it++) {
			RestoreParamId(ParamName, it->first);
		}
	}
	void ParamPatcher::RestoreParamId(std::wstring ParamName, std::uint32_t EntryID) {
		auto elements = &Restore[ParamName][EntryID];
		for (auto it = elements->begin(); it != elements->end(); it++) {
			RestoreParamIdMember(ParamName, EntryID, it->first);
		}
	}
	void ParamPatcher::RestoreParamIdMember(std::wstring ParamName, std::uint32_t EntryID, std::uint32_t Offset) {
		std::uint64_t ParamEntry = AllParamEntries[ParamName][EntryID];
		if (ParamEntry != NULL) {
			std::vector<std::uint8_t>* res = &Restore[ParamName][EntryID][Offset];
			if (res->size() > 0) {
				writeByteVector((ParamEntry + Offset), res);
			}
		}
	}

	SetParamEntryFunction(std::uint8_t);
	SetParamEntryFunction(std::uint16_t);
	SetParamEntryFunction(std::uint32_t);
	SetParamEntryFunction(std::uint64_t);
	SetParamEntryFunction(float);
	SetParamEntryFunction(double);

	GetParamEntryFunction(std::uint8_t);
	GetParamEntryFunction(std::uint16_t);
	GetParamEntryFunction(std::uint32_t);
	GetParamEntryFunction(std::uint64_t);
	GetParamEntryFunction(float);
	GetParamEntryFunction(double);

	bool ParamPatcher::GetParamEntryBitFlag(std::wstring ParamName, std::uint32_t EntryID, std::uint32_t Offset, std::uint8_t Bit, bool* Value) {
		std::uint8_t EightFlags;
		if (GetParamEntry(ParamName, EntryID, Offset, &EightFlags)) {
			*Value = ((EightFlags >> Bit) & 0x01);
			return true;
		}
		return false;
	}

	bool ParamPatcher::SetParamEntryBitFlag(std::string PatchGroup, std::wstring ParamName, std::uint32_t EntryID, std::uint32_t Offset, std::uint8_t Bit, bool Value) {
		std::uint8_t EightFlags;
		if (GetParamEntry(ParamName, EntryID, Offset, &EightFlags)) {
			if (Value)
				EightFlags |= 1 << Bit;
			else
				EightFlags &= ~(1 << Bit);
			return SetParamEntry(PatchGroup, ParamName, EntryID, Offset, EightFlags);
		}
		return false;
	}
}