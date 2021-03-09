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

class ToolRedirectDebugCheat : public ArgScript::ICommand
{
public:
	const char* ToolRedirectDebugCheat::GetDescription(ArgScript::DescriptionMode mode) const
	{
		if (mode == ArgScript::DescriptionMode::Basic) {
			return "ToolImageEnforcer: Add space tool from given name.";
		}
		else {
			return "ToolImageEnforcer: Add space tool to player inventory from provided name. Also adds specified use charge if tool is consumable.";
		}
	}

	void ParseLine(const ArgScript::Line& line) override
	{
		size_t numArgs;
		auto args = line.GetArgumentsRange(&numArgs, 1, 2);
		if (Simulator::IsSpaceGame()) {
			cSpaceToolDataPtr tool;
			if (!SimulatorSpaceGame.GetPlayerInventory()->GetUnlockableTool({ id(args[0]), 0, 0 })) {
				App::ConsolePrintF("Tool does not exists.");
				return;
			}
			ToolManager.LoadTool({ id(args[0]), 0, 0 }, tool);
			if (numArgs == 2) {
				tool->mCurrentAmmoCount = mpFormatParser->ParseInt(args[1]);
			}

			auto inventory = SimulatorSpaceGame.GetPlayerInventory();
			inventory->AddItem(tool.get());
		}
		else {
			App::ConsolePrintF("You must be in Space Game to use this cheat.");
		}
	}
};