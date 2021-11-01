#pragma once
#include <Windows.h>
#include <thread>
#include <string>
#include <vector>
#include <map>

namespace hoodie_script {

	//macro from amir who got it from someone
#define call(f,...) (((intptr_t(*)(uintptr_t,...))(f))((uintptr_t)__VA_ARGS__))

#define SetParamEntryDefine(type) bool SetParamEntry(std::string, std::wstring, std::uint32_t, std::uint32_t, type);
#define SetParamEntryFunction(type) \
bool ParamPatcher::SetParamEntry(std::string PatchGroup, std::wstring ParamName, std::uint32_t EntryID, std::uint32_t Offset, type Value) {\
	std::uint64_t ParamEntry = AllParamEntries[ParamName][EntryID];\
	if (ParamEntry != NULL) {\
		std::vector<std::uint8_t>* restore = &Restore[ParamName][EntryID][Offset];\
		if (restore->size() == 0) {\
			restore->resize(sizeof(Value));\
			memcpy(restore->data(), (void*)(ParamEntry + Offset), sizeof(Value));\
		}\
		std::vector<std::uint8_t>* namedpatch = &NamedPatches[PatchGroup][ParamName][EntryID][Offset];\
		namedpatch->resize(sizeof(Value));\
		memcpy(namedpatch->data(), &Value, sizeof(Value));\
		*(type*)(ParamEntry + Offset) = Value;\
		return true;\
	}\
	return false;\
}
#define GetParamEntryDefine(type) bool GetParamEntry(std::wstring, std::uint32_t, std::uint32_t, type*);
#define GetParamEntryFunction(type)\
bool ParamPatcher::GetParamEntry(std::wstring ParamName, std::uint32_t EntryID, std::uint32_t Offset, type* Value) {\
	std::uint64_t ParamEntry = AllParamEntries[ParamName][EntryID];\
	if (ParamEntry != NULL) {\
		*Value = *(type*)(ParamEntry + Offset);\
		return true;\
	}\
	return false;\
}

	class ParamPatcher
	{
	public:
		ParamPatcher();
		~ParamPatcher();
		SetParamEntryDefine(std::uint8_t);
		SetParamEntryDefine(std::uint16_t);
		SetParamEntryDefine(std::uint32_t);
		SetParamEntryDefine(std::uint64_t);
		SetParamEntryDefine(float);
		SetParamEntryDefine(double);

		GetParamEntryDefine(std::uint8_t);
		GetParamEntryDefine(std::uint16_t);
		GetParamEntryDefine(std::uint32_t);
		GetParamEntryDefine(std::uint64_t);
		GetParamEntryDefine(float);
		GetParamEntryDefine(double);

		bool GetParamEntryBitFlag(std::wstring, std::uint32_t, std::uint32_t, std::uint8_t, bool*);
		bool SetParamEntryBitFlag(std::string, std::wstring, std::uint32_t, std::uint32_t, std::uint8_t, bool);

		void EnablePatchGroup(std::string);
		void DisablePatchGroup(std::string);
		void DestroyPatchGroup(std::string);

		void RestoreAll();
		void RestoreParam(std::wstring);
		void RestoreParamId(std::wstring, std::uint32_t);
		void RestoreParamIdMember(std::wstring, std::uint32_t, std::uint32_t);

		std::vector<std::uint32_t> GetAllIDsInParam(std::wstring);
	private:
		std::vector<std::thread*> ParamWorkers;
		std::map<std::wstring, std::map<std::uint32_t, std::uint64_t>> AllParamEntries;
		//Oh God this is a mess
		//Ex: NamedPatches["DMBundle"][L"EquipParamGoods"][341][0x0].data()
		//        Patch Group           Param                 ParamEntryID           EntryOffset   Value as AOB     
		std::map <std::string, std::map<std::wstring, std::map<std::uint32_t, std::map<std::uint32_t, std::vector<std::uint8_t>>>>> NamedPatches;
		//        Param                  ParamEntryID            EntryOffset    Original Value as AOB
		std::map <std::wstring, std::map<std::uint32_t, std::map<std::uint32_t, std::vector<std::uint8_t>>>> Restore;
		//std::map<std::uint64_t, std::vector<std::uint8_t>> Restore;
		//
		const std::uint64_t PARAMBASE = 0x144785FE0;
		/*
		Functions
		*/
		void writeByteVector(std::uint64_t, std::vector<std::uint8_t>*);
		bool hasGameLoaded();

	};
}