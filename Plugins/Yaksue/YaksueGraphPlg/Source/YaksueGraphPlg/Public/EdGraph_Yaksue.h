#pragma once

#include "CoreMinimal.h"
#include "EdGraphNode_Yaksue.h"
#include "UObject/ObjectMacros.h"
#include "EdGraph/EdGraph.h"

#include "EdGraph_Yaksue.generated.h"


UCLASS()
class UEdGraph_Yaksue : public UEdGraph
{
	GENERATED_UCLASS_BODY()

    //重新构建图表
    void RebuildGraph();
};
