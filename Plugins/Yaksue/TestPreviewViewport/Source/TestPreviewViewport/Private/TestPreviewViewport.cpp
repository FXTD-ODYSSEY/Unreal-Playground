// Copyright Epic Games, Inc. All Rights Reserved.

#include "TestPreviewViewport.h"
#include "STestLevelEditorViewport.h"
#include "STestEditorViewport.h"
#include "TestPreviewViewportStyle.h"
#include "TestPreviewViewportCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"

static const FName TestPreviewViewportTabName("TestPreviewViewport");
static const FName IntterTabName_EditorViewport("EditorViewport");
static const FName IntterTabName_CustomViewport("CustomViewport");

#define LOCTEXT_NAMESPACE "FTestPreviewViewportModule"

void FTestPreviewViewportModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	FTestPreviewViewportStyle::Initialize();
	FTestPreviewViewportStyle::ReloadTextures();

	FTestPreviewViewportCommands::Register();

	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FTestPreviewViewportCommands::Get().OpenPreviewViewportWindow,
		FExecuteAction::CreateRaw(this, &FTestPreviewViewportModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FTestPreviewViewportModule::RegisterMenus));

	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(TestPreviewViewportTabName, FOnSpawnTab::CreateRaw(this, &FTestPreviewViewportModule::OnSpawnPluginTab)).SetDisplayName(LOCTEXT("FTestPreviewViewportTabTitle", "TestPreviewViewport")).SetMenuType(ETabSpawnerMenuType::Hidden);

	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(IntterTabName_EditorViewport, FOnSpawnTab::CreateLambda([](const FSpawnTabArgs& SpawnTabArgs)
	{
		return
			SNew(SDockTab)
			.TabRole(ETabRole::NomadTab)
			[
				SNew(STestLevelEditorViewport)
			];
	}))
	.SetDisplayName(FText::FromName(IntterTabName_EditorViewport))
	.SetMenuType(ETabSpawnerMenuType::Hidden);

	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(IntterTabName_CustomViewport, FOnSpawnTab::CreateLambda([](const FSpawnTabArgs& SpawnTabArgs)
	{
		return
			SNew(SDockTab)
			.TabRole(ETabRole::NomadTab)
			[
				SNew(STestEditorViewport)
			];
	}))
	.SetDisplayName(FText::FromName(IntterTabName_CustomViewport))
	.SetMenuType(ETabSpawnerMenuType::Hidden);

}

void FTestPreviewViewportModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FTestPreviewViewportStyle::Shutdown();

	FTestPreviewViewportCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(TestPreviewViewportTabName);
}

TSharedRef<SDockTab> FTestPreviewViewportModule::OnSpawnPluginTab(const FSpawnTabArgs &SpawnTabArgs)
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
		TabManagerLayout = FTabManager::NewLayout("ViewportLayout")
			->AddArea
			(
				FTabManager::NewPrimaryArea()
				->SetOrientation(Orient_Horizontal)
				->Split
				(
					FTabManager::NewStack()
					->SetSizeCoefficient(.4f)
					->AddTab(IntterTabName_EditorViewport, ETabState::OpenedTab)
				)
				->Split
				(
					FTabManager::NewStack()
					->SetSizeCoefficient(.4f)
					->AddTab(IntterTabName_CustomViewport, ETabState::OpenedTab)
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

void FTestPreviewViewportModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(TestPreviewViewportTabName);
}

void FTestPreviewViewportModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu *Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection &Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FTestPreviewViewportCommands::Get().OpenPreviewViewportWindow, PluginCommands);
		}
	}

	{
		UToolMenu *ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection &Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry &Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FTestPreviewViewportCommands::Get().OpenPreviewViewportWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FTestPreviewViewportModule, TestPreviewViewport)