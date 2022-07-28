#include "pch.h"
#include "entry.h"
#include "vendor/DInput8/DInput8Proxy.h"

//DLL Entry function/
//It is called upon loading the dll and runs into the game's calling thread.
//It must return to resume the game's calling thread.
BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
	static HMODULE dinput8dll = nullptr;
	HMODULE chainModule = NULL;
	wchar_t chainPath[MAX_PATH];
	wchar_t dllPath[MAX_PATH];

	//Switch for logic during different DLL *events*
	switch (ul_reason_for_call) {
	//In case of the DLL being loaded into the game.
	case DLL_PROCESS_ATTACH:
		
		//This code handles DLL Chaining, it is disabled here but commented regardless.
		/*
		//Reads other dll's path from hoodiescript.ini
		GetPrivateProfileStringW(L"Misc", L"ChainloadDinput8dll", L"", chainPath, MAX_PATH, L".\\HoodieScript.ini");

		//If the wide string <chainPath> isn't null or empty proceed
		if (chainPath && wcscmp(chainPath, L""))
		{
			//Gets the game executable's path as wide string in <dllPath>
			GetCurrentDirectoryW(MAX_PATH, dllPath);
			//Concatenates <dllPath> with "\" (Escapes it with another "\")
			wcscat_s(dllPath, MAX_PATH, L"\\");
			//Concatenates <dllPath> with <chainPath>
			wcscat_s(dllPath, MAX_PATH, chainPath);
			//Load chained DLL from <dllPath> and write the module's pointer in <chainModule>
			chainModule = LoadLibraryW(dllPath);
			
			//If <chainModule> is not null, proceed.
			if (chainModule)
			{
				//Write the pointer of the chained module's DirectInput8Create function in <DirectInput8Create_fn>
				DirectInput8Create_fn = (DirectInput8Create_TYPE)GetProcAddress(chainModule, "DirectInput8Create");
			}
		}
		*/

		//If <chainModule> contains no pointer proceed.
		if (!chainModule)
		{
			//Just a wide string, long <MAX_PATH> defined in the windows headers
			wchar_t path[MAX_PATH];
			//Get system directory as a wide string and put it in <path>
			GetSystemDirectoryW(path, MAX_PATH);
			//Concatenate <path> with "\dinput8.dll" (the \ is escaped with \ obviously)
			wcscat_s(path, MAX_PATH, L"\\dinput8.dll");
			//load dinput8 from <path> and store the module's pointer in <dinput8dll>
			dinput8dll = LoadLibraryW(path);

			//If <chainModule> is not null, proceed. 
			if (dinput8dll)
			{
				//Write the pointer of the chained module's DirectInput8Create function in <DirectInput8Create_fn>
				DirectInput8Create_fn = (DirectInput8Create_TYPE)GetProcAddress(dinput8dll, "DirectInput8Create");
			}
		}
		//Runs the attach function, then breaks.
		attach();
		break;
	//In case of the DLL being unloaded from the game.
	case DLL_PROCESS_DETACH:
		//Runs the detach function, then breaks.
		detach();
		break;
	default:
		break;
	}
	return TRUE;
}

/// <summary>
/// Runs on the new thread started by the attach function. 
/// This function is not required to return in order to resume game execution.
/// </summary>
/// <param name="lpParam"></param>
/// <returns></returns>
DWORD WINAPI init_thread(void* lpParam)
{
	std::cout << "I am here to stay!" << std::endl;
	//Nope, not gonna return.
	while (true)
	{
		std::cout << "I am still here!" << std::endl;
		Sleep(5000);
	}

	//Lies, still not gonna return.
	return S_OK;
}

/// <summary>
/// Prepares and opens the console, the spawns a new thread and returns.
/// </summary>
void attach()
{
	//allocates the console and opens up the console
	prepare_console();

	//Creates a thread for your code to run, indipendently from the game.
	CreateThread(nullptr, 0x1000, &init_thread, nullptr, 0, nullptr);
}

/// <summary>
/// Closes the console and deallocates it.
/// </summary>
void detach()
{
	free_console();
}

/// <summary>
/// Allocates the console then opens it, or opens it in case it is already allocated.
/// </summary>
void prepare_console() {
	if (GetConsoleWindow() != nullptr) {
		//If the console window's pointer isn't null, simply open the console window.
		freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
	}
	else {
		//else, allocate it then open it.
		AllocConsole();
		freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
	}
}

/// <summary>
/// Deallocates the console if one is allocated, else fails silently.
/// </summary>
void free_console() {

	if (GetConsoleWindow() != nullptr) {
		FreeConsole();
	}
}