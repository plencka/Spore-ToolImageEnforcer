#include "stdafx.h"
#include "ToolRedirector.h"

ToolRedirectorPtr ToolRedirector::instance;

ToolRedirector::ToolRedirector()
{
	ReadModdedPNGs();
}

ToolRedirector::~ToolRedirector()
{
}

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

bool ToolRedirector::IsIllegalID(uint32_t id)
{
	for (uint32_t illegalToolImageID : illegalToolImageIDs) {
		if (id == illegalToolImageID) {
			return true;
		}
	}

	return false;
}

void ToolRedirector::ReadModdedPNGs()
{
	eastl::vector<ResourceKey> toolIconKeys;
	auto filter = new StandardFileFilter(ResourceKey::kWildcardID,
		0x3064CB38, //ufotools~
		TypeIDs::png,
		ResourceKey::kWildcardID);

	ResourceManager.GetFileKeys(toolIconKeys, filter);
	for (const ResourceKey& toolIconKey : toolIconKeys) {
		if (!IsIllegalID(toolIconKey.instanceID)) {
			filteredKeys.push_back(toolIconKey);
		}
	}
}

void ToolRedirector::InjectIconWindows(UTFWin::IWindow* window)
{
	for (const ResourceKey& toolIconKey : filteredKeys) {
		intrusive_ptr<UTFWin::IWindow> iconWindow = UTFWin::IImageDrawable::AddImageWindow(
			{ toolIconKey.instanceID, TypeIDs::png, toolIconKey.groupID },
			0, 0, window);

		iconWindow->SetControlID(toolIconKey.instanceID);
		iconWindow->SetFillColor(Color(255, 255, 255, 0));
		iconWindow->SetArea({ 0, 0, 300, 300 });
		iconWindow->SetFlag(UTFWin::kWinFlagVisible, false);
	}
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
