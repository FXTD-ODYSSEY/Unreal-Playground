#pragma once

#include "UObject/Object.h"

#include "YaksueTestAsset.generated.h"

UCLASS(EditInlineNew, config = Engine)
class UYaksueTestAsset : public UObject
{
	GENERATED_UCLASS_BODY()
public:

	UPROPERTY(EditAnywhere)
	int TestData;
};
