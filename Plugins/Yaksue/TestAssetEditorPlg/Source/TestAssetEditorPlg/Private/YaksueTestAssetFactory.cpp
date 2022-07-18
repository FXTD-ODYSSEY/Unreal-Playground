#include "YaksueTestAssetFactory.h"
#include"YaksueTestAsset.h"

#include "AssetTypeCategories.h"

#define LOCTEXT_NAMESPACE "YaksueTest"

UYaksueTestAssetFactory::UYaksueTestAssetFactory(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bCreateNew = true;
	bEditAfterNew = true;//true if the associated editor should be opened after creating a new object
	SupportedClass = UYaksueTestAsset::StaticClass();
}

UObject* UYaksueTestAssetFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	UYaksueTestAsset* CreatedAsset = NewObject<UYaksueTestAsset>(InParent, Class, Name, Flags | RF_Transactional);
	return CreatedAsset;
}

uint32 UYaksueTestAssetFactory::GetMenuCategories() const
{
	return EAssetTypeCategories::Misc;
}

#undef LOCTEXT_NAMESPACE
