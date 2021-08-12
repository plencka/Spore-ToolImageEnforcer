// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include <Spore/App/cGameModeManager.h>
#include "ToolRedirector.h"

void Initialize()
{
	ToolRedirector::LoadManager();
}

void Dispose()
{
	ToolRedirector::Unload();
}

member_detour(FindWindowByID_detour, UTFWin::UILayout, UTFWin::IWindow* (uint32_t, bool)) {
	UTFWin::IWindow* detoured(uint32_t controlID,
		bool bRecursive) {
		if (this->mResourceKey.instanceID == 0x46fed9c8) { // InstanceID of layout used to create icons in inventory
			if (auto redirectInstance = ToolRedirector::GetInstance()) {
				if (auto iconWindow = redirectInstance->TryFindingWindowID(controlID)) {
					return iconWindow;
				}
			}
		}
		return original_function(this, controlID,
				bRecursive);
	}
};


member_detour(GameModeEnter_detour, App::cGameModeManager, bool(const char*)) {
	bool detoured(const char* pName) {
		if (strcmp(pName, "Game_Space") == 0) {
			if (auto redirectInstance = ToolRedirector::GetInstance()) {
					redirectInstance->CreateWindows();
			}
		}
		/*else { // This might be done by the parent window managed by the base game! Also conflicts with gameMode change cheats!
			if (auto redirectInstance = ToolRedirector::GetInstance()) {
				redirectInstance->DestroyWindows();
			}
		}*/
		return original_function(this, pName);
	}
};

void AttachDetours()
{
	FindWindowByID_detour::attach(GetAddress(UTFWin::UILayout, FindWindowByID));
	GameModeEnter_detour::attach(GetAddress(App::cGameModeManager, SetActiveModeByName));
}


// Generally, you don't need to touch any code here
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		ModAPI::AddPostInitFunction(Initialize);
		ModAPI::AddDisposeFunction(Dispose);

		PrepareDetours(hModule);
		AttachDetours();
		CommitDetours();
		break;

	case DLL_PROCESS_DETACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		break;
	}
	return TRUE;
}

