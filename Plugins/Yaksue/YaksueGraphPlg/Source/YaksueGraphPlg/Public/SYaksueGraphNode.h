#pragma once

#include "CoreMinimal.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "SGraphNode.h"

class UEdGraphNode_Yaksue;

class SYaksueGraphNode : public SGraphNode
{
public:
	SLATE_BEGIN_ARGS(SYaksueGraphNode){}

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct( const FArguments& InArgs, UEdGraphNode_Yaksue* InNode );

	// SGraphNode implementation
	virtual void UpdateGraphNode() override;
	// End SGraphNode implementation
};
