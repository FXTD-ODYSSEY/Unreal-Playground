// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FToolBarBuilder;
class FMenuBuilder;

class FTestLayoutWindowModule : public IModuleInterface
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	/** This function will be bound to Command (by default it will bring up plugin window) */
	void PluginButtonClicked();
	void AddMenuExtension(FMenuBuilder &Builder);
	void AddToolbarExtension(FToolBarBuilder &Builder);

protected:
	TSharedPtr<class FTabManager> TabManager;
	TSharedPtr<FTabManager::FLayout> TabManagerLayout;
	
private:
	void RegisterMenus();

	TSharedRef<class SDockTab> OnSpawnPluginTab(const class FSpawnTabArgs &SpawnTabArgs);
	TSharedPtr<class FUICommandList> PluginCommands;


};
