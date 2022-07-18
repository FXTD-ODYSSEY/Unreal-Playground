#include "MyFilter.h"

#define LOCTEXT_NAMESPACE "MyFilter"

// 颜色
FLinearColor FMyFilter::GetColor() const
{
	return FLinearColor::Yellow;
}

// 引擎内部的标识名称，不可重复
FString FMyFilter::GetName() const
{
	return TEXT("MyFilter");
}

// 显示名
FText FMyFilter::GetDisplayName() const
{
	return LOCTEXT("MyFilterDisplay", "MyFilter");
}

// 鼠标指针移到Filter列表上时显示的提示
FText FMyFilter::GetToolTipText() const
{
	return LOCTEXT("MyDisplayTooltip", "This is my Filter");
}

// Filter的主要逻辑
// 内容浏览器中显示的文件夹下的每个文件都经过这个判断。
bool FMyFilter::PassesFilter(FAssetFilterType InItem) const
{
	//当前逻辑：过滤掉开头为“temp”的资源
	return !InItem.AssetName.ToString().StartsWith("temp");
}

#undef LOCTEXT_NAMESPACE
