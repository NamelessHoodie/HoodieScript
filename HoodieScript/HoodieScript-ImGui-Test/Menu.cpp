#include "pch.h"
#include "Menu.h"

using namespace ImGui;

float test = 1;

//Addresses
const __int64 chr_ptr_address = 0x144768E78;
const __int64 hit_ptr_address = 0x144766C80;
const __int64 world_chr_man_dbg_ptr_address = 0x144768F98;

struct ChrFinder {
	__int64 vtable = 0x14284CC50;
	__int64 unk1 = 0;
	__int64 unk2 = 0;
	int result = 0;
};

typedef void(__thiscall* _getMAXIMOSENEMIGOS)(__int64 chr_ptr, ChrFinder* chr_finder_ptr, __int64 some_value);
_getMAXIMOSENEMIGOS getMAXIMOSENEMIGOS = (_getMAXIMOSENEMIGOS)0x1408D3240;

typedef char(__thiscall* _getChrIsOmission)(__int64 chr_ptr);
_getChrIsOmission getChrIsOmission = (_getChrIsOmission)0x140891290;

typedef char(__thiscall* _getChrIsEnable)(__int64 chr_ptr);
_getChrIsEnable getChrIsEnable = (_getChrIsEnable)0x1403B32E0;

typedef char(__thiscall* _getChrIsEnableDraw)(__int64 chr_ptr);
_getChrIsEnableDraw getChrIsEnableDraw = (_getChrIsEnableDraw)0x140864AD0;

typedef char(__thiscall* _switchAllNoUpdate)(__int64 some_ptr, int idx);
_switchAllNoUpdate switchAllNoUpdate = (_switchAllNoUpdate)0x1408D8750;

typedef char(__thiscall* _dbgChrInsPressEnterButtonListener)(__int64 this_ptr, int idx);
_dbgChrInsPressEnterButtonListener dbgChrInsPressEnterButtonListener = (_dbgChrInsPressEnterButtonListener)0x14088A700;

typedef __int64(__fastcall* _testFunc)(__int64 some_ptr, __int64 sth_ptr, int idx);
_testFunc testFunc = (_testFunc)0x14088B920;

typedef void(__fastcall* _getIdxForHitMtrlString)(unsigned int* result_ptr, int idx);
_getIdxForHitMtrlString getIdxForHitMtrlString = (_getIdxForHitMtrlString)0x140E23F50;

typedef wchar_t*(__fastcall* _getHitMtrlString)(unsigned int* hitMatIdx);
_getHitMtrlString getHitMtrlString = (_getHitMtrlString)0x140E23CD0;

typedef int(__fastcall* _getMapNameId)(__int64 some_ptr);
_getMapNameId getMapNameId = (_getMapNameId)0x14084F1F0;

typedef struct {
	wchar_t* ptr_to_string;
	char unknown[48];
} SillyBlob;

SillyBlob blob;

// Calling it like this is apparantly some leaky shit (or just wrong)
typedef __int64(__fastcall* _makeFancyHitNameString)(__int64 some_ptr, SillyBlob* blob);
_makeFancyHitNameString makeFancyHitNameString = (_makeFancyHitNameString)0x140850EC0;

typedef __int64(__fastcall* _getMapUidForSth)(__int64 some_ptr, int* uid);
_getMapUidForSth getMapUidForSth = (_getMapUidForSth)0x14084F220;

typedef wchar_t*(__fastcall* _getPartMsbName)(__int64 some_ptr);
_getPartMsbName getPartMsbName = (_getPartMsbName)0x14084F2F0;

typedef __int64(__fastcall* _getModelDrawParamFogIdForNpc)(__int64 some_ptr, __int64* fog_id);
_getModelDrawParamFogIdForNpc getModelDrawParamFogIdForNpc = (_getModelDrawParamFogIdForNpc)0x140881310;

typedef __int64(__fastcall* _getModelDrawParamLightIdForNpc)(__int64 some_ptr, __int64* light_id);
_getModelDrawParamLightIdForNpc getModelDrawParamLightIdForNpc = (_getModelDrawParamLightIdForNpc)0x1408817A0;

typedef int(__fastcall* _getSceneGparamEventId)(__int64 some_ptr, int idx);
_getSceneGparamEventId getSceneGparamEventId = (_getSceneGparamEventId)0x140E0AA10;

typedef int(__fastcall* _getEventEntityId)(__int64 some_ptr);
_getEventEntityId getEventEntityId = (_getEventEntityId)0x140E0A120;

typedef int(__fastcall* _getDisabledBonfireId)(__int64 some_ptr);
_getDisabledBonfireId getDisabledBonfireId = (_getDisabledBonfireId)0x14084F070;

typedef int(__fastcall* _getSomeShit)(__int64 some_ptr); //mimicry shit
_getSomeShit getSomeShit = (_getSomeShit)0x14084F1C0;

//////////////////////
typedef __int64(__fastcall* _getCollisionInfo)(__int64 some_ptr, signed int some_int, int some_int_aswell);
_getCollisionInfo getCollisionInfo = (_getCollisionInfo)0x140E07490;

typedef int(__fastcall* _getCollisionGroupNo)(__int64 some_ptr, char some_number, char some_number_too);
_getCollisionGroupNo getCollisionGroupNo = (_getCollisionGroupNo)0x14084EF00;


typedef __int64(__fastcall* _getModelDrawParamLightIdForCollision)(__int64 some_ptr, __int64* light_id);
_getModelDrawParamLightIdForCollision getModelDrawParamLightIdForCollision = (_getModelDrawParamLightIdForCollision)0x14084F150;

typedef __int64(__fastcall* _getModelDrawParamFogIdForCollision)(__int64 some_ptr, __int64* fog_id);
_getModelDrawParamFogIdForCollision getModelDrawParamFogIdForCollision = (_getModelDrawParamFogIdForCollision)0x14084F130;

typedef __int64(__fastcall* _getModelDrawParamScatterIdForCollision)(__int64 some_ptr, __int64* scatter_id);
_getModelDrawParamScatterIdForCollision getModelDrawParamScatterIdForCollision = (_getModelDrawParamScatterIdForCollision)0x14084F3A0;

typedef __int64(__fastcall* _getModelDrawParamEnvMapIdForCollision)(__int64 some_ptr, __int64* envmap_id);
_getModelDrawParamEnvMapIdForCollision getModelDrawParamEnvMapIdForCollision = (_getModelDrawParamEnvMapIdForCollision)0x14084F100;

typedef __int64(__fastcall* _testTest)(__int64 some_ptr, __int64 another_ptr, int idx);
_testTest testTest = (_testTest)0x140857CB0;

typedef int(__fastcall* _getNumLoadedLoHitPolygons)(__int64 some_ptr);
_getNumLoadedLoHitPolygons getNumLoadedLoHitPolygons = (_getNumLoadedLoHitPolygons)0x140857AB0;

typedef int(__fastcall* _getNumLoadedHiHitPolygons)(__int64 some_ptr);
_getNumLoadedHiHitPolygons getNumLoadedHiHitPolygons = (_getNumLoadedHiHitPolygons)0x140857A50;

BYTE mouse_patch[] = { 0x90, 0x90, 0x90, 0x90, 0x90 };

HANDLE hProcess;

DWORD GetProcId(const wchar_t* procname)
{
	PROCESSENTRY32W pe;
	HANDLE hSnap;
	pe.dwSize = sizeof(PROCESSENTRY32W);
	hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	if (Process32FirstW(hSnap, &pe)) {
		do {
			if (wcscmp(pe.szExeFile, procname) == 0) {
				break;
			}
		} while (Process32NextW(hSnap, &pe));
	}
	return pe.th32ProcessID;
}

BOOL BuildBitGroupString(unsigned int group, char* string)
{
	int bit_grouping = 0;
	unsigned int current_bit = 0x80000000;

	char* temp = string;
	int count = 0;

	while (true) {
		if (group & current_bit) {
			*temp = '\xE2';
			temp++;
			*temp = '\x96';
			temp++;
			*temp = '\xA0';
			temp++;
		} else {
			*temp = '\xE2';
			temp++;
			*temp = '\x96';
			temp++;
			*temp = '\xA1';
			temp++;
		}

		if (count == 7) {
			*temp = ' ';
			temp++;
			count = 0;
		} else {
			count++;
		}

		if (current_bit == 1)
			break;

		current_bit /= 2;
	}

	return 0;

	//for (int i = 0; i < 32; i++) {
	//	// Mind the gap
	//	if (!(i % 8) && i > 0) {
	//		string[i + bit_grouping] = ' ';
	//		bit_grouping++;
	//	}
	//		
	//	if (group & current_bit) {
	//		string[i + bit_grouping] = '1';
	//	}
	//	else {
	//		string[i + bit_grouping] = '0';
	//	}

	//	current_bit /= 2;
	//}
}

Menu::Menu()
{
	hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, GetProcId(L"DarkSoulsIII.exe"));
}

Menu::~Menu()
{
	CloseHandle(hProcess);
}

