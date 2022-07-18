#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "FrontendFilterBase.h"

// 自定义Filter
class FMyFilter : public FFrontendFilter
{
public:
	FMyFilter(TSharedPtr<FFrontendFilterCategory> InCategory)
		: FFrontendFilter(InCategory)
	{
	}

	// FFrontendFilter implementation
	virtual FLinearColor GetColor() const override;
	virtual FString GetName() const override;
	virtual FText GetDisplayName() const override;
	virtual FText GetToolTipText() const override;
	// End of FFrontendFilter implementation

	// IFilter implementation
	virtual bool PassesFilter(FAssetFilterType InItem) const override;
	// End of IFilter implementation
};
