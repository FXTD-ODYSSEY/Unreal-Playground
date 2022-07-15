#pragma once

#include "Factories/Factory.h"

#include "YaksueTestAssetFactory.generated.h"

UCLASS(config = Editor)
class UYaksueTestAssetFactory : public UFactory
{
    GENERATED_UCLASS_BODY()
public:
	// UFactory interface
	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
	virtual uint32 GetMenuCategories() const override;
	// End of UFactory interface
};
