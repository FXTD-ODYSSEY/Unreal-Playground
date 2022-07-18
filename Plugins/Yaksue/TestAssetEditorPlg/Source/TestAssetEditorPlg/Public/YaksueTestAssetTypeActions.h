#pragma once

#include "AssetTypeActions_Base.h"
#include "YaksueTestAsset.h"
#include "YaksueTestAssetToolkit.h"

class FYaksueTestAssetTypeActions : public FAssetTypeActions_Base
{
public:
	FYaksueTestAssetTypeActions(EAssetTypeCategories::Type InAssetCategory);

	// Asset的名字
	virtual FText GetName() const override { return FText::FromName(TEXT("YaksueTestAsset")); }
	// Asset图标的颜色
	virtual FColor GetTypeColor() const override { return FColor(0, 255, 255); }
	// Asset的UObject是什么
	virtual UClass *GetSupportedClass() const override { return UYaksueTestAsset::StaticClass(); }
	// Asset所属的分类
	virtual uint32 GetCategories() override;

	virtual void OpenAssetEditor(const TArray<UObject *> &InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor = TSharedPtr<IToolkitHost>()) override;

private:
	EAssetTypeCategories::Type AssetCategory;
};
