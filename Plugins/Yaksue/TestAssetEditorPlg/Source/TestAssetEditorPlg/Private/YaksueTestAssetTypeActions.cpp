#include "YaksueTestAssetTypeActions.h"

#define LOCTEXT_NAMESPACE "YaksueTest"

FYaksueTestAssetTypeActions::FYaksueTestAssetTypeActions(EAssetTypeCategories::Type InAssetCategory)
{
	AssetCategory = InAssetCategory;
}

uint32 FYaksueTestAssetTypeActions::GetCategories()
{
	return AssetCategory;
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
