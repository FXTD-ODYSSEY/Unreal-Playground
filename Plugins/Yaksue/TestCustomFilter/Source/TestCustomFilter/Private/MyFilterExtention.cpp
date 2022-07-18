#include "MyFilterExtention.h"
#include "MyFilter.h"


void UMyFilterExtention::AddFrontEndFilterExtensions(TSharedPtr<class FFrontendFilterCategory> DefaultCategory, TArray< TSharedRef<class FFrontendFilter> >& InOutFilterList) const
{
	// 注册MyFilter
	InOutFilterList.Add(MakeShareable(new FMyFilter(DefaultCategory)));
}
