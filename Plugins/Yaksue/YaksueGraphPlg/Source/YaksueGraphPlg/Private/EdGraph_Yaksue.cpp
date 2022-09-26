#include "EdGraph_Yaksue.h"


UEdGraph_Yaksue::UEdGraph_Yaksue(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}


void UEdGraph_Yaksue::RebuildGraph()
{
	//创建一个节点
	CreateNode(UEdGraphNode_Yaksue::StaticClass());
}
