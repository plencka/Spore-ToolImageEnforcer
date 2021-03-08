#include "stdafx.h"
#include "ToolRedirector.h"

ToolRedirectorPtr ToolRedirector::instance;

void ToolRedirector::LoadManager()
{
	instance = new ToolRedirector();
}

void ToolRedirector::Unload()
{
	instance = nullptr;
}

ToolRedirectorPtr ToolRedirector::GetInstance()
{
	return instance;
}

ToolRedirector::ToolRedirector()
{
	ReadModdedPNGs();
}


ToolRedirector::~ToolRedirector()
{
	DestroyWindows();
}

void ToolRedirector::ReadModdedPNGs()
{
	eastl::vector<ResourceKey> keys;
	auto filter = new StandardFileFilter(ResourceKey::kWildcardID,
		0x3064CB38,
		0x2F7D0004,
		ResourceKey::kWildcardID); //ufotools~, png

	ResourceManager.GetFileKeys(keys, filter);
	for (auto& key : keys) { // Inefficient, but only ran once per runtime
		bool isIllegal = false;
		for (auto illegalToolImageID : illegalToolImageIDs) {
			if (key.instanceID == illegalToolImageID) {
				isIllegal = true;
			}
		}
		if (!isIllegal) {
			filteredKeys.push_back(key);
		}
	}
}

void ToolRedirector::CreateWindows()
{
	mainWindow = new UTFWin::Window();
	mainWindow->SetControlID(id("ToolEnfoncer_Control"));
	WindowManager.GetMainWindow()->AddWindow(mainWindow);
	for (auto& key : filteredKeys) {
		auto win = UTFWin::IImageDrawable::AddImageWindow({ key.instanceID, TypeIDs::png, key.groupID }, 0, 0, mainWindow);
		win->SetControlID(key.instanceID);
		win->SetFillColor(Color(255, 255, 255, 0));
		win->SetArea({ 0, 0, 300, 300 });
		win->SetFlag(UTFWin::kWinFlagVisible, false);
	}
}

void ToolRedirector::DestroyWindows()
{
	if (mainWindow) {
		WindowManager.GetMainWindow()->DisposeWindowFamily(mainWindow);
		mainWindow = nullptr;
	}
}

UTFWin::IWindow* ToolRedirector::TryFindingWindowID(uint32_t controlID)
{
	if (mainWindow) {
		return mainWindow->FindWindowByID(controlID, true);
	}
	return nullptr;
}

// For internal use, do not modify.
int ToolRedirector::AddRef()
{
	return DefaultRefCounted::AddRef();
}

// For internal use, do not modify.
int ToolRedirector::Release()
{
	return DefaultRefCounted::Release();
}

// You can extend this function to return any other types your class implements.
void* ToolRedirector::Cast(uint32_t type) const
{
	CLASS_CAST(Object);
	CLASS_CAST(ToolRedirector);
	return nullptr;
}
