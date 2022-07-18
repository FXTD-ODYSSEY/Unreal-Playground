#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "ContentBrowserFrontEndFilterExtension.h"

#include "MyFilterExtention.generated.h"

UCLASS()
class UMyFilterExtention : public UContentBrowserFrontEndFilterExtension
{
public:
	GENERATED_BODY()

	// UContentBrowserFrontEndFilterExtension interface
	virtual void AddFrontEndFilterExtensions(TSharedPtr<class FFrontendFilterCategory> DefaultCategory, TArray< TSharedRef<class FFrontendFilter> >& InOutFilterList) const override;
	// End of UContentBrowserFrontEndFilterExtension interface
};
