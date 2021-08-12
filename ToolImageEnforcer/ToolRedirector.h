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
	bool IsIllegalID(uint32_t id);
	void InjectIconWindows(UTFWin::IWindow* window);

	int AddRef() override;
	int Release() override;
	void* Cast(uint32_t type) const override;
private:
	ToolRedirector();
	~ToolRedirector();

	void ReadModdedPNGs();

	static intrusive_ptr<ToolRedirector> instance;
	eastl::vector<ResourceKey> filteredKeys;
};
