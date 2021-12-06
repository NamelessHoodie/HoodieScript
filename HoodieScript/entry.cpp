#include "pch.h"
#include "entry.h"
#include "vendor/DInput8/DInput8Proxy.h"
#include "LuaEvents/OnParamLoaded.h"
#include <Amir/ds3runtime.h>
#include "GameObjects/SprjMsgRepositoryImp.h"

#define EXCEPTION_STRING_SIZE    1024

std::shared_ptr<hoodie_script::DS3RuntimeScripting> hoodie_script::ds3runtime_global;;

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
	HANDLE thread;
	static HMODULE dinput8dll = nullptr;
	HMODULE chainModule = NULL;
	wchar_t chainPath[MAX_PATH];
	wchar_t dllPath[MAX_PATH];

	switch (ul_reason_for_call) {
	case DLL_PROCESS_ATTACH:
		GetPrivateProfileStringW(L"Misc", L"ChainloadDinput8dll", L"", chainPath, MAX_PATH, L".\\HoodieScript.ini");

		if (chainPath && wcscmp(chainPath, L""))
		{
			GetCurrentDirectoryW(MAX_PATH, dllPath);
			wcscat_s(dllPath, MAX_PATH, L"\\");
			wcscat_s(dllPath, MAX_PATH, chainPath);
			chainModule = LoadLibraryW(dllPath);

			if (chainModule)
			{
				DirectInput8Create_fn = (DirectInput8Create_TYPE)GetProcAddress(chainModule, "DirectInput8Create");
			}
		}

		if (!chainModule)
		{
			wchar_t path[MAX_PATH];
			GetSystemDirectoryW(path, MAX_PATH);
			wcscat_s(path, MAX_PATH, L"\\dinput8.dll");
			dinput8dll = LoadLibraryW(path);

			if (dinput8dll)
			{
				DirectInput8Create_fn = (DirectInput8Create_TYPE)GetProcAddress(dinput8dll, "DirectInput8Create");
			}
		}
		attach();
		break;
	case DLL_PROCESS_DETACH:
		detach();
		break;
	default:
		break;
	}
	return TRUE;
}
void* inputLockOfAddr;
void* menuOpenGetter;
void* menuOpenSetter;
void* addVehOgFun;
void* debugMemeOg;
void* memeHelp;

uint32_t Meme1(int a)
{
	uint32_t meme = call(menuOpenGetter, a);
	static uint32_t memes[5000]{};
	if (memes[a] != meme)
	{
		memes[a] = meme;
		hoodie_script::logging::write_line(std::format("I = {0} | O = {1}", a, meme));
	}
	if (a == 8)
	{
		return 2;
	}
	//return 1;
	return meme;
}

void Meme2(uint32_t index, uint32_t newVal)
{
	static uint32_t memes[5000]{};
	if (memes[index] != newVal)
	{
		memes[index] = newVal;
		hoodie_script::logging::write_line(std::format("index = {0}, newVal = {1}", index, newVal));
	}
	call(menuOpenSetter, index, newVal);
}

const wchar_t* Memletto(uintptr_t luaPtr, uint32_t argIdx)
{
	std::cout << "PreHelp\n";
	const wchar_t* helpMe = (const wchar_t*)call(debugMemeOg, luaPtr, argIdx);
	std::wcout << helpMe << L"\n";
	return helpMe;
}

uint32_t Memes()
{
	return ((uint32_t)call(inputLockOfAddr, NULL)) | 0x40;
}

PVOID addVeh(ULONG first, PVECTORED_EXCEPTION_HANDLER handler)
{
	std::cout << "VEH Added : First = " << first << ", handler = " << std::hex << (unsigned long long)handler << std::endl;
	return (PVOID)call(addVehOgFun, first, handler);
}

bool Idk(uintptr_t hkbMeme)
{
	std::cout << hkbMeme << std::endl;
	//hoodie_script::logging::write_line(std::format("Str = {0}", luaArgs));
	return false;
}

void MemeHelp(uintptr_t luaState, const char* name, uintptr_t functionptr)
{
	static uintptr_t lastAdr = 0;
	if (lastAdr != luaState)
	{
		call(memeHelp, luaState, "HoodieFun", Idk);
		std::cout << std::hex << "HkbLuaState* = " << luaState << ", HKSStringName = " << name << ", FunctionPointer = " << functionptr << "\n";
		lastAdr = luaState;
	}

	call(memeHelp, luaState, name, functionptr);
}

