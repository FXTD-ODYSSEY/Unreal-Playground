
#include"STestEditorViewport.h"

#include"EditorViewportClient.h"
#include"PreviewScene.h"
#include"SCommonEditorViewportToolbarBase.h"

void STestEditorViewport::Construct(const FArguments& InArgs)
{
	SEditorViewport::Construct(SEditorViewport::FArguments());
}
STestEditorViewport::STestEditorViewport()
{
}
STestEditorViewport::~STestEditorViewport()
{
}

TSharedRef<FEditorViewportClient> STestEditorViewport::MakeEditorViewportClient()
{
	PreviewScene = MakeShareable(new FPreviewScene());

	//向预览场景中加一个测试模型
	{
		//读取模型
		UStaticMesh* SM = LoadObject<UStaticMesh>(NULL, TEXT("StaticMesh'/Engine/EngineMeshes/Cube.Cube'"), NULL, LOAD_None, NULL);
		//创建组件
		UStaticMeshComponent* SMC = NewObject<UStaticMeshComponent>();
		SMC->SetStaticMesh(SM);
		//向预览场景中增加组件
		PreviewScene->AddComponent(SMC, FTransform::Identity);		
	}

	TSharedPtr<FEditorViewportClient> EditorViewportClient = MakeShareable(new FEditorViewportClient(nullptr, PreviewScene.Get()));

	return EditorViewportClient.ToSharedRef();
}

TSharedPtr<SWidget> STestEditorViewport::MakeViewportToolbar()
{
	return SNew(SCommonEditorViewportToolbarBase, SharedThis(this));
}

TSharedRef<class SEditorViewport> STestEditorViewport::GetViewportWidget()
{
	return SharedThis(this);
}

TSharedPtr<FExtender> STestEditorViewport::GetExtenders() const
{
	TSharedPtr<FExtender> Result(MakeShareable(new FExtender));
	return Result;
}

void STestEditorViewport::OnFloatingButtonClicked()
{
}
