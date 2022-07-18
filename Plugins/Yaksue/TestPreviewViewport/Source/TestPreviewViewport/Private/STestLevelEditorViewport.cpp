#include "STestLevelEditorViewport.h"

#include "EditorViewportClient.h"

void STestLevelEditorViewport::Construct(const FArguments &InArgs)
{
	SEditorViewport::Construct(SEditorViewport::FArguments());
}
STestLevelEditorViewport::STestLevelEditorViewport()
{
}
STestLevelEditorViewport::~STestLevelEditorViewport()
{
}

TSharedRef<FEditorViewportClient> STestLevelEditorViewport::MakeEditorViewportClient()
{
	TSharedPtr<FEditorViewportClient> EditorViewportClient = MakeShareable(new FEditorViewportClient(nullptr));

	return EditorViewportClient.ToSharedRef();
}
