#pragma once

#include <Spore\BasicIncludes.h>
#include "IllegalKeyDefines.h"

#define ToolRedirectorPtr intrusive_ptr<ToolRedirector>
class ToolRedirector 
	: public Object
	, public DefaultRefCounted
{
public:
	static const uint32_t TYPE = id("ToolRedirector");
	static void LoadManager();
	static void Unload();
	static ToolRedirectorPtr GetInstance();
	ToolRedirector();
	~ToolRedirector();
	void ReadModdedPNGs();
	void CreateWindows();
	void DestroyWindows();
	UTFWin::IWindow* TryFindingWindowID(uint32_t controlID);
	int AddRef() override;
	int Release() override;
	void* Cast(uint32_t type) const override;
private:
	static intrusive_ptr<ToolRedirector> instance;
	eastl::vector<ResourceKey> filteredKeys;
	UTFWin::Window* mainWindow;
};