void Menu::Render()
{
	ImGui_ImplDX11_NewFrame();


	static bool no_titlebar = false;
	static bool no_border = true;
	static bool no_resize = false;
	static bool auto_resize = false;
	static bool no_move = false;
	static bool no_scrollbar = false;
	static bool no_collapse = false;
	static bool no_menu = true;
	static bool start_pos_set = false;

	ImVec4* colors = ImGui::GetStyle().Colors;
	colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
	colors[ImGuiCol_WindowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.83f);
	colors[ImGuiCol_ChildBg] = ImVec4(1.00f, 1.00f, 1.00f, 0.00f);
	colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
	colors[ImGuiCol_Border] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
	colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_FrameBg] = ImVec4(0.16f, 0.29f, 0.48f, 0.54f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
	colors[ImGuiCol_TitleBg] = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.16f, 0.29f, 0.48f, 1.00f);
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_MenuBarBg] = ImVec4(1.00f, 0.00f, 0.00f, 0.61f);
	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
	colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.16f, 0.29f, 0.48f, 0.54f);
	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
	colors[ImGuiCol_CheckMark] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_SliderGrab] = ImVec4(0.24f, 0.52f, 0.88f, 1.00f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_Button] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.06f, 0.53f, 0.98f, 1.00f);
	colors[ImGuiCol_Header] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_Separator] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
	colors[ImGuiCol_SeparatorHovered] = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
	colors[ImGuiCol_SeparatorActive] = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);
	colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.25f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
	colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
	colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
	colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
	colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
	colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
	
	ImGuiWindowFlags	window_flags = 0;
	if (no_titlebar)	window_flags |= ImGuiWindowFlags_NoTitleBar;
	if (no_resize)		window_flags |= ImGuiWindowFlags_NoResize;
	if (auto_resize)	window_flags |= ImGuiWindowFlags_AlwaysAutoResize;
	if (no_move)		window_flags |= ImGuiWindowFlags_NoMove;
	if (no_scrollbar)	window_flags |= ImGuiWindowFlags_NoScrollbar;
	if (no_collapse)	window_flags |= ImGuiWindowFlags_NoCollapse;
	if (!no_menu)		window_flags |= ImGuiWindowFlags_MenuBar;
	ImGui::SetNextWindowSize(ImVec2(450, 600), ImGuiCond_Once);
	if (!start_pos_set) { ImGui::SetNextWindowPos(ImVec2(25, 25)); start_pos_set = true; }
	//ImGui::GetIO().MouseDrawCursor = IsOpen;


	if (IsOpen)
	{
		BYTE test_byte;
		ReadProcessMemory(hProcess, (LPVOID)0x140EA8665, &test_byte, 1, NULL);

		//Re-Apply Patch if necessary
		if (test_byte != 0x90)
			WriteProcessMemory(hProcess, (LPVOID)0x140EA8665, mouse_patch, 5, NULL);

		ImGui::Begin("Knockoff Debug Menu", &IsOpen, window_flags);

		ImGui::PushItemWidth(ImGui::GetWindowWidth() * 0.65f);
		ImGui::PushItemWidth(-140);

		ImGui::Text("Kanjis: \xe2\x96\xa0\xe2\x89\xaasda\xe3\x80\x87\xe6\x97\xa5\xe6\x9c\xac\xe8\xaa\x9e (nihongo)");

		if (ImGui::CollapsingHeader("[Root]"))
		{
			if (ImGui::TreeNode("[GAME]"))
			{
				if (ImGui::TreeNode("[HIT INS]"))
				{
					RenderHitInsMenu();

					ImGui::TreePop();
				}

				if (ImGui::TreeNode("[CHR INS]"))
				{

					RenderChrInsMenu();

					ImGui::TreePop();
				}

				ImGui::TreePop();
			}

			if (ImGui::TreeNode("[RESOURCE]"))
			{

				ImGui::TreePop();
			}
		}

		/*if (ImGui::CollapsingHeader("MENU"))
		{
			if (ImGui::TreeNode("SUB MENU"))
			{
				ImGui::Text("Text Test");
				if (ImGui::Button("Button Test")) {}
				ImGui::Checkbox("CheckBox Test", &no_titlebar);
				ImGui::SliderFloat("Slider Test", &test, 1.0f, 100.0f);

				ImGui::TreePop();
			}
		}*/

		ImGui::End();
	}

	// Background Test
	/*ImVec2 dispSize = ImGui::GetIO().DisplaySize;
	if (dispSize.x > 0 && dispSize.y > 0)
	{
		ImGui::SetNextWindowPos(ImVec2(0, 0));
		ImGui::Begin("BCKGND", NULL, dispSize, 0.0f, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoBringToFrontOnFocus);
		ImGui::GetWindowDrawList()->AddText(ImVec2(0, 0), ImColor(1.0f, 1.0f, 1.0f, 1.0f), "Text in Background Layer");
		ImGui::End();
	}*/

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void Menu::RenderHitInsMenu()
{
	__int64 hit_ptr = 0;
	if (ReadProcessMemory(hProcess, (LPCVOID)hit_ptr_address, &hit_ptr, 8, NULL) && hit_ptr)
	{

		if (ImGui::TreeNode("[WORLD HIT MAN]"))
		{
			int ready_lo_num = 0;
			int ready_hi_num = 0;
			int max_num = 0;

			__int64 ptr_sth_hit = 0;

			ReadProcessMemory(hProcess, (LPCVOID)(hit_ptr + 0x17B8), &max_num, 4, NULL);
			ReadProcessMemory(hProcess, (LPCVOID)(hit_ptr + 0x17BC), &ready_hi_num, 4, NULL);
			ReadProcessMemory(hProcess, (LPCVOID)(hit_ptr + 0x17C0), &ready_lo_num, 4, NULL);
			ReadProcessMemory(hProcess, (LPCVOID)(hit_ptr + 0x17D8), &ptr_sth_hit, 8, NULL);

			ImGui::Text("%04d/%04d/%04d<ReadyHiNum/ReadyLoNum/MaxNum", ready_hi_num, ready_lo_num, max_num);

			int map_uid = 0;

			if (ptr_sth_hit) {
				getMapUidForSth(ptr_sth_hit + 0x10, &map_uid);
				wchar_t* hit_name = getPartMsbName(ptr_sth_hit + 0x10);

				char hit_name_string[128];

				int pos = 0;
				char read_char;
				do {
					read_char = (char)hit_name[pos];
					hit_name_string[pos] = read_char;
					pos++;
				} while (read_char);

				ImGui::Text("\xe2\x89\xaa""A%02dB%d:%s\xe2\x89\xab""CurrentHit", map_uid >> 24 & 0xFF, map_uid >> 16 & 0xFF, hit_name_string);
			}
			else
			{
				ImGui::Text("\xe2\x89\xaa""----\xe2\x89\xab""CurrentHit");
			}

			bool is_disp_lo_hit = 0;
			bool is_disp_hi_hit = 0;
			bool is_disp_obj_hit_dbg = 0;
			bool is_disp_chr_proxy_hit = 0;
			bool is_disp_chr_ragdoll_hit = 0;
			bool is_disp_chr_hit_on_sel = 0;
			bool group_debug_valid_hits = 0;
			bool active_group_debug_valid_hits = 0;
			bool backread_group_debug_valid_hits = 0;
			bool use_display_buffer_lo_hit = 0;
			bool use_display_buffer_hi_hit = 0;
			bool is_connect_hit_valid = 0;
			bool enable_adjacent_hi_hits = 0;

			__int64 world_chr_man_dbg_ptr = 0;

			ReadProcessMemory(hProcess, (LPCVOID)0x144766C6C, &is_disp_lo_hit, 1, NULL);
			ReadProcessMemory(hProcess, (LPCVOID)0x144766C6D, &is_disp_hi_hit, 1, NULL);
			ReadProcessMemory(hProcess, (LPCVOID)0x144766C6E, &is_disp_obj_hit_dbg, 1, NULL);
			ReadProcessMemory(hProcess, (LPCVOID)0x144766C6F, &is_disp_chr_ragdoll_hit, 1, NULL);
			ReadProcessMemory(hProcess, (LPCVOID)0x144766C70, &is_disp_chr_hit_on_sel, 1, NULL);
			ReadProcessMemory(hProcess, (LPCVOID)0x144766C71, &group_debug_valid_hits, 1, NULL);
			ReadProcessMemory(hProcess, (LPCVOID)0x144766C72, &active_group_debug_valid_hits, 1, NULL);
			ReadProcessMemory(hProcess, (LPCVOID)0x144766C73, &backread_group_debug_valid_hits, 1, NULL);

			ReadProcessMemory(hProcess, (LPCVOID)0x144583078, &is_connect_hit_valid, 1, NULL);
			ReadProcessMemory(hProcess, (LPCVOID)0x144583079, &enable_adjacent_hi_hits, 1, NULL);
			ReadProcessMemory(hProcess, (LPCVOID)0x14458307A, &use_display_buffer_lo_hit, 1, NULL);
			ReadProcessMemory(hProcess, (LPCVOID)0x14458307B, &use_display_buffer_hi_hit, 1, NULL);

			ReadProcessMemory(hProcess, (LPCVOID)world_chr_man_dbg_ptr_address, &world_chr_man_dbg_ptr, 8, NULL);

			if (ImGui::Checkbox("IsDispLoHitDebug", &is_disp_lo_hit))
			{
				WriteProcessMemory(hProcess, (LPVOID)0x144766C6C, &is_disp_lo_hit, 1, NULL);
			}

			if (ImGui::Checkbox("IsDispHiHitDebug", &is_disp_hi_hit))
			{
				WriteProcessMemory(hProcess, (LPVOID)0x144766C6D, &is_disp_hi_hit, 1, NULL);
			}

			if (ImGui::Checkbox("IsDispActiveHitDispGroupDbg", &group_debug_valid_hits))
			{
				WriteProcessMemory(hProcess, (LPVOID)0x144766C71, &group_debug_valid_hits, 1, NULL);
			}

			if (ImGui::Checkbox("IsDispActiveHitActivateGroupDbg", &active_group_debug_valid_hits))
			{
				WriteProcessMemory(hProcess, (LPVOID)0x144766C72, &active_group_debug_valid_hits, 1, NULL);
			}

			if (ImGui::Checkbox("IsDispActiveHitBackreadGroupDbg", &backread_group_debug_valid_hits))
			{
				WriteProcessMemory(hProcess, (LPVOID)0x144766C73, &backread_group_debug_valid_hits, 1, NULL);
			}

			if (ImGui::Checkbox("IsDispObjHitDebug", &is_disp_obj_hit_dbg))
			{
				WriteProcessMemory(hProcess, (LPVOID)0x144766C6E, &is_disp_obj_hit_dbg, 1, NULL);
			}

			if (world_chr_man_dbg_ptr) {
				ReadProcessMemory(hProcess, (LPCVOID)(world_chr_man_dbg_ptr + 0x66), &is_disp_chr_proxy_hit, 1, NULL);

				if (ImGui::Checkbox("IsDispChrProxyHitDebug", &is_disp_chr_proxy_hit))
				{
					WriteProcessMemory(hProcess, (LPVOID)(world_chr_man_dbg_ptr + 0x66), &is_disp_chr_proxy_hit, 1, NULL);
				}
			}

			if (ImGui::Checkbox("IsDispChrRagdollHitDebug", &is_disp_chr_ragdoll_hit))
			{
				WriteProcessMemory(hProcess, (LPVOID)0x144766C6F, &is_disp_chr_ragdoll_hit, 1, NULL);
			}

			if (ImGui::Checkbox("IsDispChrOnSelectedHitDebug", &is_disp_chr_hit_on_sel))
			{
				WriteProcessMemory(hProcess, (LPVOID)0x144766C70, &is_disp_chr_hit_on_sel, 1, NULL);
			}

			ImGui::SetNextItemWidth(200);
			const char* items[] = { "Default", "Random Color", "Angle", "Material" };
			static int item_current = 0;
			if (ImGui::Combo("Display Mode", &item_current, items, IM_ARRAYSIZE(items)))
			{
				WriteProcessMemory(hProcess, (LPVOID)0x144766C74, &item_current, 4, NULL);
			}

			int some_idx = 0;
			unsigned int result = 0;

			ReadProcessMemory(hProcess, (LPCVOID)0x144766C78, &some_idx, 4, NULL);

			getIdxForHitMtrlString(&result, some_idx);

			const wchar_t* hit_mtrl_stringW;

			char floor_mat_name[128];

			hit_mtrl_stringW = getHitMtrlString(&result);

			int pos = 0;
			char read_char;
			do {
				read_char = (char)hit_mtrl_stringW[pos];
				floor_mat_name[pos] = read_char;
				pos++;
			} while (read_char);

			ImGui::Text("\xe2\x89\xaa""%d:%s\xe2\x89\xab""Material ID", some_idx, floor_mat_name);

			if (ImGui::Checkbox("Use Display Buffer for Lo-Hit Draw", &use_display_buffer_lo_hit))
			{
				WriteProcessMemory(hProcess, (LPVOID)0x14458307A, &use_display_buffer_lo_hit, 1, NULL);
			}

			if (ImGui::Checkbox("Use Display Buffer for Hi-Hit Draw", &use_display_buffer_hi_hit))
			{
				WriteProcessMemory(hProcess, (LPVOID)0x14458307B, &use_display_buffer_hi_hit, 1, NULL);
			}

			if (ImGui::Checkbox("IsConnectHitValid", &is_connect_hit_valid))
			{
				WriteProcessMemory(hProcess, (LPVOID)0x144583078, &is_connect_hit_valid, 1, NULL);
			}

			if (ImGui::Checkbox("Enable Adjacent Hi-Hit", &enable_adjacent_hi_hits))
			{
				WriteProcessMemory(hProcess, (LPVOID)0x144583079, &enable_adjacent_hi_hits, 1, NULL);
			}

			ImGui::Text("Total Number of Loaded Lo-Hit Polygons: %d", getNumLoadedLoHitPolygons(hit_ptr));
			ImGui::Text("Total Number of Loaded Hi-Hit Polygons: %d", getNumLoadedHiHitPolygons(hit_ptr));

			ImGui::TreePop();
		}

		RenderHitInsWorldBlockHit(hit_ptr);

		int num_maps = 0;
		__int64 map_hit_ptr = 0;

		if (ReadProcessMemory(hProcess, (LPCVOID)(hit_ptr + 0x14), &num_maps, 4, NULL) && ReadProcessMemory(hProcess, (LPCVOID)(hit_ptr + 0x18), &map_hit_ptr, 8, NULL))
		{
			for (int i = 0; i < num_maps; i++) 
			{
				int num_blocks = 0;
				__int64 map_hit_ptr2 = 0;
				__int64 map_info_sth_ptr = 0;
				unsigned int area_id = 0;

				if (ReadProcessMemory(hProcess, (LPCVOID)(map_hit_ptr + 8), &map_info_sth_ptr, 8, NULL))
				{
					ReadProcessMemory(hProcess, (LPCVOID)(map_info_sth_ptr + 8), &area_id, 4, NULL);
				}

				// I don't know where to get the block id, so it will remain 0 (maybe it's part of the map id and I have this all wrong)

				if (ReadProcessMemory(hProcess, (LPCVOID)(map_hit_ptr + 0x10), &num_blocks, 4, NULL) && ReadProcessMemory(hProcess, (LPCVOID)(map_hit_ptr + 0x18), &map_hit_ptr2, 8, NULL))
				{
					for (int j = 0; j < num_blocks; j++) 
					{
						int num_cols = 0;
						__int64 col_ptr = 0;

						

						if (ReadProcessMemory(hProcess, (LPCVOID)(map_hit_ptr2 + 0x7C), &num_cols, 4, NULL) && ReadProcessMemory(hProcess, (LPCVOID)(map_hit_ptr2 + 0x80), &col_ptr, 8, NULL))
						{
							//ImGui::Text("%llx", map_hit_ptr2);
							for (int k = 0; k < num_cols; k++) 
							{
								__int64 col_msb_ptr = 0;

								if (ReadProcessMemory(hProcess, (LPCVOID)(col_ptr + 0x30), &col_msb_ptr, 8, NULL)) {
									__int64 col_msb_name_ptr = 0;
									__int64 col_msb_path_ptr = 0;

									if (ReadProcessMemory(hProcess, (LPCVOID)col_msb_ptr, &col_msb_name_ptr, 8, NULL) && ReadProcessMemory(hProcess, (LPCVOID)(col_msb_ptr + 0x10), &col_msb_path_ptr, 8, NULL)) {
										int name_length = col_msb_path_ptr - col_msb_name_ptr;

										wchar_t col_nameW[64];
										//ImGui::Text("%d of %d, %llx, %llx, %llx, %d", k, num_cols, col_ptr, col_msb_name_ptr, col_msb_path_ptr, name_length);
										ReadProcessMemory(hProcess, (LPCVOID)col_msb_name_ptr, col_nameW, name_length, NULL);

										char col_name[64];

										int pos = 0;
										char read_char;
										do {
											read_char = (char)col_nameW[pos];
											col_name[pos] = read_char;
											pos++;
										} while (read_char);

										char col_name_new[128];

										sprintf_s(col_name_new, "A%02dB%d:%s", area_id >> 24, 0, col_name);

										char lo_res_state = 0;
										char lo_req_set_res_state = 0;
										short lo_is_target_ready = 0;
										float lo_res_state_time = 0.0f;

										char hi_res_state = 0;
										char hi_req_set_res_state = 0;
										short hi_is_target_ready = 0;
										float hi_res_state_time = 0.0f;

										char backread_state = 0;
										char target_backread_state = 0;
										char debug_display_flag = 0;

										ReadProcessMemory(hProcess, (LPCVOID)(col_ptr + 0x100), &lo_res_state, 1, NULL);
										ReadProcessMemory(hProcess, (LPCVOID)(col_ptr + 0x101), &lo_req_set_res_state, 1, NULL);
										ReadProcessMemory(hProcess, (LPCVOID)(col_ptr + 0x102), &lo_is_target_ready, 2, NULL);
										ReadProcessMemory(hProcess, (LPCVOID)(col_ptr + 0x104), &lo_res_state_time, 4, NULL);
										ReadProcessMemory(hProcess, (LPCVOID)(col_ptr + 0x128), &hi_res_state, 1, NULL);
										ReadProcessMemory(hProcess, (LPCVOID)(col_ptr + 0x129), &hi_req_set_res_state, 1, NULL);
										ReadProcessMemory(hProcess, (LPCVOID)(col_ptr + 0x12A), &hi_is_target_ready, 2, NULL);
										ReadProcessMemory(hProcess, (LPCVOID)(col_ptr + 0x12C), &hi_res_state_time, 4, NULL);

										ReadProcessMemory(hProcess, (LPCVOID)(col_ptr + 0x145), &backread_state, 1, NULL);
										ReadProcessMemory(hProcess, (LPCVOID)(col_ptr + 0x146), &target_backread_state, 1, NULL);
										ReadProcessMemory(hProcess, (LPCVOID)(col_ptr + 0x147), &debug_display_flag, 1, NULL);

										bool is_disp_aabb = debug_display_flag & 1;
										bool is_disp_lohit_rigid = debug_display_flag & 2;
										bool is_disp_hihit_rigid = debug_display_flag & 4;

										lo_is_target_ready &= 1;
										hi_is_target_ready &= 1;

										unsigned int drawgroups[8];
										unsigned int dispgroups[8];
										unsigned int navigroups[8];

										ReadProcessMemory(hProcess, (LPVOID)(col_ptr + 0x5C), drawgroups, 32, NULL);
										ReadProcessMemory(hProcess, (LPVOID)(col_ptr + 0x7C), dispgroups, 32, NULL);
										ReadProcessMemory(hProcess, (LPVOID)(col_ptr + 0xBC), navigroups, 32, NULL);

										if (lo_is_target_ready && hi_is_target_ready) {
											ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.4f, 1.0f, 0.4f, 1.0f));
										}
										else if (lo_is_target_ready) {
											ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 0.4f, 1.0f));
										}
										else {
											ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.4f, 0.4f, 1.0f));
										}

										if (ImGui::TreeNode(col_name_new))
										{
											ImGui::PopStyleColor();

											if (ImGui::IsItemHovered()) {
												debug_display_flag |= 8;
												WriteProcessMemory(hProcess, (LPVOID)(col_ptr + 0x147), &debug_display_flag, 1, NULL);
											}

											if (ImGui::TreeNode("[HIT-INFO]"))
											{
												static char bit_string[100];

												for (int l = 0; l < 8; l++) {
													BuildBitGroupString(drawgroups[l], bit_string);
													ImGui::Text("DrawGroup> %s", bit_string);
												}

												for (int l = 0; l < 8; l++) {
													BuildBitGroupString(dispgroups[l], bit_string);
													ImGui::Text("DispGroup> %s", bit_string);
												}

												for (int l = 0; l < 8; l++) {
													BuildBitGroupString(navigroups[l], bit_string);
													ImGui::Text("NaviGroup> %s", bit_string);
												}

												__int64 light_id = 0;
												__int64 fog_id = 0;
												__int64 scatter_id = 0;
												__int64 envmap_id = 0;

												ImGui::Text("ModelDrawParam> Light\xe2\x89\xaa""%d\xe2\x89\xab"" Fog\xe2\x89\xaa""%d\xe2\x89\xab"" Scattering\xe2\x89\xaa""%d\xe2\x89\xab"" Envmap\xe2\x89\xaa""%d\xe2\x89\xab", getModelDrawParamLightIdForCollision(col_ptr + 0x10, &light_id) >> 32, getModelDrawParamFogIdForCollision(col_ptr + 0x10, &fog_id) >> 32, getModelDrawParamScatterIdForCollision(col_ptr + 0x10, &scatter_id) >> 32, getModelDrawParamEnvMapIdForCollision(col_ptr + 0x10, &envmap_id) >> 32);
												ImGui::Text("SceneGparam EventID[%d][%d][%d][%d]", getSceneGparamEventId(col_ptr + 0x10, 1), getSceneGparamEventId(col_ptr + 0x10, 2), getSceneGparamEventId(col_ptr + 0x10, 3), getSceneGparamEventId(col_ptr + 0x10, 4));

												__int64 some_ptr = 0;
												int some_int = 0;

												if (ReadProcessMemory(hProcess, (LPCVOID)(col_ptr + 0x50), &some_ptr, 8, NULL) && ReadProcessMemory(hProcess, (LPCVOID)(col_ptr + 0x58), &some_int, 2, NULL))
												{
													__int64 some_result_ptr = getCollisionInfo(some_ptr, 5, some_int);
													int result = 0;

													if (ReadProcessMemory(hProcess, (LPCVOID)(some_result_ptr + 0xB8), &some_result_ptr, 8, NULL))
													{
														if (ReadProcessMemory(hProcess, (LPCVOID)some_result_ptr, &result, 1, NULL))
														{
															ImGui::Text("LoGroupNo\xe2\x89\xaa""%02d\xe2\x89\xab"" MidGroupNo\xe2\x89\xaa""%02d\xe2\x89\xab"" HiGroupNo\xe2\x89\xaa""%02d\xe2\x89\xab"" Type\xe2\x89\xaa""%02d\xe2\x89\xab""<CollisionInfo", getCollisionGroupNo(col_ptr + 0x10, 1, 0), getCollisionGroupNo(col_ptr + 0x10, 1, 1), getCollisionGroupNo(col_ptr + 0x10, 0, 0), result);
															
														}

														int vagrant_id1 = 0;
														int vagrant_id2 = 0;
														int vagrant_id3 = 0;

														if (ReadProcessMemory(hProcess, (LPCVOID)(some_result_ptr + 0x18), &vagrant_id1, 4, NULL) && ReadProcessMemory(hProcess, (LPCVOID)(some_result_ptr + 0x1C), &vagrant_id2, 4, NULL) && ReadProcessMemory(hProcess, (LPCVOID)(some_result_ptr + 0x20), &vagrant_id3, 4, NULL))
														{
															ImGui::Text("[%04d][%04d][%04d]<VagrantEntityId", vagrant_id1, vagrant_id2, vagrant_id3);
														}
													}
												}

												ImGui::TreePop();
											}

											if (ImGui::TreeNode("[LO-HIT RES]")) 
											{
												ImGui::Text("IsTargetReady:%d ResState:%d ReqSetResState:%d ResStateTime:%0.3f", lo_is_target_ready, lo_res_state, lo_req_set_res_state, lo_res_state_time);

												ImGui::TreePop();
											}

											if (ImGui::TreeNode("[HI-HIT RES]"))
											{
												ImGui::Text("IsTargetReady:%d ResState:%d ReqSetResState:%d ResStateTime:%0.3f", hi_is_target_ready, hi_res_state, hi_req_set_res_state, hi_res_state_time);

												ImGui::TreePop();
											}

											if (ImGui::Checkbox("IsDispAabb", &is_disp_aabb))
											{
												if (is_disp_aabb) {
													debug_display_flag |= 1;
												}
												else {
													debug_display_flag &= 0xFE;
												}

												WriteProcessMemory(hProcess, (LPVOID)(col_ptr + 0x147), &debug_display_flag, 1, NULL);
											}

											if (ImGui::Checkbox("IsDispLoHitRigid", &is_disp_lohit_rigid))
											{
												if (is_disp_lohit_rigid) {
													debug_display_flag |= 2;
												}
												else {
													debug_display_flag &= 0xFD;
												}

												WriteProcessMemory(hProcess, (LPVOID)(col_ptr + 0x147), &debug_display_flag, 1, NULL);
											}

											if (ImGui::Checkbox("IsDispHiHitRigid", &is_disp_hihit_rigid))
											{
												if (is_disp_hihit_rigid) {
													debug_display_flag |= 4;
												}
												else {
													debug_display_flag &= 0xFB;
												}

												WriteProcessMemory(hProcess, (LPVOID)(col_ptr + 0x147), &debug_display_flag, 1, NULL);
											}

											ImGui::Text("MapNameId: %d", getMapNameId(col_ptr + 0x10));
											ImGui::Text("DisabledBonfireId: %d", getDisabledBonfireId(col_ptr + 0x10));
											ImGui::Text("MapMimicryEstablishmentParamId: %d", getSomeShit(col_ptr + 0x10));

											ImGui::TreePop();
										}
										else 
										{
											ImGui::PopStyleColor();

											if (ImGui::IsItemHovered()) {
												debug_display_flag |= 8;
												WriteProcessMemory(hProcess, (LPVOID)(col_ptr + 0x147), &debug_display_flag, 1, NULL);
											}

										}
									}
								}
								col_ptr += 0x148;
							}
						}
						map_hit_ptr2 += 0xA8;
					}
				}
				map_hit_ptr += 0x20;
			}
		}
	}


}

