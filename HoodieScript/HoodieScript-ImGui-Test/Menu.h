#pragma once
#include "ImGui/imgui.h"
#include <HoodieScript-ImGui-Test/imgui_impl_dx11.h>

class Menu
{

public:

	Menu();
	~Menu();

	bool IsOpen = true;
	void Render();

private:

	typedef struct {
		bool dbgPlayerNoDead;
		bool dbgPlayerExterminate;
		bool dbgAllNoStaminaConsume;
		bool dbgAllNoMPConsume;
		bool dbgAllNoArrowConsume;
		bool dbgAllNoMagicQtyConsume;
		bool dbgPlayerHide;
		bool dbgPlayerSilence;
		bool dbgAllNoDead;
		bool dbgAllNoDamage;
		bool dbgAllNoHit;
		bool dbgAllNoAttack;
		bool dbgAllNoMove;
		bool dbgAllNoUpdateAi;
		bool dbgAllNoWepProtDurabilityDamage;
		bool dbgAllNoArtsPointConsume;
		bool dbgForcedParryMode;
		bool dbgInsufficiencyTest;
		bool dbgAllOmissionMode;
		bool unk_144768F7B;
		bool dbgTestLogOutputForNet;
		bool dbgSphereCastB4AttachLeader;
		bool dbgDash;
		bool dbgPlayerReload;
		bool dbgIsEnableBehFlags;
		bool dbgIsEnableAnimPlaybackSpeed;
		bool dbgIsActivateTestParams;
		bool dbgIsEnableAnimMovAdjustment;
		bool dbgIsEnablePlayerBehFlags;
		bool dbgIsEnablePlayerAnimPlaybackSpeed;
		bool dbgIsEnablePlayerTestParams;
		bool dbgIsEnablePlayerAnimMovAdjustment;
	} chrDbgFlags;

	chrDbgFlags chrDbgFlags;

	void RenderHitInsMenu();
	void RenderHitInsWorldBlockHit(__int64);
	void RenderChrInsMenu();
	void RenderWorldChrMan(__int64);
	//void RenderWorldChrMan_c0000(__int64);
	void RenderWorldChrManChrEntry(__int64, bool);
	void RenderChrDbg();
	char* GetMapNameForId(__int64);

	
};

