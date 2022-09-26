#include "SYaksueGraphWindow.h"
#include "EdGraph_Yaksue.h"
#include "YaksueGraphSchema.h"


void SYaksueGraphWindow::Construct(const FArguments& InArgs)
{
	//创建图表对象
	GraphObj = NewObject<UEdGraph_Yaksue>();
	GraphObj->Schema = UYaksueGraphSchema::StaticClass();
	GraphObj->AddToRoot();
	
    GraphObj->RebuildGraph();
    
	//创建图表编辑器控件
	GraphEditorPtr = SNew(SGraphEditor)
		.GraphToEdit(GraphObj);
		

	//指定本控件的UI：
	ChildSlot
	[
		GraphEditorPtr.ToSharedRef()
	];
}
