#pragma once

#include "CoreMinimal.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/SCompoundWidget.h"
#include "GraphEditor.h"


class SYaksueGraphWindow : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SYaksueGraphWindow){}

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct( const FArguments& InArgs );

	//图表编辑器控件
	TSharedPtr<SGraphEditor> GraphEditorPtr;

	//图表对象
	class UEdGraph_Yaksue* GraphObj;
};