void Menu::RenderHitInsWorldBlockHit(__int64 hit_ptr)
{
	int num_maps = 0;

	if (ImGui::TreeNode("[WorldBlockHit]"))
	{
		if (ReadProcessMemory(hProcess, (LPCVOID)(hit_ptr + 0x20), &num_maps, 4, NULL))
		{
			if (num_maps)
			{
				__int64 some_hit_ptr = 0;

				if (ReadProcessMemory(hProcess, (LPCVOID)(hit_ptr + 0x28), &some_hit_ptr, 8, NULL))
				{
					int count = 0;
					while (count < num_maps)
					{
						__int64 map_sth_ptr = 0;

						if (ReadProcessMemory(hProcess, (LPCVOID)(some_hit_ptr + 8), &map_sth_ptr, 8, NULL))
						{
							unsigned int map_uid = 0;

							if (ReadProcessMemory(hProcess, (LPCVOID)(map_sth_ptr + 8), &map_uid, 4, NULL))
							{
								char map_name[32];

								sprintf_s(map_name, "[m%02d_%02d_%02d_%02d]", map_uid >> 24, map_uid >> 16 & 0xFF, map_uid >> 8 & 0xFF, map_uid & 0xFF);

								if (ImGui::TreeNode(map_name))
								{
									unsigned int dispgroups[8];
									unsigned int navigroups[8];
									unsigned int backgroups[8];

									bool lock_cam_slot_number = false;

									ReadProcessMemory(hProcess, (LPVOID)(some_hit_ptr + 0x18), dispgroups, 32, NULL);
									ReadProcessMemory(hProcess, (LPVOID)(some_hit_ptr + 0x38), navigroups, 32, NULL);
									ReadProcessMemory(hProcess, (LPVOID)(some_hit_ptr + 0x58), backgroups, 32, NULL);

									ReadProcessMemory(hProcess, (LPVOID)(some_hit_ptr + 0x98), &lock_cam_slot_number, 1, NULL);
									
									static char bit_string[100];

									for (int k = 0; k < 8; k++) {
										BuildBitGroupString(dispgroups[k], bit_string);
										ImGui::Text("DispGroup> %s", bit_string);
									}

									for (int k = 0; k < 8; k++) {
										BuildBitGroupString(navigroups[k], bit_string);
										ImGui::Text("NaviGroup> %s", bit_string);
									}

									for (int k = 0; k < 8; k++) {
										BuildBitGroupString(backgroups[k], bit_string);
										ImGui::Text("BackGroup> %s", bit_string);
									}

									if (ImGui::Checkbox("Lock Camera Slot Number", &lock_cam_slot_number))
									{
										WriteProcessMemory(hProcess, (LPVOID)(some_hit_ptr + 0x98), &lock_cam_slot_number, 1, NULL);
									}

									//TODO MapStudio Export

									ImGui::TreePop();
								}
							}
						}

						some_hit_ptr += 0xA8;
						count++;
					}
				}

			}

		}

		ImGui::TreePop();
	}
}

void Menu::RenderChrInsMenu()
{
	static __int64 chr_ptr = 0;

	if (ReadProcessMemory(hProcess, (LPCVOID)chr_ptr_address, &chr_ptr, 8, NULL) && chr_ptr)
	{
		RenderWorldChrMan(chr_ptr);
		RenderChrDbg();
	}
}

