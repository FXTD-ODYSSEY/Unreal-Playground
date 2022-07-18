#include "YaksueTestAssetTypeActions.h"
#include "YaksueTestAsset.h"

#define LOCTEXT_NAMESPACE "YaksueTest"

FYaksueTestAssetTypeActions::FYaksueTestAssetTypeActions()
{	
	// UE_LOG(LogTemp, Warning, TEXT("FAvatarAssetTypeActions::FAvatarAssetTypeActions"));
	// IAssetTools& AssetToolsModule=FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
    // AvatarAssetCategory = AssetToolsModule.RegisterAdvancedAssetCategory(FName(TEXT("Avatar")), LOCTEXT("AvatarAssetCategory", "Avatar"));
}

// Asset的名字
FText FYaksueTestAssetTypeActions::GetName() const
{
	return LOCTEXT("YaksueTestAssetTypeActions", "YaksueTestAsset");
}
// Asset图标的颜色
FColor FYaksueTestAssetTypeActions::GetTypeColor() const
{
	return FColor(0, 255, 255);
}
// Asset的UObject是什么
UClass *FYaksueTestAssetTypeActions::GetSupportedClass() const
{
	return UYaksueTestAsset::StaticClass();
}
// Asset所属的分类
uint32 FYaksueTestAssetTypeActions::GetCategories()
{
	// return AvatarAssetCategory;
	return EAssetTypeCategories::Misc;
}

void FYaksueTestAssetTypeActions::OpenAssetEditor(const TArray<UObject *> &InObjects, TSharedPtr<IToolkitHost> EditWithinLevelEditor)
{
	EToolkitMode::Type Mode = EToolkitMode::Standalone;

	for (auto ObjIt = InObjects.CreateConstIterator(); ObjIt; ++ObjIt)
	{
		auto Asset = Cast<UYaksueTestAsset>(*ObjIt);
		if (Asset != NULL)
		{
			TSharedRef<FYaksueTestAssetToolkit> NewToolkit(new FYaksueTestAssetToolkit());
			NewToolkit->Initialize(Mode, EditWithinLevelEditor, Asset);
		}
	}
}

#undef LOCTEXT_NAMESPACE
