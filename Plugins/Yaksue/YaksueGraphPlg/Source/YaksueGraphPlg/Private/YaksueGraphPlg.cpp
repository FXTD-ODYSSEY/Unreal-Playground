// Copyright Epic Games, Inc. All Rights Reserved.

#include "YaksueGraphPlg.h"
#include "YaksueGraphPlgStyle.h"
#include "YaksueGraphPlgCommands.h"
#include "SYaksueGraphWindow.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"

#include "EdGraphNode_Yaksue.h"
#include "SYaksueGraphNode.h"

static const FName YaksueGraphPlgTabName("YaksueGraphPlg");

#define LOCTEXT_NAMESPACE "FYaksueGraphPlgModule"

//定义图表节点工厂
class FYaksueGraphNodeFactory : public FGraphPanelNodeFactory
{
	virtual TSharedPtr<class SGraphNode> CreateNode(UEdGraphNode* Node) const override
	{
		if (UEdGraphNode_Yaksue* YaksueGraphNode = Cast<UEdGraphNode_Yaksue>(Node))
		{
			return SNew(SYaksueGraphNode, YaksueGraphNode);
		}

		return nullptr;
	}
};

void FYaksueGraphPlgModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FYaksueGraphPlgStyle::Initialize();
	FYaksueGraphPlgStyle::ReloadTextures();

	FYaksueGraphPlgCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FYaksueGraphPlgCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FYaksueGraphPlgModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FYaksueGraphPlgModule::RegisterMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(YaksueGraphPlgTabName, FOnSpawnTab::CreateRaw(this, &FYaksueGraphPlgModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FYaksueGraphPlgTabTitle", "YaksueGraphPlg"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
	
	FEdGraphUtilities::RegisterVisualNodeFactory(MakeShareable(new FYaksueGraphNodeFactory()));
}

void FYaksueGraphPlgModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FYaksueGraphPlgStyle::Shutdown();

	FYaksueGraphPlgCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(YaksueGraphPlgTabName);
}

TSharedRef<SDockTab> FYaksueGraphPlgModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FYaksueGraphPlgModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("YaksueGraphPlg.cpp"))
		);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SYaksueGraphWindow)
		];
}

void FYaksueGraphPlgModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(YaksueGraphPlgTabName);
}

void FYaksueGraphPlgModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FYaksueGraphPlgCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FYaksueGraphPlgCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FYaksueGraphPlgModule, YaksueGraphPlg)