void Menu::RenderWorldChrMan(__int64 chr_ptr)
{
	if (ImGui::TreeNode("[WORLD CHR MAN]"))
	{
		__int64 chr_ptr_inter = 0;
		int map_num = 0;

		ReadProcessMemory(hProcess, (LPVOID)(chr_ptr + 0xC0), &map_num, 4, NULL);

		for (int i = 0; i < map_num; i++) {
			
			if (ReadProcessMemory(hProcess, (LPVOID)(chr_ptr + 0xC8 + i * 8), &chr_ptr_inter, 8, NULL)) 
			{
				if (chr_ptr_inter)
				{
					unsigned int chr_num = 0;
					__int64 map_sth_ptr = 0;
					unsigned int map_id = 0;
					ReadProcessMemory(hProcess, (LPVOID)(chr_ptr_inter + 0x80), &chr_num, 4, NULL);
					
					if (chr_num)
					{
						if (ReadProcessMemory(hProcess, (LPVOID)(chr_ptr_inter + 8), &map_sth_ptr, 8, NULL))
						{
							ReadProcessMemory(hProcess, (LPVOID)(map_sth_ptr + 8), &map_id, 4, NULL);
						
							char map_name[32];
							sprintf_s(map_name, "[m%02d_%02d_%02d_%02d](%d)", map_id >> 24, map_id >> 16 & 0xFF, map_id >> 8 & 0xFF, map_id & 0xFF, chr_num + 1);

							if (ImGui::TreeNode(map_name))
							{
								if (ReadProcessMemory(hProcess, (LPVOID)(chr_ptr_inter + 0x88), &chr_ptr_inter, 8, NULL)) 
								{
									
									for (unsigned j = 0; j < chr_num; j++) {

										__int64 enemy_base = 0;
										__int64 enemy_ptr_inter = 0;
										__int64 enemy_ptr = 0;

										if (ReadProcessMemory(hProcess, (LPVOID)(chr_ptr_inter + j * 0x38), &enemy_base, 8, NULL))
										{
											RenderWorldChrManChrEntry(enemy_base, false);

											/*if (ReadProcessMemory(hProcess, (LPVOID)(enemy_base + 0x1F90), &enemy_ptr_inter, 8, NULL))
											{
												if (ReadProcessMemory(hProcess, (LPVOID)(enemy_ptr_inter + 0x18), &enemy_ptr, 8, NULL))
												{
													
													char enemy_name[32];
													char read_char;
													int count = 0;
													do {
														ReadProcessMemory(hProcess, (LPVOID)(enemy_ptr + 0x130 + count * 2), &read_char, 1, NULL);
														enemy_name[count] = read_char;
														count++;
													} while (read_char);

													__int64 enemy_ptr_something = 0;
													char enemy_isLoaded = 0;
													
													ReadProcessMemory(hProcess, (LPVOID)(enemy_base + 0x30), &enemy_ptr_something, 8, NULL);
													ReadProcessMemory(hProcess, (LPVOID)(enemy_ptr_something + 0x84), &enemy_isLoaded, 1, NULL);

													if (enemy_isLoaded) {
														ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.4f, 1.4f, 0.4f, 1.0f));
													}
													else {
														ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.4f, 0.4f, 1.0f));
													}

													if (ImGui::TreeNode(enemy_name))
													{
														ImGui::PopStyleColor();

														static int enemy_hp = 0;
														static int enemy_hp_max = 0;
														static int enemy_mp = 0;
														static int enemy_mp_max = 0;
														static int enemy_stamina = 0;
														static int enemy_stamina_max = 0;

														static bool enemy_noHit = false;
														static bool enemy_noAttack = false;
														static bool enemy_noMove = false;
														static bool enemy_noGoodsConsume = false;
														static bool enemy_noUpdate = false;
														static bool enemy_disableGravity = false;
														static bool enemy_invalidateTAE = false;

														static char enemy_flags1 = 0;
														static char enemy_flags2 = 0;
														static char enemy_flags3 = 0;
														static char enemy_flags4 = 0;
														static char enemy_flags5 = 0;

														ReadProcessMemory(hProcess, (LPVOID)(enemy_base + 0x1EE8), &enemy_flags1, 1, NULL);
														ReadProcessMemory(hProcess, (LPVOID)(enemy_base + 0x1EE9), &enemy_flags2, 1, NULL);
														ReadProcessMemory(hProcess, (LPVOID)(enemy_base + 0x1EEA), &enemy_flags3, 1, NULL);
														ReadProcessMemory(hProcess, (LPVOID)(enemy_base + 0x1A08), &enemy_flags4, 1, NULL);

														__int64 enemy_flags5_inter = 0;

														ReadProcessMemory(hProcess, (LPVOID)(enemy_base + 0x50), &enemy_flags5_inter, 1, NULL);
														ReadProcessMemory(hProcess, (LPVOID)(enemy_flags5_inter + 0x48), &enemy_flags5_inter, 1, NULL);
														ReadProcessMemory(hProcess, (LPVOID)(enemy_flags5_inter + 0x108), &enemy_flags5, 1, NULL);

														ReadProcessMemory(hProcess, (LPVOID)(enemy_ptr + 0xD8), &enemy_hp, 4, NULL);
														ReadProcessMemory(hProcess, (LPVOID)(enemy_ptr + 0xDC), &enemy_hp_max, 4, NULL);
														ReadProcessMemory(hProcess, (LPVOID)(enemy_ptr + 0xE4), &enemy_mp, 4, NULL);
														ReadProcessMemory(hProcess, (LPVOID)(enemy_ptr + 0xE8), &enemy_mp_max, 4, NULL);
														ReadProcessMemory(hProcess, (LPVOID)(enemy_ptr + 0xF0), &enemy_stamina, 4, NULL);
														ReadProcessMemory(hProcess, (LPVOID)(enemy_ptr + 0xF4), &enemy_stamina_max, 4, NULL);


														enemy_noHit = enemy_flags1 >> 5 & 1;
														enemy_noAttack = enemy_flags1 >> 6 & 1;
														enemy_noMove = enemy_flags1 >> 7 & 1;
														enemy_noGoodsConsume = enemy_flags3 >> 3 & 1;
														enemy_noUpdate = enemy_flags2 >> 3 & 1;
														enemy_disableGravity = enemy_flags4 >> 6 & 1;
														enemy_invalidateTAE = enemy_flags5 >> 5 & 1;

														if (ImGui::Checkbox("No Hit", &enemy_noHit))
														{
															if (enemy_noHit) {
																enemy_flags1 |= 0x20;
															}
															else {
																enemy_flags1 &= 0xDF;
															}

															WriteProcessMemory(hProcess, (LPVOID)(enemy_base + 0x1EE8), &enemy_flags1, 1, NULL);
														}

														if (ImGui::Checkbox("No Attack", &enemy_noAttack))
														{
															if (enemy_noAttack) {
																enemy_flags1 |= 0x40;
															}
															else {
																enemy_flags1 &= 0xBF;
															}

															WriteProcessMemory(hProcess, (LPVOID)(enemy_base + 0x1EE8), &enemy_flags1, 1, NULL);
														}

														if (ImGui::Checkbox("No Move", &enemy_noMove))
														{
															if (enemy_noMove) {
																enemy_flags1 |= 0x80;
															}
															else {
																enemy_flags1 &= 0x7F;
															}

															WriteProcessMemory(hProcess, (LPVOID)(enemy_base + 0x1EE8), &enemy_flags1, 1, NULL);
														}

														if (ImGui::Checkbox("No Goods Consume", &enemy_noGoodsConsume))
														{
															if (enemy_noGoodsConsume) {
																enemy_flags3 |= 0x8;
															}
															else {
																enemy_flags3 &= 0xF7;
															}

															WriteProcessMemory(hProcess, (LPVOID)(enemy_base + 0x1EEA), &enemy_flags3, 1, NULL);
														}

														if (ImGui::Checkbox("No Update", &enemy_noUpdate))
														{
															if (enemy_noUpdate) {
																enemy_flags2 |= 0x8;
															}
															else {
																enemy_flags2 &= 0xF7;
															}

															WriteProcessMemory(hProcess, (LPVOID)(enemy_base + 0x1EE9), &enemy_flags2, 1, NULL);
														}

														if (ImGui::Checkbox("Disable Gravity", &enemy_disableGravity))
														{
															if (enemy_disableGravity) {
																enemy_flags4 |= 0x40;
															}
															else {
																enemy_flags4 &= 0xBF;
															}

															WriteProcessMemory(hProcess, (LPVOID)(enemy_base + 0x1A08), &enemy_flags4, 1, NULL);
														}

														ImGui::SameLine();

														if (ImGui::Checkbox("Invalidate TAE", &enemy_invalidateTAE))
														{
															if (enemy_invalidateTAE) {
																enemy_flags5 |= 0x20;
															}
															else {
																enemy_flags5 &= 0xDF;
															}

															WriteProcessMemory(hProcess, (LPVOID)(enemy_flags5_inter + 0x108), &enemy_flags5, 1, NULL);
														}

														if (ImGui::Button("Switch Control Player"))
														{
															dbgChrInsPressEnterButtonListener(enemy_base, 0);
														}

														if (ImGui::Button("Return Control Player"))
														{
															dbgChrInsPressEnterButtonListener(enemy_base, 40);
														}

														if (ImGui::Button("Move Position to this pos"))
														{
															dbgChrInsPressEnterButtonListener(enemy_base, 42);
														}

														if (ImGui::Button("Reset Position at InitPos"))
														{
															dbgChrInsPressEnterButtonListener(enemy_base, 41);
														}

														if (ImGui::Button("Export MapStudio"))
														{
															dbgChrInsPressEnterButtonListener(enemy_base, 2000);
														}

														if (ImGui::TreeNode("[Draw]"))
														{
															static unsigned int drawgroups[8];
															static unsigned int dispgroups[8];
															static unsigned int backreadgroups[8];

															ReadProcessMemory(hProcess, (LPVOID)(enemy_ptr + 0x1A5C), drawgroups, 32, NULL);
															ReadProcessMemory(hProcess, (LPVOID)(enemy_ptr + 0x1A7C), dispgroups, 32, NULL);
															ReadProcessMemory(hProcess, (LPVOID)(enemy_ptr + 0x1A9C), backreadgroups, 32, NULL);

															static char bit_string[36];

															for (int k = 0; k < 8; k++) {
																BuildBitGroupString(drawgroups[k], bit_string);
																ImGui::Text("DrawGroup> %s", bit_string);
															}
															for (int k = 0; k < 8; k++) {
																BuildBitGroupString(dispgroups[k], bit_string);
																ImGui::Text("DispGroup> %s", bit_string);
															}
															for (int k = 0; k < 8; k++) {
																BuildBitGroupString(backreadgroups[k], bit_string);
																ImGui::Text("BackReadGroup> %s", bit_string);
															}
															
															ImGui::TreePop();
														}

														ImGui::Text("HP : [%d / %d]", enemy_hp, enemy_hp_max);
														ImGui::Text("MP : [%d / %d] Stamina : [%d / %d]", enemy_mp, enemy_mp_max, enemy_stamina, enemy_stamina_max);


														ImGui::TreePop();
													}
													else {
														ImGui::PopStyleColor();
													}
												}
											}*/
										}
									}
								}

								ImGui::TreePop();
							}
						}

					}
				}
			}



		}

		__int64 chr_base = 0;

		if (ReadProcessMemory(hProcess, (LPVOID)(chr_ptr + 0x80), &chr_base, 8, NULL))
		{
			RenderWorldChrManChrEntry(chr_base, true);
			/*int c0000_flags1 = 0;
			ReadProcessMemory(hProcess, (LPVOID)(chr_base + 0x1EE8), &c0000_flags1, 1, NULL);

			if (ImGui::TreeNode("[c0000]"))
			{
				if (ImGui::IsItemHovered()) {
					c0000_flags1 |= 1;
					WriteProcessMemory(hProcess, (LPVOID)(chr_base + 0x1EE8), &c0000_flags1, 1, NULL);
				}

				RenderWorldChrMan_c0000(chr_base);

				ImGui::TreePop();
			}
			else {
				if (ImGui::IsItemHovered()) {
					c0000_flags1 |= 1;
					WriteProcessMemory(hProcess, (LPVOID)(chr_base + 0x1EE8), &c0000_flags1, 1, NULL);
				}
			}*/
		}

		ImGui::TreePop();
	}
}

