// Copyright Epic Games, Inc. All Rights Reserved.

#include "AssetToolsModule.h"
#include "YaksueTestAssetTypeActions.h"
#include "TestAssetEditorPlg.h"

#define LOCTEXT_NAMESPACE "FTestAssetEditorPlgModule"

void FTestAssetEditorPlgModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	IAssetTools &AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	// AssetCategory = AssetTools.RegisterAdvancedAssetCategory(FName(TEXT("MyDefined")), FText::FromName(TEXT("MyDefined")));
	// AssetCategory = AssetTools.RegisterAdvancedAssetCategory(FName(TEXT("Custom Asset")), LOCTEXT("CustomAsset", "Custom Asset"));
	// AssetTools.RegisterAssetTypeActions(MakeShareable(new FYaksueTestAssetTypeActions()));

    EAssetTypeCategories::Type AssetCategory = AssetTools.RegisterAdvancedAssetCategory(FName(TEXT("Avatar")), LOCTEXT("AvatarAssetCategory", "Avatar"));
	TSharedPtr<FYaksueTestAssetTypeActions> AssetTypeAction = MakeShareable(new FYaksueTestAssetTypeActions(AssetCategory));
	AssetTools.RegisterAssetTypeActions(AssetTypeAction.ToSharedRef());
}

void FTestAssetEditorPlgModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FTestAssetEditorPlgModule, TestAssetEditorPlg)