// Copyright Epic Games, Inc. All Rights Reserved.

#include "TestSPanel.h"
#include "TestSPanelStyle.h"
#include "TestSPanelCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"

static const FName TestSPanelTabName("TestSPanel");

#define LOCTEXT_NAMESPACE "FTestSPanelModule"

void FTestSPanelModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	FTestSPanelStyle::Initialize();
	FTestSPanelStyle::ReloadTextures();

	FTestSPanelCommands::Register();

	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FTestSPanelCommands::Get().OpenSPanel,
		FExecuteAction::CreateRaw(this, &FTestSPanelModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FTestSPanelModule::RegisterMenus));

	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(TestSPanelTabName, FOnSpawnTab::CreateRaw(this, &FTestSPanelModule::OnSpawnPluginTab)).SetDisplayName(LOCTEXT("FTestSPanelTabTitle", "TestSPanel")).SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FTestSPanelModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FTestSPanelStyle::Shutdown();

	FTestSPanelCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(TestSPanelTabName);
}

TSharedRef<SDockTab> FTestSPanelModule::OnSpawnPluginTab(const FSpawnTabArgs &SpawnTabArgs)
{
	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
			[
				// Put your tab content here!
				SNew(SOverlay) + SOverlay::Slot()													//底层
									 [SNew(SHorizontalBox) + SHorizontalBox::Slot().FillWidth(0.3f) //占30%
																 [SNew(SButton)] +
									  SHorizontalBox::Slot().FillWidth(0.7f)						  //占70%
										  [SNew(SVerticalBox) + SVerticalBox::Slot().FillHeight(0.5f) //占50%
																	[SNew(SButton)] +
										   SVerticalBox::Slot().FillHeight(0.5f) //占50%
											   [SNew(SButton)]]] +
				SOverlay::Slot()												   //顶层
					[SNew(SHorizontalBox) + SHorizontalBox::Slot().FillWidth(1.0f) //占满剩余空间
					 + SHorizontalBox::Slot().AutoWidth()
						   [SNew(SVerticalBox) + SVerticalBox::Slot().FillHeight(1.0f) //占满剩余空间
							+ SVerticalBox::Slot().AutoHeight()
								  [SNew(SBox)
									   .HeightOverride(128)
									   .WidthOverride(128)
										   [SNew(SButton)]] +
							SVerticalBox::Slot().FillHeight(1.0f) //占满剩余空间
	] + SHorizontalBox::Slot().FillWidth(1.0f)					  //占满剩余空间
	]

	];
}

void FTestSPanelModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(TestSPanelTabName);
}

void FTestSPanelModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu *Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection &Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FTestSPanelCommands::Get().OpenSPanel, PluginCommands);
		}
	}

	{
		UToolMenu *ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection &Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry &Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FTestSPanelCommands::Get().OpenSPanel));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FTestSPanelModule, TestSPanel)