//void Menu::RenderWorldChrMan_c0000(__int64 chr_base)
//{
//	__int64 chr_inter1 = 0;
//
//	if (ReadProcessMemory(hProcess, (LPVOID)(chr_base + 0x1F90), &chr_inter1, 8, NULL))
//	{
//		__int64 c0000_ptr = 0;
//
//		if (ReadProcessMemory(hProcess, (LPVOID)(chr_inter1 + 0x18), &c0000_ptr, 8, NULL))
//		{
//			static int c0000_hp = 0;
//			static int c0000_hp_max = 0;
//			static int c0000_mp = 0;
//			static int c0000_mp_max = 0;
//			static int c0000_stamina = 0;
//			static int c0000_stamina_max = 0;
//
//			static bool c0000_noHit = false;
//			static bool c0000_noAttack = false;
//			static bool c0000_noMove = false;
//			static bool c0000_noGoodsConsume = false;
//			static bool c0000_noUpdate = false;
//			static bool c0000_disableGravity = false;
//			static bool c0000_invalidateTAE = false;
//
//			static bool c0000_drawHit = false;
//			static bool c0000_drawDirection = false;
//
//			static bool c0000_drawDmyPolygon = false;
//
//			static char c0000_flags1 = 0;
//			static char c0000_flags2 = 0;
//			static char c0000_flags3 = 0;
//			static char c0000_flags4 = 0;
//			static char c0000_flags5 = 0;
//
//			static int draw_polygon_num = 1000;
//
//			ReadProcessMemory(hProcess, (LPVOID)(chr_base + 0x1EE8), &c0000_flags1, 1, NULL);
//			ReadProcessMemory(hProcess, (LPVOID)(chr_base + 0x1EE9), &c0000_flags2, 1, NULL);
//			ReadProcessMemory(hProcess, (LPVOID)(chr_base + 0x1EEA), &c0000_flags3, 1, NULL);
//			ReadProcessMemory(hProcess, (LPVOID)(chr_base + 0x1A08), &c0000_flags4, 1, NULL);
//
//			ReadProcessMemory(hProcess, (LPVOID)(0x144584510), &draw_polygon_num, 4, NULL);
//
//			__int64 c0000_flags5_inter = 0;
//
//			ReadProcessMemory(hProcess, (LPVOID)(chr_base + 0x50), &c0000_flags5_inter, 1, NULL);
//			ReadProcessMemory(hProcess, (LPVOID)(c0000_flags5_inter + 0x48), &c0000_flags5_inter, 1, NULL);
//			ReadProcessMemory(hProcess, (LPVOID)(c0000_flags5_inter + 0x108), &c0000_flags5, 1, NULL);
//
//			ReadProcessMemory(hProcess, (LPVOID)(c0000_ptr + 0xD8), &c0000_hp, 4, NULL);
//			ReadProcessMemory(hProcess, (LPVOID)(c0000_ptr + 0xDC), &c0000_hp_max, 4, NULL);
//			ReadProcessMemory(hProcess, (LPVOID)(c0000_ptr + 0xE4), &c0000_mp, 4, NULL);
//			ReadProcessMemory(hProcess, (LPVOID)(c0000_ptr + 0xE8), &c0000_mp_max, 4, NULL);
//			ReadProcessMemory(hProcess, (LPVOID)(c0000_ptr + 0xF0), &c0000_stamina, 4, NULL);
//			ReadProcessMemory(hProcess, (LPVOID)(c0000_ptr + 0xF4), &c0000_stamina_max, 4, NULL);
//
//			c0000_drawHit = c0000_flags1 >> 2 & 1;
//			c0000_drawDirection = c0000_flags2 >> 2 & 1;
//			c0000_drawDmyPolygon = c0000_flags2 & 1;
//			c0000_noHit = c0000_flags1 >> 5 & 1;
//			c0000_noAttack = c0000_flags1 >> 6 & 1;
//			c0000_noMove = c0000_flags1 >> 7 & 1;
//			c0000_noGoodsConsume = c0000_flags3 >> 3 & 1;
//			c0000_noUpdate = c0000_flags2 >> 3 & 1;
//			c0000_disableGravity = c0000_flags4 >> 6 & 1;
//			c0000_invalidateTAE = c0000_flags5 >> 5 & 1;
//
//			if (ImGui::Checkbox("No Hit", &c0000_noHit))
//			{
//				if (c0000_noHit) {
//					c0000_flags1 |= 0x20;
//				}
//				else {
//					c0000_flags1 &= 0xDF;
//				}
//
//				WriteProcessMemory(hProcess, (LPVOID)(chr_base + 0x1EE8), &c0000_flags1, 1, NULL);
//			}
//
//			if (ImGui::Checkbox("No Attack", &c0000_noAttack))
//			{
//				if (c0000_noAttack) {
//					c0000_flags1 |= 0x40;
//				}
//				else {
//					c0000_flags1 &= 0xBF;
//				}
//
//				WriteProcessMemory(hProcess, (LPVOID)(chr_base + 0x1EE8), &c0000_flags1, 1, NULL);
//			}
//
//			if (ImGui::Checkbox("No Move", &c0000_noMove))
//			{
//				if (c0000_noMove) {
//					c0000_flags1 |= 0x80;
//				}
//				else {
//					c0000_flags1 &= 0x7F;
//				}
//
//				WriteProcessMemory(hProcess, (LPVOID)(chr_base + 0x1EE8), &c0000_flags1, 1, NULL);
//			}
//
//			if (ImGui::Checkbox("No Goods Consume", &c0000_noGoodsConsume))
//			{
//				if (c0000_noGoodsConsume) {
//					c0000_flags3 |= 0x8;
//				}
//				else {
//					c0000_flags3 &= 0xF7;
//				}
//
//				WriteProcessMemory(hProcess, (LPVOID)(chr_base + 0x1EEA), &c0000_flags3, 1, NULL);
//			}
//
//			if (ImGui::Checkbox("No Update", &c0000_noUpdate))
//			{
//				if (c0000_noUpdate) {
//					c0000_flags2 |= 0x8;
//				}
//				else {
//					c0000_flags2 &= 0xF7;
//				}
//
//				WriteProcessMemory(hProcess, (LPVOID)(chr_base + 0x1EE9), &c0000_flags2, 1, NULL);
//			}
//
//			if (ImGui::Checkbox("Disable Gravity", &c0000_disableGravity))
//			{
//				if (c0000_disableGravity) {
//					c0000_flags4 |= 0x40;
//				}
//				else {
//					c0000_flags4 &= 0xBF;
//				}
//
//				WriteProcessMemory(hProcess, (LPVOID)(chr_base + 0x1A08), &c0000_flags4, 1, NULL);
//			}
//
//			ImGui::SameLine();
//
//			if (ImGui::Checkbox("Invalidate TAE", &c0000_invalidateTAE))
//			{
//				if (c0000_invalidateTAE) {
//					c0000_flags5 |= 0x20;
//				}
//				else {
//					c0000_flags5 &= 0xDF;
//				}
//
//				WriteProcessMemory(hProcess, (LPVOID)(c0000_flags5_inter + 0x108), &c0000_flags5, 1, NULL);
//			}
//
//			if (ImGui::Button("Switch Control Player"))
//			{
//				dbgChrInsPressEnterButtonListener(chr_base, 0);
//			}
//
//			if (ImGui::Button("Return Control Player"))
//			{
//				dbgChrInsPressEnterButtonListener(chr_base, 40);
//			}
//
//			if (ImGui::Button("Move Position to this pos"))
//			{
//				dbgChrInsPressEnterButtonListener(chr_base, 42);
//			}
//
//			if (ImGui::Button("Reset Position at InitPos"))
//			{
//				dbgChrInsPressEnterButtonListener(chr_base, 41);
//			}
//
//			static unsigned __int64* lololo = 0;
//
//			if (ImGui::Button("TEST"))
//			{
//
//				unsigned int shit = 3;
//				//lololo = getHitMatString(&shit);
//				testFunc(chr_base, 0, 101);
//
//
//			}
//
//			if (ImGui::TreeNode("[Draw]"))
//			{
//				unsigned int drawgroups[8];
//				unsigned int dispgroups[8];
//				unsigned int backreadgroups[8];
//
//				short floor = 0;
//				unsigned int floor_actual = 0;
//				char floor_mat_name[128];
//				float floor_alpha = 0.0f;
//				int map_name_id = 0;
//
//				int armor_se1 = 0;
//				int armor_se2 = 0;
//				int armor_sfx1 = 0;
//				int armor_sfx2 = 0;
//				int sound_space = 0;
//				int play_region_id = 0;
//
//				__int64 ptr_sth_hit = 0;
//
//				char visibility_type_byte = 0;
//
//				ReadProcessMemory(hProcess, (LPVOID)(chr_base + 0x1A5C), drawgroups, 32, NULL);
//				ReadProcessMemory(hProcess, (LPVOID)(chr_base + 0x1A7C), dispgroups, 32, NULL);
//				ReadProcessMemory(hProcess, (LPVOID)(chr_base + 0x1A9C), backreadgroups, 32, NULL);
//				ReadProcessMemory(hProcess, (LPVOID)(chr_base + 0x1ABC), &play_region_id, 4, NULL);
//				ReadProcessMemory(hProcess, (LPVOID)(chr_base + 0x1AC0), &sound_space, 1, NULL);
//				ReadProcessMemory(hProcess, (LPVOID)(chr_base + 0x1AC1), &visibility_type_byte, 1, NULL);
//				ReadProcessMemory(hProcess, (LPVOID)(chr_base + 0x1AC8), &ptr_sth_hit, 8, NULL);
//				ReadProcessMemory(hProcess, (LPVOID)(chr_base + 0x1AD8), &floor_alpha, 4, NULL);
//
//				__int64 chr_sth_draw_ptr = 0;
//
//				if (ReadProcessMemory(hProcess, (LPVOID)(chr_inter1 + 0x68), &chr_sth_draw_ptr, 8, NULL))
//				{
//					ReadProcessMemory(hProcess, (LPVOID)(chr_sth_draw_ptr + 0x1F0), &floor_actual, 4, NULL);
//
//					__int64 chr_sth_draw_ptr1 = 0;
//
//					if (ReadProcessMemory(hProcess, (LPVOID)(chr_inter1 + 0xA0), &chr_sth_draw_ptr1, 8, NULL))
//					{
//						ReadProcessMemory(hProcess, (LPVOID)(chr_sth_draw_ptr1 + 0x10), &floor, 2, NULL);
//						ReadProcessMemory(hProcess, (LPVOID)(chr_sth_draw_ptr1 + 0x12), &armor_se1, 2, NULL);
//						ReadProcessMemory(hProcess, (LPVOID)(chr_sth_draw_ptr1 + 0x14), &armor_se2, 2, NULL);
//						ReadProcessMemory(hProcess, (LPVOID)(chr_sth_draw_ptr1 + 0x16), &armor_sfx1, 2, NULL);
//						ReadProcessMemory(hProcess, (LPVOID)(chr_sth_draw_ptr1 + 0x18), &armor_sfx2, 2, NULL);
//
//						__int64 chr_yet_another_ptr = 0;
//
//						//if (ReadProcessMemory(hProcess, (LPVOID)(chr_base + 0x1AC8), &chr_yet_another_ptr, 8, NULL))
//						//{
//							if (ptr_sth_hit) {
//
//								map_name_id = getMapNameId(ptr_sth_hit + 0x10);
//							}
//						//}
//
//						unsigned int hit_mat_param_idx = floor_actual; //this could go horribly wrong
//
//						const wchar_t* hit_mtrl_stringW;
//
//						hit_mtrl_stringW = getHitMtrlString(&hit_mat_param_idx);
//
//						int pos = 0;
//						char read_char;
//						do {
//							read_char = (char)hit_mtrl_stringW[pos];
//							floor_mat_name[pos] = read_char;
//							pos++;
//						} while (read_char);
//
//						static char bit_string[36];
//
//						for (int k = 0; k < 8; k++) {
//							BuildBitGroupString(drawgroups[k], bit_string);
//							ImGui::Text("DrawGroup> %s", bit_string);
//						}
//
//						for (int k = 0; k < 8; k++) {
//							BuildBitGroupString(dispgroups[k], bit_string);
//							ImGui::Text("DispGroup> %s", bit_string);
//						}
//
//						for (int k = 0; k < 8; k++) {
//							BuildBitGroupString(backreadgroups[k], bit_string);
//							ImGui::Text("BackReadGroup> %s", bit_string);
//						}
//
//						ImGui::Text("Material> Floor:%02d(%03d)(%s) FloorAlpha:%0.2f MapNameId:%d", floor, floor_actual, floor_mat_name, floor_alpha, map_name_id);
//						ImGui::Text("Material> ArmorSE1:%02d ArmorSE2:%02d ArmorSFX1:%02d ArmorSFX2:%02d SoundSpace:%02d playRegionId:%d", armor_se1, armor_se2, armor_sfx1, armor_sfx2, sound_space, play_region_id);
//
//						int map_uid = 0;
//
//						if (ptr_sth_hit) {
//							getMapUidForSth(ptr_sth_hit + 0x10, &map_uid);
//							wchar_t* hit_name = getPartMsbName(ptr_sth_hit + 0x10);
//
//							char hit_name_string[128];
//
//							pos = 0;
//							read_char;
//							do {
//								read_char = (char)hit_name[pos];
//								hit_name_string[pos] = read_char;
//								pos++;
//							} while (read_char);
//
//							ImGui::Text("<<A%02dB%d:%s>>FloorHitIns", map_uid >> 24 & 0xFF, map_uid >> 16 & 0xFF, hit_name_string);
//						}
//						else 
//						{
//							ImGui::Text("<<---->>FloorHitIns");
//						}
//
//						ImGui::Text("VisibilityType:%d, VisibilityType_HitIns:%d", visibility_type_byte & 0xF, visibility_type_byte >> 4);
//
//						static __int64 fog_id = 0;
//						static __int64 light_id = 0;
//						static __int64 sth_modeldraw_ptr = 0;
//
//						ReadProcessMemory(hProcess, (LPVOID)(chr_base + 0x48), &sth_modeldraw_ptr, 8, NULL);
//
//						if (sth_modeldraw_ptr)
//						{
//							getModelDrawParamFogIdForNpc(sth_modeldraw_ptr, &fog_id);
//							fog_id >>= 32;
//							getModelDrawParamLightIdForNpc(sth_modeldraw_ptr, &light_id);
//							light_id >>= 32;
//
//							ImGui::Text("ModelDrawParam> Light<<%d>> Fog<<%d>>", light_id, fog_id);
//						}
//						else 
//						{
//							ImGui::Text("ModelDrawParam> LightId<<-->> FogId<<-->>");
//						}
//
//						if (ptr_sth_hit)
//						{
//							ImGui::Text("SceneGparam EventID[%d][%d][%d][%d]", getSceneGparamEventId(ptr_sth_hit + 0x10, 1), getSceneGparamEventId(ptr_sth_hit + 0x10, 2), getSceneGparamEventId(ptr_sth_hit + 0x10, 3), getSceneGparamEventId(ptr_sth_hit + 0x10, 4));
//							ImGui::Text("EventEntityID<<%d>>", getEventEntityId(ptr_sth_hit + 0x10));
//						}
//						else 
//						{
//							ImGui::Text("SceneGparam EventID[--][--][--][--]");
//							ImGui::Text("EventEntityID<<none>>");
//						}
//
//						if (ImGui::Checkbox("Draw Hit", &c0000_drawHit))
//						{
//							if (c0000_drawHit) {
//								c0000_flags1 |= 0x4;
//							}
//							else {
//								c0000_flags1 &= 0xFB;
//							}
//
//							WriteProcessMemory(hProcess, (LPVOID)(chr_base + 0x1EE8), &c0000_flags1, 1, NULL);
//						}
//
//						if (ImGui::Checkbox("Draw Direction", &c0000_drawDirection))
//						{
//							if (c0000_drawDirection) {
//								c0000_flags2 |= 0x4;
//							}
//							else {
//								c0000_flags2 &= 0xFB;
//							}
//
//							WriteProcessMemory(hProcess, (LPVOID)(chr_base + 0x1EE9), &c0000_flags2, 1, NULL);
//						}
//
//						if (ImGui::Checkbox("Draw Dummy Polygon", &c0000_drawDmyPolygon))
//						{
//							if (c0000_drawDmyPolygon) {
//								c0000_flags2 |= 1;
//							}
//							else {
//								c0000_flags2 &= 0xFE;
//							}
//
//							WriteProcessMemory(hProcess, (LPVOID)(chr_base + 0x1EE9), &c0000_flags2, 1, NULL);
//						}
//
//						ImGui::SameLine();
//
//						int temp_draw_polygon_num = draw_polygon_num;
//						//static int test_draw_polygon_num = 1000;
//
//						if (draw_polygon_num == 0) {
//							if (ImGui::InputInt("(ALL)", &draw_polygon_num))
//							{
//								//WriteProcessMemory(hProcess, (LPVOID)(0x144584510), &draw_polygon_num, 4, NULL);
//							}
//						}
//						else
//						{
//							if (draw_polygon_num < 0) draw_polygon_num *= -1;
//							
//							if (ImGui::InputInt("(ONLY)", &draw_polygon_num))
//							{
//								//WriteProcessMemory(hProcess, (LPVOID)(0x144584510), &draw_polygon_num, 4, NULL);
//							}
//						}
//
//						if (draw_polygon_num != temp_draw_polygon_num)
//							WriteProcessMemory(hProcess, (LPVOID)(0x144584510), &draw_polygon_num, 4, NULL);
//						
//					}
//
//				}
//
//
//				ImGui::TreePop();
//			}
//
//			ImGui::Text("HP : [%d / %d]", c0000_hp, c0000_hp_max);
//			ImGui::Text("MP : [%d / %d] Stamina : [%d / %d]", c0000_mp, c0000_mp_max, c0000_stamina, c0000_stamina_max);
//
//		}
//	}
//}

