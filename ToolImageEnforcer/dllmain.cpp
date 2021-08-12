// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "ToolRedirector.h"

void Initialize()
{
	ToolRedirector::LoadManager();
}

void Dispose()
{
	ToolRedirector::Unload();
}

member_detour(LoadSPUI_detour, UTFWin::UILayout, bool (const ResourceKey&, bool, uint32_t)) {
	bool detoured(const ResourceKey & resourceKey, bool unkBool, uint32_t unkParams) {
		bool result = original_function(this, resourceKey, unkBool, unkParams);
		if (resourceKey.instanceID == 0x46fed9c8) {
			intrusive_ptr<UTFWin::UILayout> layout = this;
			auto firstIcon = layout->FindWindowByID(0xC19CCD88); // First icon from spui. Should be the fastest to access.
			if (intrusive_ptr<ToolRedirector> toolRedirectorInstance = ToolRedirector::GetInstance()) {
				toolRedirectorInstance->InjectIconWindows(firstIcon); // Icons should be destroyed with hierarchy
			}
		}

		return result;
	}
};

void AttachDetours()
{
	LoadSPUI_detour::attach(GetAddress(UTFWin::UILayout, Load));
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
