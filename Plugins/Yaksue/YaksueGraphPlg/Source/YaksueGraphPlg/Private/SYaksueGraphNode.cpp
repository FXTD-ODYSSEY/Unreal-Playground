#include "SYaksueGraphNode.h"
#include "EdGraphNode_Yaksue.h"
#include "Widgets/Input/SButton.h"

void SYaksueGraphNode::Construct( const FArguments& InArgs, UEdGraphNode_Yaksue* InNode )
{
	GraphNode = InNode;
	UpdateGraphNode();
}

void SYaksueGraphNode::UpdateGraphNode()
{
	GetOrAddSlot( ENodeZone::Center )
	[
		SNew(SButton).Text(FText::FromString("Hello Yaksue"))
	];
}