void Menu::RenderWorldChrManChrEntry(__int64 enemy_base, bool is_player)
{
	__int64 enemy_ptr_inter = 0;
	__int64 enemy_ptr = 0;

	if (ReadProcessMemory(hProcess, (LPVOID)(enemy_base + 0x1F90), &enemy_ptr_inter, 8, NULL))
	{
		if (ReadProcessMemory(hProcess, (LPVOID)(enemy_ptr_inter + 0x18), &enemy_ptr, 8, NULL))
		{

			char enemy_name[32];
			char read_char;
			int count = 0;


			if (!is_player) 
			{
				do 
				{
					ReadProcessMemory(hProcess, (LPVOID)(enemy_ptr + 0x130 + count * 2), &read_char, 1, NULL);
					enemy_name[count] = read_char;
					count++;
				} while (read_char);
			}
			else 
			{
				strcpy_s(enemy_name, "[c0000]");
			}

			__int64 enemy_ptr_something = 0;
			char enemy_isLoaded = 0;

			ReadProcessMemory(hProcess, (LPVOID)(enemy_base + 0x30), &enemy_ptr_something, 8, NULL);
			ReadProcessMemory(hProcess, (LPVOID)(enemy_ptr_something + 0x84), &enemy_isLoaded, 1, NULL);

			if (enemy_isLoaded) {
				ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.4f, 1.4f, 0.4f, 1.0f));
			}
			else {
				ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.4f, 0.4f, 1.0f));
			}

			int flags1 = 0;
			ReadProcessMemory(hProcess, (LPVOID)(enemy_base + 0x1EE8), &flags1, 1, NULL);

			if (ImGui::TreeNode(enemy_name))
			{
				ImGui::PopStyleColor();

				if (ImGui::IsItemHovered()) {
					flags1 |= 1;
					WriteProcessMemory(hProcess, (LPVOID)(enemy_base + 0x1EE8), &flags1, 1, NULL);
				}

				int enemy_hp = 0;
				int enemy_hp_max = 0;
				int enemy_mp = 0;
				int enemy_mp_max = 0;
				int enemy_stamina = 0;
				int enemy_stamina_max = 0;

				bool enemy_drawHit = false;
				bool enemy_drawDirection = false;
				bool enemy_drawDmyPolygon = false;
				bool enemy_noHit = false;
				bool enemy_noAttack = false;
				bool enemy_noMove = false;
				bool enemy_noGoodsConsume = false;
				bool enemy_noUpdate = false;
				bool enemy_disableGravity = false;
				bool enemy_invalidateTAE = false;

				char enemy_flags1 = 0;
				char enemy_flags2 = 0;
				char enemy_flags3 = 0;
				char enemy_flags4 = 0;
				char enemy_flags5 = 0;
				char enemy_flags6 = 0;

				static int draw_polygon_num = 1000;

				ReadProcessMemory(hProcess, (LPVOID)(enemy_base + 0x1EE8), &enemy_flags1, 1, NULL);
				ReadProcessMemory(hProcess, (LPVOID)(enemy_base + 0x1EE9), &enemy_flags2, 1, NULL);
				ReadProcessMemory(hProcess, (LPVOID)(enemy_base + 0x1EEA), &enemy_flags3, 1, NULL);
				ReadProcessMemory(hProcess, (LPVOID)(enemy_base + 0x1A08), &enemy_flags4, 1, NULL);
				ReadProcessMemory(hProcess, (LPVOID)(enemy_base + 0x1A09), &enemy_flags6, 1, NULL);

				__int64 enemy_flags5_inter = 0;

				ReadProcessMemory(hProcess, (LPVOID)(0x144584510), &draw_polygon_num, 4, NULL);

				ReadProcessMemory(hProcess, (LPVOID)(enemy_base + 0x50), &enemy_flags5_inter, 1, NULL);
				ReadProcessMemory(hProcess, (LPVOID)(enemy_flags5_inter + 0x48), &enemy_flags5_inter, 1, NULL);
				ReadProcessMemory(hProcess, (LPVOID)(enemy_flags5_inter + 0x108), &enemy_flags5, 1, NULL);

				ReadProcessMemory(hProcess, (LPVOID)(enemy_ptr + 0xD8), &enemy_hp, 4, NULL);
				ReadProcessMemory(hProcess, (LPVOID)(enemy_ptr + 0xDC), &enemy_hp_max, 4, NULL);
				ReadProcessMemory(hProcess, (LPVOID)(enemy_ptr + 0xE4), &enemy_mp, 4, NULL);
				ReadProcessMemory(hProcess, (LPVOID)(enemy_ptr + 0xE8), &enemy_mp_max, 4, NULL);
				ReadProcessMemory(hProcess, (LPVOID)(enemy_ptr + 0xF0), &enemy_stamina, 4, NULL);
				ReadProcessMemory(hProcess, (LPVOID)(enemy_ptr + 0xF4), &enemy_stamina_max, 4, NULL);

				enemy_drawHit = enemy_flags1 >> 2 & 1;
				enemy_drawDirection = enemy_flags2 >> 2 & 1;
				enemy_drawDmyPolygon = enemy_flags2 & 1;
				enemy_noHit = enemy_flags1 >> 5 & 1;
				enemy_noAttack = enemy_flags1 >> 6 & 1;
				enemy_noMove = enemy_flags1 >> 7 & 1;
				enemy_noGoodsConsume = enemy_flags3 >> 3 & 1;
				enemy_noUpdate = enemy_flags2 >> 3 & 1;
				enemy_disableGravity = enemy_flags4 >> 6 & 1;
				enemy_invalidateTAE = enemy_flags5 >> 5 & 1;

				if (ImGui::Checkbox("No Hit", &enemy_noHit))
				{
					if (enemy_noHit) {
						enemy_flags1 |= 0x20;
					}
					else {
						enemy_flags1 &= 0xDF;
					}

					WriteProcessMemory(hProcess, (LPVOID)(enemy_base + 0x1EE8), &enemy_flags1, 1, NULL);
				}

				if (ImGui::Checkbox("No Attack", &enemy_noAttack))
				{
					if (enemy_noAttack) {
						enemy_flags1 |= 0x40;
					}
					else {
						enemy_flags1 &= 0xBF;
					}

					WriteProcessMemory(hProcess, (LPVOID)(enemy_base + 0x1EE8), &enemy_flags1, 1, NULL);
				}

				if (ImGui::Checkbox("No Move", &enemy_noMove))
				{
					if (enemy_noMove) {
						enemy_flags1 |= 0x80;
					}
					else {
						enemy_flags1 &= 0x7F;
					}

					WriteProcessMemory(hProcess, (LPVOID)(enemy_base + 0x1EE8), &enemy_flags1, 1, NULL);
				}

				if (ImGui::Checkbox("No Goods Consume", &enemy_noGoodsConsume))
				{
					if (enemy_noGoodsConsume) {
						enemy_flags3 |= 0x8;
					}
					else {
						enemy_flags3 &= 0xF7;
					}

					WriteProcessMemory(hProcess, (LPVOID)(enemy_base + 0x1EEA), &enemy_flags3, 1, NULL);
				}

				if (ImGui::Checkbox("No Update", &enemy_noUpdate))
				{
					if (enemy_noUpdate) {
						enemy_flags2 |= 0x8;
					}
					else {
						enemy_flags2 &= 0xF7;
					}

					WriteProcessMemory(hProcess, (LPVOID)(enemy_base + 0x1EE9), &enemy_flags2, 1, NULL);
				}

				if (ImGui::Checkbox("Disable Gravity", &enemy_disableGravity))
				{
					if (enemy_disableGravity) {
						enemy_flags4 |= 0x40;
					}
					else {
						enemy_flags4 &= 0xBF;
					}

					WriteProcessMemory(hProcess, (LPVOID)(enemy_base + 0x1A08), &enemy_flags4, 1, NULL);
				}

				ImGui::SameLine();

				if (ImGui::Checkbox("Invalidate TAE", &enemy_invalidateTAE))
				{
					if (enemy_invalidateTAE) {
						enemy_flags5 |= 0x20;
					}
					else {
						enemy_flags5 &= 0xDF;
					}

					WriteProcessMemory(hProcess, (LPVOID)(enemy_flags5_inter + 0x108), &enemy_flags5, 1, NULL);
				}

				if (ImGui::Button("Switch Control Player"))
				{
					dbgChrInsPressEnterButtonListener(enemy_base, 0);
				}

				if (ImGui::Button("Return Control Player"))
				{
					dbgChrInsPressEnterButtonListener(enemy_base, 40);
				}

				if (ImGui::Button("Move Position to this pos"))
				{
					dbgChrInsPressEnterButtonListener(enemy_base, 42);
				}

				if (ImGui::Button("Reset Position at InitPos"))
				{
					dbgChrInsPressEnterButtonListener(enemy_base, 41);
				}

				if (!is_player) 
				{
					if (ImGui::Button("Export MapStudio"))
					{
						dbgChrInsPressEnterButtonListener(enemy_base, 2000);
					}
				}

				if (ImGui::TreeNode("[Draw]"))
				{
					unsigned int drawgroups[8];
					unsigned int dispgroups[8];
					unsigned int backreadgroups[8];

					float enemy_alpha = 1.0f;

					short floor = 0;
					unsigned int floor_actual = 0;
					char floor_mat_name[128];
					float floor_alpha = 0.0f;
					int map_name_id = 0;

					int armor_se1 = 0;
					int armor_se2 = 0;
					int armor_sfx1 = 0;
					int armor_sfx2 = 0;
					int sound_space = 0;
					int play_region_id = 0;

					char visibility_type_byte = 0;

					__int64 chr_yet_another_ptr = 0;

					ReadProcessMemory(hProcess, (LPVOID)(enemy_base + 0x1A44), &enemy_alpha, 4, NULL);
					ReadProcessMemory(hProcess, (LPVOID)(enemy_base + 0x1A5C), drawgroups, 32, NULL);
					ReadProcessMemory(hProcess, (LPVOID)(enemy_base + 0x1A7C), dispgroups, 32, NULL);
					ReadProcessMemory(hProcess, (LPVOID)(enemy_base + 0x1A9C), backreadgroups, 32, NULL);
					ReadProcessMemory(hProcess, (LPVOID)(enemy_base + 0x1ABC), &play_region_id, 4, NULL);
					ReadProcessMemory(hProcess, (LPVOID)(enemy_base + 0x1AC0), &sound_space, 1, NULL);
					ReadProcessMemory(hProcess, (LPVOID)(enemy_base + 0x1AC1), &visibility_type_byte, 1, NULL);
					ReadProcessMemory(hProcess, (LPVOID)(enemy_base + 0x1AC8), &chr_yet_another_ptr, 8, NULL);
					ReadProcessMemory(hProcess, (LPVOID)(enemy_base + 0x1AD8), &floor_alpha, 4, NULL);

					__int64 chr_sth_draw_ptr = 0;

					if (ReadProcessMemory(hProcess, (LPVOID)(enemy_ptr_inter + 0x68), &chr_sth_draw_ptr, 8, NULL))
					{
						ReadProcessMemory(hProcess, (LPVOID)(chr_sth_draw_ptr + 0x1F0), &floor_actual, 4, NULL);

						__int64 chr_sth_draw_ptr1 = 0;

						if (ReadProcessMemory(hProcess, (LPVOID)(enemy_ptr_inter + 0xA0), &chr_sth_draw_ptr1, 8, NULL))
						{
							ReadProcessMemory(hProcess, (LPVOID)(chr_sth_draw_ptr1 + 0x10), &floor, 2, NULL);
							ReadProcessMemory(hProcess, (LPVOID)(chr_sth_draw_ptr1 + 0x12), &armor_se1, 2, NULL);
							ReadProcessMemory(hProcess, (LPVOID)(chr_sth_draw_ptr1 + 0x14), &armor_se2, 2, NULL);
							ReadProcessMemory(hProcess, (LPVOID)(chr_sth_draw_ptr1 + 0x16), &armor_sfx1, 2, NULL);
							ReadProcessMemory(hProcess, (LPVOID)(chr_sth_draw_ptr1 + 0x18), &armor_sfx2, 2, NULL);

							
							if (chr_yet_another_ptr) {
								//chr_yet_another_ptr += 0x10;

								map_name_id = getMapNameId(chr_yet_another_ptr + 0x10);
							}

							unsigned int hit_mat_param_idx = floor_actual; //this could go horribly wrong

							const wchar_t* hit_mtrl_stringW;

							hit_mtrl_stringW = getHitMtrlString(&hit_mat_param_idx);

							int pos = 0;
							char read_char;
							do {
								read_char = (char)hit_mtrl_stringW[pos];
								floor_mat_name[pos] = read_char;
								pos++;
							} while (read_char);

							static char bit_string[100];

							ImGui::BeginGroup();
							{
								for (int k = 0; k < 8; k++) {
									ImGui::Text("DrawGroup>");
								}

								for (int k = 0; k < 8; k++) {
									ImGui::Text("DispGroup>");
								}

								for (int k = 0; k < 8; k++) {
									ImGui::Text("BackReadGroup>");
								}
							}
							ImGui::EndGroup();
							ImGui::SameLine();

							ImGui::BeginGroup();
							{
								for (int k = 0; k < 8; k++) {
									BuildBitGroupString(drawgroups[k], bit_string);
									ImGui::Text(bit_string);
								}

								for (int k = 0; k < 8; k++) {
									BuildBitGroupString(dispgroups[k], bit_string);
									ImGui::Text(bit_string);
								}

								for (int k = 0; k < 8; k++) {
									BuildBitGroupString(backreadgroups[k], bit_string);
									ImGui::Text(bit_string);
								}
							}
							ImGui::EndGroup();

							/*for (int k = 0; k < 8; k++) {
								BuildBitGroupString(drawgroups[k], bit_string);
								ImGui::Text("DrawGroup> %s", bit_string);
							}

							for (int k = 0; k < 8; k++) {
								BuildBitGroupString(dispgroups[k], bit_string);
								ImGui::Text("DispGroup> %s", bit_string);
							}

							for (int k = 0; k < 8; k++) {
								BuildBitGroupString(backreadgroups[k], bit_string);
								ImGui::Text("BackReadGroup> %s", bit_string);
							}*/

							ImGui::Text("Material> Floor:%02d(%03d)(%s) FloorAlpha:%0.2f MapNameId:%d", floor, floor_actual, floor_mat_name, floor_alpha, map_name_id);
							ImGui::Text("Material> ArmorSE1:%02d ArmorSE2:%02d ArmorSFX1:%02d ArmorSFX2:%02d SoundSpace:%02d playRegionId:%d", armor_se1, armor_se2, armor_sfx1, armor_sfx2, sound_space, play_region_id);
						
							int map_uid = 0;

							if (chr_yet_another_ptr) {
								getMapUidForSth(chr_yet_another_ptr + 0x10, &map_uid);
								wchar_t* hit_name = getPartMsbName(chr_yet_another_ptr + 0x10);

								char hit_name_string[128];

								pos = 0;
								read_char;
								do {
									read_char = (char)hit_name[pos];
									hit_name_string[pos] = read_char;
									pos++;
								} while (read_char);

								ImGui::Text("\xe2\x89\xaa""A%02dB%d:%s\xe2\x89\xab""FloorHitIns", map_uid >> 24 & 0xFF, map_uid >> 16 & 0xFF, hit_name_string);
							}
							else
							{
								ImGui::Text("\xe2\x89\xaa""----\xe2\x89\xab""FloorHitIns");
							}

							ImGui::Text("VisibilityType:%d, VisibilityType_HitIns:%d", visibility_type_byte & 0xF, visibility_type_byte >> 4);

							static __int64 fog_id = 0;
							static __int64 light_id = 0;
							static __int64 sth_modeldraw_ptr = 0;

							ReadProcessMemory(hProcess, (LPVOID)(enemy_base + 0x48), &sth_modeldraw_ptr, 8, NULL);

							if (sth_modeldraw_ptr)
							{
								getModelDrawParamFogIdForNpc(sth_modeldraw_ptr, &fog_id);
								fog_id >>= 32;
								getModelDrawParamLightIdForNpc(sth_modeldraw_ptr, &light_id);
								light_id >>= 32;

								ImGui::Text("ModelDrawParam> Light\xe2\x89\xaa""%d\xe2\x89\xab"" Fog\xe2\x89\xaa""%d\xe2\x89\xab""", light_id, fog_id);
							}
							else
							{
								ImGui::Text("ModelDrawParam> LightId\xe2\x89\xaa""--\xe2\x89\xab"" FogId\xe2\x89\xaa""--\xe2\x89\xab""");
							}

							if (chr_yet_another_ptr)
							{
								ImGui::Text("SceneGparam EventID[%d][%d][%d][%d]", getSceneGparamEventId(chr_yet_another_ptr + 0x10, 1), getSceneGparamEventId(chr_yet_another_ptr + 0x10, 2), getSceneGparamEventId(chr_yet_another_ptr + 0x10, 3), getSceneGparamEventId(chr_yet_another_ptr + 0x10, 4));
								ImGui::Text("EventEntityID\xe2\x89\xaa""%d\xe2\x89\xab""", getEventEntityId(chr_yet_another_ptr + 0x10));
							}
							else
							{
								ImGui::Text("SceneGparam EventID[--][--][--][--]");
								ImGui::Text("EventEntityID\xe2\x89\xaa""none\xe2\x89\xab");
							}

							if (ImGui::Checkbox("Draw Hit", &enemy_drawHit))
							{
								if (enemy_drawHit) {
									enemy_flags1 |= 0x4;
								}
								else {
									enemy_flags1 &= 0xFB;
								}

								WriteProcessMemory(hProcess, (LPVOID)(enemy_base + 0x1EE8), &enemy_flags1, 1, NULL);
							}

							if (ImGui::Checkbox("Draw Direction", &enemy_drawDirection))
							{
								if (enemy_drawDirection) {
									enemy_flags2 |= 0x4;
								}
								else {
									enemy_flags2 &= 0xFB;
								}

								WriteProcessMemory(hProcess, (LPVOID)(enemy_base + 0x1EE9), &enemy_flags2, 1, NULL);
							}

							if (ImGui::Button("Toggle Draw"))
							{
								dbgChrInsPressEnterButtonListener(enemy_base, 121);
							}

							bool enemy_is_draw = enemy_flags6 >> 5 & 1;

							ImGui::Text("IsEnableDraw:%d (IsDraw:%d IsEnable:%d IsOmission:%d)", getChrIsEnableDraw(enemy_base), enemy_is_draw, getChrIsEnable(enemy_base) == 0, getChrIsOmission(enemy_base));

							if (ImGui::Checkbox("Draw Dummy Polygon", &enemy_drawDmyPolygon))
							{
								if (enemy_drawDmyPolygon) {
									enemy_flags2 |= 1;
								}
								else {
									enemy_flags2 &= 0xFE;
								}

								WriteProcessMemory(hProcess, (LPVOID)(enemy_base + 0x1EE9), &enemy_flags2, 1, NULL);
							}

							ImGui::SameLine();

							int temp_draw_polygon_num = draw_polygon_num;
							//static int test_draw_polygon_num = 1000;

							if (draw_polygon_num == 0) {
								if (ImGui::InputInt("(ALL)", &draw_polygon_num))
								{
									//WriteProcessMemory(hProcess, (LPVOID)(0x144584510), &draw_polygon_num, 4, NULL);
								}
							}
							else
							{
								if (draw_polygon_num < 0) draw_polygon_num *= -1;

								if (ImGui::InputInt("(ONLY)", &draw_polygon_num))
								{
									//WriteProcessMemory(hProcess, (LPVOID)(0x144584510), &draw_polygon_num, 4, NULL);
								}
							}

							if (draw_polygon_num != temp_draw_polygon_num)
								WriteProcessMemory(hProcess, (LPVOID)(0x144584510), &draw_polygon_num, 4, NULL);

							bool enemy_drawCounter = enemy_flags3 & 1;

							if (ImGui::Checkbox("Draw Counter", &enemy_drawCounter))
							{
								if (enemy_drawCounter) {
									enemy_flags3 |= 1;
								}
								else {
									enemy_flags3 &= 0xFE;
								}

								WriteProcessMemory(hProcess, (LPVOID)(enemy_base + 0x1EEA), &enemy_flags3, 1, NULL);
							}

							if (ImGui::InputFloat("Ghost \xce\xb1", &enemy_alpha, 0.01f, 0.1f))
							{
								if (enemy_alpha < 0.0f)
								{
									enemy_alpha = 1.0f;
								}
								else if (enemy_alpha > 1.0f)
								{
									enemy_alpha = 0.0f;
								}

								WriteProcessMemory(hProcess, (LPVOID)(enemy_base + 0x1A44), &enemy_alpha, 4, NULL);
							}

							int fade_out_from = 0;

							ReadProcessMemory(hProcess, (LPVOID)(enemy_base + 0x1F4C), &fade_out_from, 4, NULL);

							ImGui::Text("FadeOut From[%d]", fade_out_from);

							__int64 func_address = 0;

							ReadProcessMemory(hProcess, (LPVOID)enemy_base, &func_address, 8, NULL);
							ReadProcessMemory(hProcess, (LPVOID)(func_address + 0x3A8), &func_address, 8, NULL);

							typedef int(__fastcall* _getShit)(__int64 this_ptr);
							_getShit call_this_function = (_getShit)func_address;

							int debug_change = 0;
							int water_id = 0;

							float water_wetting_rate = 0.0f;
							float water_wetting_rate_metal = 0.0f;
							float water_wetting_rate_non_metal = 0.0f;

							ReadProcessMemory(hProcess, (LPVOID)(enemy_base + 0x1F38), &debug_change, 4, NULL);
							ReadProcessMemory(hProcess, (LPVOID)(enemy_base + 0x1F3C), &water_id, 4, NULL);
							ReadProcessMemory(hProcess, (LPVOID)(enemy_base + 0x1F40), &water_wetting_rate, 4, NULL);
							ReadProcessMemory(hProcess, (LPVOID)(enemy_base + 0x1F44), &water_wetting_rate_metal, 4, NULL);
							ReadProcessMemory(hProcess, (LPVOID)(enemy_base + 0x1F48), &water_wetting_rate_metal, 4, NULL);

							if (func_address) 
							{
								ImGui::Text("Phantom Parameter ID: Current Value [%d], Debug Change [%d]", call_this_function(enemy_base), debug_change);
							}

							ImGui::Text("Water ID: Current Value [%d], Debug Change [%d]", water_id, water_id);

							if (ImGui::InputFloat("Water Wetting Rate", &water_wetting_rate, 0.01f, 0.1f))
							{
								if (water_wetting_rate < 0.0f)
								{
									water_wetting_rate = 1.0f;
								}
								else if (water_wetting_rate > 1.0f)
								{
									water_wetting_rate = 0.0f;
								}

								WriteProcessMemory(hProcess, (LPVOID)(enemy_base + 0x1F40), &water_wetting_rate, 4, NULL);
							}

							if (ImGui::InputFloat("Water Wetting Rate (Metal)", &water_wetting_rate_metal, 0.01f, 0.1f))
							{
								if (water_wetting_rate_metal < 0.0f)
								{
									water_wetting_rate_metal = 1.0f;
								}
								else if (water_wetting_rate_metal > 1.0f)
								{
									water_wetting_rate_metal = 0.0f;
								}

								WriteProcessMemory(hProcess, (LPVOID)(enemy_base + 0x1F44), &water_wetting_rate_metal, 4, NULL);
							}

							if (ImGui::InputFloat("Water Wetting Rate (Non-Metal)", &water_wetting_rate_non_metal, 0.01f, 0.1f))
							{
								if (water_wetting_rate_non_metal < 0.0f)
								{
									water_wetting_rate_non_metal = 1.0f;
								}
								else if (water_wetting_rate_non_metal > 1.0f)
								{
									water_wetting_rate_non_metal = 0.0f;
								}

								WriteProcessMemory(hProcess, (LPVOID)(enemy_base + 0x1F48), &water_wetting_rate_non_metal, 4, NULL);
							}

							//TODO: WetControl


						}

					}


					ImGui::TreePop();
				}

				ImGui::Text("HP : [%d / %d]", enemy_hp, enemy_hp_max);
				ImGui::Text("MP : [%d / %d] Stamina : [%d / %d]", enemy_mp, enemy_mp_max, enemy_stamina, enemy_stamina_max);


				ImGui::TreePop();
			}
			else {
				ImGui::PopStyleColor();

				if (ImGui::IsItemHovered()) {
					flags1 |= 1;
					WriteProcessMemory(hProcess, (LPVOID)(enemy_base + 0x1EE8), &flags1, 1, NULL);
				}
			}

			/*int draw_flags1 = 0;
			ReadProcessMemory(hProcess, (LPVOID)(enemy_base + 0x1EE8), &draw_flags1, 1, NULL);

			if (ImGui::IsItemHovered()) {
				draw_flags1 |= 1;
				WriteProcessMemory(hProcess, (LPVOID)(enemy_base + 0x1EE8), &draw_flags1, 1, NULL);
			}*/
		}
	}
}

