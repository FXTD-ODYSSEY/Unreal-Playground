#pragma once

#include "AssetTypeActions_Base.h"

class FYaksueTestAssetTypeActions : public FAssetTypeActions_Base
{
public:
	//Asset的名字
	virtual FText GetName() const override;
	//Asset图标的颜色
	virtual FColor GetTypeColor() const override;
	//Asset的UObject是什么
	virtual UClass* GetSupportedClass() const override;
	//Asset所属的分类
	virtual uint32 GetCategories() override;
	
	virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor = TSharedPtr<IToolkitHost>()) override;

};
