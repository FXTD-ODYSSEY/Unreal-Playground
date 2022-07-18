// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "TestLayoutWindow.h"
#include "TestLayoutWindowStyle.h"
#include "TestLayoutWindowCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"

static const FName TestLayoutWindowTabName("TestLayoutWindow");
static const FName InnerTabName("InnerTab");
static const FName InnerTabName2("InnerTab2");


#define LOCTEXT_NAMESPACE "FTestLayoutWindowModule"

void FTestLayoutWindowModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FTestLayoutWindowStyle::Initialize();
	FTestLayoutWindowStyle::ReloadTextures();

	FTestLayoutWindowCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FTestLayoutWindowCommands::Get().OpenLayoutWindow,
		FExecuteAction::CreateRaw(this, &FTestLayoutWindowModule::PluginButtonClicked),
		FCanExecuteAction());
		
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	
	{
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
		MenuExtender->AddMenuExtension("WindowLayout", EExtensionHook::After, PluginCommands, FMenuExtensionDelegate::CreateRaw(this, &FTestLayoutWindowModule::AddMenuExtension));

		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	}
	
	{
		TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
		ToolbarExtender->AddToolBarExtension("Settings", EExtensionHook::After, PluginCommands, FToolBarExtensionDelegate::CreateRaw(this, &FTestLayoutWindowModule::AddToolbarExtension));
		
		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	}
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(TestLayoutWindowTabName, FOnSpawnTab::CreateRaw(this, &FTestLayoutWindowModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FTestLayoutWindowTabTitle", "TestLayoutWindow"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);

	//InnerTab的内容：
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(InnerTabName, FOnSpawnTab::CreateLambda([](const FSpawnTabArgs& SpawnTabArgs)
	{
		return
			SNew(SDockTab)
			.TabRole(ETabRole::NomadTab)
			[
				SNew(STextBlock)
				.Text(FText::FromString("InnerTab"))
			];
	}))
	.SetDisplayName(LOCTEXT("InnerTab", "InnerTab"))
	.SetMenuType(ETabSpawnerMenuType::Hidden);

	//InnerTab2的内容：
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(InnerTabName2, FOnSpawnTab::CreateLambda([](const FSpawnTabArgs& SpawnTabArgs)
	{
		return
			SNew(SDockTab)
			.TabRole(ETabRole::NomadTab)
			[
				SNew(STextBlock)
				.Text(FText::FromString("InnerTab2"))
			];
	}))
	.SetDisplayName(LOCTEXT("InnerTab2", "InnerTab2"))
	.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FTestLayoutWindowModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FTestLayoutWindowStyle::Shutdown();

	FTestLayoutWindowCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(TestLayoutWindowTabName);
}

TSharedRef<SDockTab> FTestLayoutWindowModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	//原来的分页：
	const TSharedRef<SDockTab> NomadTab = SNew(SDockTab)
		.TabRole(ETabRole::NomadTab);

	//创建TabManager
	if (!TabManager.IsValid())
	{
		TabManager = FGlobalTabmanager::Get()->NewTabManager(NomadTab);
	}

	//创建布局：
	if (!TabManagerLayout.IsValid())
	{
		TabManagerLayout = FTabManager::NewLayout("TestLayoutWindow")
			->AddArea
			(
				FTabManager::NewPrimaryArea()
				->SetOrientation(Orient_Vertical)
				->Split
				(
					FTabManager::NewStack()
					->SetSizeCoefficient(.4f)
					->AddTab(InnerTabName, ETabState::OpenedTab)
				)
				->Split
				(
					FTabManager::NewStack()
					->SetSizeCoefficient(.4f)
					->AddTab(InnerTabName2, ETabState::OpenedTab)
				)
			);

	}

	//从布局中恢复得到控件
	TSharedRef<SWidget> TabContents = TabManager->RestoreFrom(TabManagerLayout.ToSharedRef(), TSharedPtr<SWindow>()).ToSharedRef();

	//设置内容控件
	NomadTab->SetContent(
		TabContents
	);

	return NomadTab;
}

void FTestLayoutWindowModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->InvokeTab(TestLayoutWindowTabName);
}

void FTestLayoutWindowModule::AddMenuExtension(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(FTestLayoutWindowCommands::Get().OpenLayoutWindow);
}

void FTestLayoutWindowModule::AddToolbarExtension(FToolBarBuilder& Builder)
{
	Builder.AddToolBarButton(FTestLayoutWindowCommands::Get().OpenLayoutWindow);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FTestLayoutWindowModule, TestLayoutWindow)