void Menu::RenderChrDbg() 
{
	if (ImGui::TreeNode("[CHR DBG]"))
	{
		__int64 world_chr_man_dbg_ptr = 0;

		if (ReadProcessMemory(hProcess, (LPCVOID)world_chr_man_dbg_ptr_address, &world_chr_man_dbg_ptr, 8, NULL))
		{
			if (world_chr_man_dbg_ptr)
			{
				ReadProcessMemory(hProcess, (LPVOID)0x144768F68, &chrDbgFlags, 0x20, NULL);

				if (ImGui::Checkbox("Player No Dead", &chrDbgFlags.dbgPlayerNoDead))
				{
					WriteProcessMemory(hProcess, (LPVOID)0x144768F68, &chrDbgFlags.dbgPlayerNoDead, 1, NULL);
				}

				if (ImGui::Checkbox("Player Exterminate", &chrDbgFlags.dbgPlayerExterminate))
				{
					WriteProcessMemory(hProcess, (LPVOID)0x144768F69, &chrDbgFlags.dbgPlayerExterminate, 1, NULL);
				}

				if (ImGui::Checkbox("All No Dead", &chrDbgFlags.dbgAllNoDead))
				{
					WriteProcessMemory(hProcess, (LPVOID)0x144768F70, &chrDbgFlags.dbgAllNoDead, 1, NULL);
				}

				if (ImGui::Checkbox("All No Damage", &chrDbgFlags.dbgAllNoDamage))
				{
					WriteProcessMemory(hProcess, (LPVOID)0x144768F71, &chrDbgFlags.dbgAllNoDamage, 1, NULL);
				}

				if (ImGui::Checkbox("All No Hit", &chrDbgFlags.dbgAllNoHit))
				{
					WriteProcessMemory(hProcess, (LPVOID)0x144768F72, &chrDbgFlags.dbgAllNoHit, 1, NULL);
				}

				if (ImGui::Checkbox("All No Attack", &chrDbgFlags.dbgAllNoAttack))
				{
					WriteProcessMemory(hProcess, (LPVOID)0x144768F73, &chrDbgFlags.dbgAllNoAttack, 1, NULL);
				}

				if (ImGui::Checkbox("All No Move", &chrDbgFlags.dbgAllNoMove))
				{
					WriteProcessMemory(hProcess, (LPVOID)0x144768F74, &chrDbgFlags.dbgAllNoMove, 1, NULL);
				}

				if (ImGui::Checkbox("All No Update AI", &chrDbgFlags.dbgAllNoUpdateAi))
				{
					WriteProcessMemory(hProcess, (LPVOID)0x144768F75, &chrDbgFlags.dbgAllNoUpdateAi, 1, NULL);
				}

				if (ImGui::Checkbox("All No Stamina Consume", &chrDbgFlags.dbgAllNoStaminaConsume))
				{
					WriteProcessMemory(hProcess, (LPVOID)0x144768F6A, &chrDbgFlags.dbgAllNoStaminaConsume, 1, NULL);
				}

				if (ImGui::Checkbox("All No MP Consume", &chrDbgFlags.dbgAllNoMPConsume))
				{
					WriteProcessMemory(hProcess, (LPVOID)0x144768F6B, &chrDbgFlags.dbgAllNoMPConsume, 1, NULL);
				}

				if (ImGui::Checkbox("All No Arrow Consume", &chrDbgFlags.dbgAllNoArrowConsume))
				{
					WriteProcessMemory(hProcess, (LPVOID)0x144768F6C, &chrDbgFlags.dbgAllNoArrowConsume, 1, NULL);
				}

				if (ImGui::Checkbox("All No MagicQty Consume", &chrDbgFlags.dbgAllNoMagicQtyConsume))
				{
					WriteProcessMemory(hProcess, (LPVOID)0x144768F6D, &chrDbgFlags.dbgAllNoMagicQtyConsume, 1, NULL);
				}

				if (ImGui::Checkbox("All No WepProtDurability Damage", &chrDbgFlags.dbgAllNoWepProtDurabilityDamage))
				{
					WriteProcessMemory(hProcess, (LPVOID)0x144768F76, &chrDbgFlags.dbgAllNoWepProtDurabilityDamage, 1, NULL);
				}

				if (ImGui::Checkbox("All No Arts Point Consume", &chrDbgFlags.dbgAllNoArtsPointConsume))
				{
					WriteProcessMemory(hProcess, (LPVOID)0x144768F77, &chrDbgFlags.dbgAllNoArtsPointConsume, 1, NULL);
				}

				if (ImGui::Checkbox("Player Hide", &chrDbgFlags.dbgPlayerHide))
				{
					WriteProcessMemory(hProcess, (LPVOID)0x144768F6E, &chrDbgFlags.dbgPlayerHide, 1, NULL);
				}

				if (ImGui::Checkbox("Player Silence", &chrDbgFlags.dbgPlayerSilence))
				{
					WriteProcessMemory(hProcess, (LPVOID)0x144768F6F, &chrDbgFlags.dbgPlayerSilence, 1, NULL);
				}

				bool new_knockback_mode = false;
				bool draw_footik_ray = false;
				bool show_toughness = false;
				bool disable_ritual_exec_cond_check = false;
				bool enable_bonfire_function = false;
				bool all_debug_drawing_functions = false;
				bool all_draw_hit = false;

				ReadProcessMemory(hProcess, (LPCVOID)(world_chr_man_dbg_ptr + 0x65), &all_debug_drawing_functions, 1, NULL);
				ReadProcessMemory(hProcess, (LPCVOID)(world_chr_man_dbg_ptr + 0x66), &all_draw_hit, 1, NULL);
				ReadProcessMemory(hProcess, (LPCVOID)(world_chr_man_dbg_ptr + 0x6B), &draw_footik_ray, 1, NULL);
				ReadProcessMemory(hProcess, (LPCVOID)(world_chr_man_dbg_ptr + 0x6C), &show_toughness, 1, NULL);
				ReadProcessMemory(hProcess, (LPCVOID)(world_chr_man_dbg_ptr + 0x135), &new_knockback_mode, 1, NULL);
				ReadProcessMemory(hProcess, (LPCVOID)(world_chr_man_dbg_ptr + 0x189), &disable_ritual_exec_cond_check, 1, NULL);
				ReadProcessMemory(hProcess, (LPCVOID)(world_chr_man_dbg_ptr + 0x18A), &enable_bonfire_function, 1, NULL);
				

				if (ImGui::Checkbox("New KnockBackMode", &new_knockback_mode))
				{
					WriteProcessMemory(hProcess, (LPVOID)(world_chr_man_dbg_ptr + 0x135), &new_knockback_mode, 1, NULL);
				}

				if (ImGui::Checkbox("Draw FootIK Ray", &draw_footik_ray))
				{
					WriteProcessMemory(hProcess, (LPVOID)(world_chr_man_dbg_ptr + 0x6B), &draw_footik_ray, 1, NULL);
				}

				if (ImGui::Checkbox("Show Toughness", &show_toughness))
				{
					WriteProcessMemory(hProcess, (LPVOID)(world_chr_man_dbg_ptr + 0x6C), &show_toughness, 1, NULL);
				}

				if (ImGui::Checkbox("Force Parry Mode", &chrDbgFlags.dbgForcedParryMode))
				{
					WriteProcessMemory(hProcess, (LPVOID)0x144768F78, &chrDbgFlags.dbgForcedParryMode, 1, NULL);
				}
				
				if (ImGui::Checkbox("Disable Ritual Execution Condition Check", &disable_ritual_exec_cond_check))
				{
					WriteProcessMemory(hProcess, (LPVOID)(world_chr_man_dbg_ptr + 0x189), &disable_ritual_exec_cond_check, 1, NULL);
				}

				if (ImGui::Checkbox("Enable Bonfire Function", &enable_bonfire_function))
				{
					WriteProcessMemory(hProcess, (LPVOID)(world_chr_man_dbg_ptr + 0x18A), &enable_bonfire_function, 1, NULL);
				}

				if (ImGui::Button("Switch All No Update"))
				{
					switchAllNoUpdate(0, 0);
				}

				if (ImGui::Checkbox("All Debug Drawing Functions", &all_debug_drawing_functions))
				{
					WriteProcessMemory(hProcess, (LPVOID)(world_chr_man_dbg_ptr + 0x65), &all_debug_drawing_functions, 1, NULL);
				}

				if (ImGui::Checkbox("All Draw Hit", &all_draw_hit))
				{
					WriteProcessMemory(hProcess, (LPVOID)(world_chr_man_dbg_ptr + 0x66), &all_draw_hit, 1, NULL);
				}

				if (ImGui::Checkbox("All Omission Mode", &chrDbgFlags.dbgAllOmissionMode))
				{
					WriteProcessMemory(hProcess, (LPVOID)0x144768F7A, &chrDbgFlags.dbgAllOmissionMode, 1, NULL);
				}

				ChrFinder chr_finder;
				__int64 chr_ptr = 0;

				ReadProcessMemory(hProcess, (LPCVOID)chr_ptr_address, &chr_ptr, 8, NULL);

				int lv1 = 0;
				int lv2 = 0;
				int lv5 = 0;
				int lv30 = 0;
				int none = 0;

				getMAXIMOSENEMIGOS(chr_ptr, &chr_finder, 0);

				ReadProcessMemory(hProcess, (LPCVOID)(world_chr_man_dbg_ptr + 0x14), &lv1, 4, NULL);
				ReadProcessMemory(hProcess, (LPCVOID)(world_chr_man_dbg_ptr + 0x18), &lv2, 4, NULL);
				ReadProcessMemory(hProcess, (LPCVOID)(world_chr_man_dbg_ptr + 0x1C), &lv5, 4, NULL);
				ReadProcessMemory(hProcess, (LPCVOID)(world_chr_man_dbg_ptr + 0x20), &lv30, 4, NULL);

				none = chr_finder.result - lv30 - lv5 - lv2 - lv1;

				ImGui::Text("Lv1[ %d ]/Lv2[ %d ]/Lv5[ %d ]Lv30[ %d ]/None[ %d ]/Total[ %d ]", lv1, lv2, lv5, lv30, none, chr_finder.result);

				int visible_num = 0;
				int ready_num = 0;

				ReadProcessMemory(hProcess, (LPCVOID)(chr_ptr + 0x2FE8), &ready_num, 4, NULL);
				ReadProcessMemory(hProcess, (LPCVOID)(chr_ptr + 0x2FEC), &visible_num, 4, NULL);

				ImGui::Text("%04d/%04d/%04d<VisibleNum/ReadyNum/MaxNum", visible_num, ready_num, chr_finder.result);

				int lv1_update_count = 0;
				int lv2_update_count = 0;
				float omitted_distance_drawgroup_invalid = 0.0f;
				float omitted_distance_discrimination_in_screen = 0.0f;
				float omitted_distance_no_frame_lv30 = 0.0f;
				float default_update_distance_whatever = 0.0f;
				float abbreviated_update_distance_nondrawing_lv2 = 0.0f;
				float abbreviated_update_distance_nondrawing_lv5 = 0.0f;
				float abbreviated_update_distance_ragdoll_prio_red_dist = 0.0f;
				int lod_level_shadows = 0;
				bool display_update_skip_status = false;
				bool hide_lv5_chrs = false;
				bool update_lv5_to_lv30 = false;
				bool npc_local_control_display = false;
				bool lod_level_display = false;
				int ez_state_fix_rand_num = 0;

				ReadProcessMemory(hProcess, (LPCVOID)(world_chr_man_dbg_ptr + 0x11), &display_update_skip_status, 1, NULL);
				ReadProcessMemory(hProcess, (LPCVOID)(world_chr_man_dbg_ptr + 0x12), &hide_lv5_chrs, 1, NULL);
				ReadProcessMemory(hProcess, (LPCVOID)(world_chr_man_dbg_ptr + 0x13), &update_lv5_to_lv30, 1, NULL);
				ReadProcessMemory(hProcess, (LPCVOID)(world_chr_man_dbg_ptr + 0x24), &lv1_update_count, 4, NULL);
				ReadProcessMemory(hProcess, (LPCVOID)(world_chr_man_dbg_ptr + 0x28), &lv2_update_count, 4, NULL);
				ReadProcessMemory(hProcess, (LPCVOID)(world_chr_man_dbg_ptr + 0x2C), &omitted_distance_drawgroup_invalid, 4, NULL);
				ReadProcessMemory(hProcess, (LPCVOID)(world_chr_man_dbg_ptr + 0x30), &default_update_distance_whatever, 4, NULL);
				ReadProcessMemory(hProcess, (LPCVOID)(world_chr_man_dbg_ptr + 0x34), &omitted_distance_discrimination_in_screen, 4, NULL);
				ReadProcessMemory(hProcess, (LPCVOID)(world_chr_man_dbg_ptr + 0x38), &abbreviated_update_distance_nondrawing_lv2, 4, NULL);
				ReadProcessMemory(hProcess, (LPCVOID)(world_chr_man_dbg_ptr + 0x3C), &abbreviated_update_distance_nondrawing_lv5, 4, NULL);
				ReadProcessMemory(hProcess, (LPCVOID)(world_chr_man_dbg_ptr + 0x40), &omitted_distance_no_frame_lv30, 4, NULL);
				ReadProcessMemory(hProcess, (LPCVOID)(world_chr_man_dbg_ptr + 0x44), &abbreviated_update_distance_ragdoll_prio_red_dist, 4, NULL);
				ReadProcessMemory(hProcess, (LPCVOID)(world_chr_man_dbg_ptr + 0x4C), &lod_level_shadows, 4, NULL);
				ReadProcessMemory(hProcess, (LPCVOID)(world_chr_man_dbg_ptr + 0x67), &npc_local_control_display, 1, NULL);
				ReadProcessMemory(hProcess, (LPCVOID)(world_chr_man_dbg_ptr + 0x6D), &lod_level_display, 1, NULL);
				ReadProcessMemory(hProcess, (LPCVOID)(world_chr_man_dbg_ptr + 0x138), &ez_state_fix_rand_num, 4, NULL);

				if (ImGui::InputInt("Lv1 Update Count", &lv1_update_count))
				{
					if (lv1_update_count < 1)
					{
						lv1_update_count = 10000;
					}
					else if (lv1_update_count > 10000) {
						lv1_update_count = 1;
					}

					WriteProcessMemory(hProcess, (LPVOID)(world_chr_man_dbg_ptr + 0x24), &lv1_update_count, 4, NULL);
				}

				if (ImGui::InputInt("Lv2 Update Count", &lv2_update_count))
				{
					if (lv2_update_count < 1)
					{
						lv2_update_count = 10000;
					}
					else if (lv2_update_count > 10000) {
						lv2_update_count = 1;
					}

					WriteProcessMemory(hProcess, (LPVOID)(world_chr_man_dbg_ptr + 0x28), &lv2_update_count, 4, NULL);
				}

				if (ImGui::InputFloat("Omitted Update Level Judgment Distance [m] (Drawing Group invalid Lv5 / 30 judgment)", &omitted_distance_drawgroup_invalid))
				{
					if (omitted_distance_drawgroup_invalid < 1.0f)
					{
						omitted_distance_drawgroup_invalid = 10000.0f;
					}
					else if (omitted_distance_drawgroup_invalid > 10000.0f) {
						omitted_distance_drawgroup_invalid = 1.0f;
					}

					WriteProcessMemory(hProcess, (LPVOID)(world_chr_man_dbg_ptr + 0x2C), &omitted_distance_drawgroup_invalid, 4, NULL);
				}

				if (ImGui::InputFloat("Default Update Level Judgment Distance [m] (Lv5 / 30 discrimination outside the screen)", &default_update_distance_whatever))
				{
					if (default_update_distance_whatever < 1.0f)
					{
						default_update_distance_whatever = 10000.0f;
					}
					else if (default_update_distance_whatever > 10000.0f) {
						default_update_distance_whatever = 1.0f;
					}

					WriteProcessMemory(hProcess, (LPVOID)(world_chr_man_dbg_ptr + 0x30), &default_update_distance_whatever, 4, NULL);
				}

				if (ImGui::InputFloat("Omitted Update Level Judgment Distance [m] (Lv5 / 30 discrimination in screen)", &omitted_distance_discrimination_in_screen))
				{
					if (omitted_distance_discrimination_in_screen < 1.0f)
					{
						omitted_distance_discrimination_in_screen = 10000.0f;
					}
					else if (omitted_distance_discrimination_in_screen > 10000.0f) {
						omitted_distance_discrimination_in_screen = 1.0f;
					}

					WriteProcessMemory(hProcess, (LPVOID)(world_chr_man_dbg_ptr + 0x34), &omitted_distance_discrimination_in_screen, 4, NULL);
				}

				if (ImGui::InputFloat("Abbreviated Update Level Judgment Distance [m] (previous frame non-drawing Lv2 judgment)", &abbreviated_update_distance_nondrawing_lv2))
				{
					if (abbreviated_update_distance_nondrawing_lv2 < 1.0f)
					{
						abbreviated_update_distance_nondrawing_lv2 = 10000.0f;
					}
					else if (abbreviated_update_distance_nondrawing_lv2 > 10000.0f) {
						abbreviated_update_distance_nondrawing_lv2 = 1.0f;
					}

					WriteProcessMemory(hProcess, (LPVOID)(world_chr_man_dbg_ptr + 0x38), &abbreviated_update_distance_nondrawing_lv2, 4, NULL);
				}

				if (ImGui::InputFloat("Abbreviated Update Level Judgment Distance [m] (previous frame non-drawing Lv5 judgment)", &abbreviated_update_distance_nondrawing_lv5))
				{
					if (abbreviated_update_distance_nondrawing_lv5 < 1.0f)
					{
						abbreviated_update_distance_nondrawing_lv5 = 10000.0f;
					}
					else if (abbreviated_update_distance_nondrawing_lv5 > 10000.0f) {
						abbreviated_update_distance_nondrawing_lv5 = 1.0f;
					}

					WriteProcessMemory(hProcess, (LPVOID)(world_chr_man_dbg_ptr + 0x3C), &abbreviated_update_distance_nondrawing_lv5, 4, NULL);
				}

				if (ImGui::InputFloat("Omitted Update Level Judgment Distance [m] (No previous frame Lv30 judgment)", &omitted_distance_no_frame_lv30))
				{
					if (omitted_distance_no_frame_lv30 < 1.0f)
					{
						omitted_distance_no_frame_lv30 = 10000.0f;
					}
					else if (omitted_distance_no_frame_lv30 > 10000.0f) {
						omitted_distance_no_frame_lv30 = 1.0f;
					}

					WriteProcessMemory(hProcess, (LPVOID)(world_chr_man_dbg_ptr + 0x40), &omitted_distance_no_frame_lv30, 4, NULL);
				}

				if (ImGui::InputFloat("Abbreviated Update Level Judgment Distance [m] (Ragdoll priority reduction distance)", &abbreviated_update_distance_ragdoll_prio_red_dist))
				{
					if (abbreviated_update_distance_ragdoll_prio_red_dist < 1.0f)
					{
						abbreviated_update_distance_ragdoll_prio_red_dist = 10000.0f;
					}
					else if (abbreviated_update_distance_ragdoll_prio_red_dist > 10000.0f) {
						abbreviated_update_distance_ragdoll_prio_red_dist = 1.0f;
					}

					WriteProcessMemory(hProcess, (LPVOID)(world_chr_man_dbg_ptr + 0x44), &abbreviated_update_distance_ragdoll_prio_red_dist, 4, NULL);
				}

				if (ImGui::Checkbox("Display Update Skip Status (Lv1: Green, Lv2: Blue, Lv5: Red, Lv30: Purple, Off: White)", &display_update_skip_status))
				{
					WriteProcessMemory(hProcess, (LPVOID)(world_chr_man_dbg_ptr + 0x11), &display_update_skip_status, 1, NULL);
				}

				if (ImGui::Checkbox("Hide Characters with Update Lv5 and above", &hide_lv5_chrs))
				{
					WriteProcessMemory(hProcess, (LPVOID)(world_chr_man_dbg_ptr + 0x12), &hide_lv5_chrs, 1, NULL);
				}

				if (ImGui::Checkbox("Update Lv5 Characters to Lv30", &update_lv5_to_lv30))
				{
					WriteProcessMemory(hProcess, (LPVOID)(world_chr_man_dbg_ptr + 0x13), &update_lv5_to_lv30, 1, NULL);
				}

				if (ImGui::Checkbox("NPC Local Control Display", &npc_local_control_display))
				{
					WriteProcessMemory(hProcess, (LPVOID)(world_chr_man_dbg_ptr + 0x67), &npc_local_control_display, 1, NULL);
				}

				if (ImGui::Checkbox("LOD Level Display (Lv0: Green, Lv1: Blue, Lv2: Red)", &lod_level_display))
				{
					WriteProcessMemory(hProcess, (LPVOID)(world_chr_man_dbg_ptr + 0x6D), &lod_level_display, 1, NULL);
				}

				if (ImGui::InputInt("LOD Level to Cast Shadows (if less than this value, cast shadows)", &lod_level_shadows))
				{
					if (lod_level_shadows > 2)
					{
						lod_level_shadows = 2;
					}
					else if (lod_level_shadows < -1) {
						lod_level_shadows = -1;
					}

					WriteProcessMemory(hProcess, (LPVOID)(world_chr_man_dbg_ptr + 0x4C), &lod_level_shadows, 4, NULL);
				}

				int dead_count = 0;

				ReadProcessMemory(hProcess, (LPCVOID)(world_chr_man_dbg_ptr + 0x13C), &dead_count, 4, NULL);

				ImGui::Text("Dead Count[%d]", dead_count);

				if (ImGui::Button("Clear Dead Count"))
				{
					switchAllNoUpdate(0, 2);
				}

				if (ImGui::Button("Check Dead Flag"))
				{
					switchAllNoUpdate(0, 3);
				}

				if (ImGui::Checkbox("Debug Dash Switch", &chrDbgFlags.dbgDash))
				{
					WriteProcessMemory(hProcess, (LPVOID)0x144768F7E, &chrDbgFlags.dbgDash, 1, NULL);
				}

				if (ImGui::InputInt("EzState fix randum integer number", &ez_state_fix_rand_num))
				{
					if (ez_state_fix_rand_num > 100000)
					{
						ez_state_fix_rand_num = -1;
					}
					else if (ez_state_fix_rand_num < -1) {
						ez_state_fix_rand_num = 100000;
					}

					WriteProcessMemory(hProcess, (LPVOID)(world_chr_man_dbg_ptr + 0x138), &ez_state_fix_rand_num, 4, NULL);
				}

				if (ImGui::TreeNode("[Positioning Warp]"))
				{
					__int64 some_ptr = 0;

					if (ReadProcessMemory(hProcess, (LPCVOID)(chr_ptr + 0x80), &some_ptr, 8, NULL))
					{
						if (ReadProcessMemory(hProcess, (LPCVOID)(some_ptr + 0x50), &some_ptr, 8, NULL))
						{
							static float posx = 0.0f;
							static float posy = 0.0f;
							static float posz = 0.0f;

							ReadProcessMemory(hProcess, (LPCVOID)(some_ptr + 0x190), &posx, 4, NULL);
							ReadProcessMemory(hProcess, (LPCVOID)(some_ptr + 0x194), &posy, 4, NULL);
							ReadProcessMemory(hProcess, (LPCVOID)(some_ptr + 0x198), &posz, 4, NULL);

							if (ImGui::InputFloat("X", &posx))
							{
								WriteProcessMemory(hProcess, (LPVOID)(some_ptr + 0x190), &posx, 4, NULL);
							}
							if (ImGui::InputFloat("Y", &posy))
							{
								WriteProcessMemory(hProcess, (LPVOID)(some_ptr + 0x194), &posy, 4, NULL);
							}
							if (ImGui::InputFloat("Z", &posz))
							{
								WriteProcessMemory(hProcess, (LPVOID)(some_ptr + 0x198), &posz, 4, NULL);
							}

							if (ImGui::Button("Execute Warp"))
							{
								char lol = 1;

								WriteProcessMemory(hProcess, (LPVOID)(some_ptr + 0x18A), &lol, 1, NULL);
							}

						}
					}

					ImGui::TreePop();
				}
			}
		}

		ImGui::TreePop();
	}
}

char* Menu::GetMapNameForId(__int64 mapId) 
{

	return (char*)"lol";
}

