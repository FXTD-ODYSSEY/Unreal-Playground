#pragma once

#include "CoreMinimal.h"
#include "SEditorViewport.h"

class STestLevelEditorViewport : public SEditorViewport
{
public:
	SLATE_BEGIN_ARGS(STestLevelEditorViewport) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
	STestLevelEditorViewport();
	~STestLevelEditorViewport();
	
protected:
	/** SEditorViewport interface */
	virtual TSharedRef<FEditorViewportClient> MakeEditorViewportClient() override;
	

};