DWORD WINAPI init_thread(void* lpParam)
{
	//SetUnhandledExceptionFilter(exception_handler);
	hoodie_script::script_runtime::initialize();
	hoodie_script::script_repository::load_files();
	HWND ds3Handle = NULL;
	while (!ds3Handle)
	{
		ds3Handle = FindWindowW(0, L"DARK SOULS III");
	}
	hoodie_script::GuiManager::Init();
	hoodie_script::HotKeyManager::Init(ds3Handle);
	hoodie_script::logging::write_line("HotKey Manager - Initialized");
	//MH_CreateHook((LPVOID)0x140761910, Memes, &inputLockOfAddr);
	//MH_EnableHook((LPVOID)0x140761910);

	//MH_CreateHook((LPVOID)0x14075ec70, Meme1, &menuOpenGetter);
	//MH_EnableHook((LPVOID)0x14075ec70);

	//MH_CreateHook((LPVOID)0x140762880, Meme2, &menuOpenSetter);
	//MH_EnableHook((LPVOID)0x140762880);
	//call(menuOpenSetter, 8, 0);

	//MH_CreateHook((LPVOID)AddVectoredExceptionHandler, addVeh, &addVehOgFun);
	//MH_EnableHook((LPVOID)AddVectoredExceptionHandler);

	//MH_CreateHook((LPVOID)0x140d9cd00, Memletto, &debugMemeOg);
	//MH_EnableHook((LPVOID)0x140d9cd00);
		
	//MH_CreateHook((LPVOID)0x1410a08e0, MemeHelp, &memeHelp);
	//MH_EnableHook((LPVOID)0x1410a08e0);
	if (hoodie_script::SprjMsgRepositoryImp::GameHasInstance())
	{
		hoodie_script::SprjMsgRepositoryImp helpMe = hoodie_script::SprjMsgRepositoryImp::GameGetInstance();
		std::wcout << L"LeMemeSS = " << helpMe.getWeaponName(2010000) << "\n";
	}
	hoodie_script::script_runtime::initializeHooks();
	return S_OK;
}

void attach()
{
	prepare_console();
	hoodie_script::logging::init();
	hoodie_script::logging::write_line("Attached HoodieScriptExtender");

	// Set up minhook
	if (MH_Initialize() != MH_OK) {
		hoodie_script::logging::write_line("Hook initialization failed");
	}
	else {
		hoodie_script::logging::write_line("Minhook set up");
	}

	CreateThread(nullptr, 0x1000, &init_thread, nullptr, 0, nullptr);
}

void detach()
{
	// TODO: keep track of all the hooks in a centralized place so we can roll them back in batch
	hoodie_script::GuiManager::Uninit();
	hoodie_script::script_runtime::deinitializeHooks();
	hoodie_script::logging::write_line("Detached HoodieScriptExtender");
	free_console();
}

void prepare_console() {
	if (GetConsoleWindow() != nullptr) {
		freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
	}
	else {
		AllocConsole();
		freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
	}
}

void free_console() {
	if (GetConsoleWindow() != nullptr) {
		FreeConsole();
	}
}

LONG WINAPI exception_handler(struct _EXCEPTION_POINTERS* exception) {
	PEXCEPTION_RECORD record = exception->ExceptionRecord;
	PCONTEXT context = exception->ContextRecord;
	char exception_text[EXCEPTION_STRING_SIZE];

	switch (record->ExceptionCode) {
	case EXCEPTION_ACCESS_VIOLATION:
		snprintf(
			exception_text,
			EXCEPTION_STRING_SIZE,
			"Access violation!\n\n"
			"Instruction at 0x%p\n"
			"attempted to %s\n"
			"memory at 0x%p\n\n"
			"Register dump:\n"
			"RAX = 0x%p\n" "RBX = 0x%p\n" "RCX = 0x%p\n" "RDX = 0x%p\n"
			"RSI = 0x%p\n" "RDI = 0x%p\n" "RBP = 0x%p\n" "RSP = 0x%p\n"
			"R8  = 0x%p\n" "R9  = 0x%p\n" "R10 = 0x%p\n" "R11 = 0x%p\n"
			"R12 = 0x%p\n" "R13 = 0x%p\n" "R14 = 0x%p\n" "R15 = 0x%p\n",
			record->ExceptionAddress,
			record->ExceptionInformation[0] ? "WRITE" : "READ",
			record->ExceptionInformation[1],
			context->Rax, context->Rbx, context->Rcx, context->Rdx,
			context->Rsi, context->Rdi, context->Rbp, context->Rsp,
			context->R8, context->R9, context->R10, context->R11,
			context->R12, context->R13, context->R14, context->R15
		);
		break;
	default:
		snprintf(
			exception_text,
			EXCEPTION_STRING_SIZE,
			"Caught unhandled exception\n"
			"Code: %x\n"
			"Address: %p",
			record->ExceptionCode,
			record->ExceptionAddress
		);
		break;
	}

	hoodie_script::logging::write_line(exception_text);
	MessageBoxA(NULL, exception_text, "Error Dump", MB_ICONERROR | MB_OK);
	return EXCEPTION_CONTINUE_SEARCH;
}