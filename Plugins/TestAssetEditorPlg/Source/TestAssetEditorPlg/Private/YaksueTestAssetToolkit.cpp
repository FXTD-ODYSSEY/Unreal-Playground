#include"YaksueTestAssetToolkit.h"

#include"Widgets/Docking/SDockTab.h"
#include"Widgets/Input/SButton.h"

#define LOCTEXT_NAMESPACE "YaksueTest"

class UYaksueTestAsset* EditingAsset;//正在编辑的Asset

const FName FYaksueTestAssetToolkit::TestTabId(TEXT("YaksueTestAssetEditor_TestTab"));

FName FYaksueTestAssetToolkit::GetToolkitFName() const
{
	return FName("YaksueTestAssetName");
}

FText FYaksueTestAssetToolkit::GetBaseToolkitName() const
{
	return LOCTEXT("YaksueTestAssetLabel", "YaksueTestAssetBase");
}

FString FYaksueTestAssetToolkit::GetWorldCentricTabPrefix() const
{
	return LOCTEXT("YaksueTestAssetTabPrefix", "YaksueTestAssetPrefix ").ToString();
}

FLinearColor FYaksueTestAssetToolkit::GetWorldCentricTabColorScale() const
{
	return FLinearColor(0,0.5f,0.6f,0.5f);
}

TSharedRef<SDockTab> FYaksueTestAssetToolkit::SpawnTestTab(const FSpawnTabArgs& Args)
{
	return
		SNew(SDockTab)
		[
			SNew(SVerticalBox)
			+SVerticalBox::Slot().AutoHeight()
			[
				SNew(STextBlock)
				.Text(FText::FromString(FString::FromInt(EditingAsset->TestData)))
			]
			+SVerticalBox::Slot().AutoHeight()
			[
				SNew(SButton)
				.Text(FText::FromString("TestJoJo!"))
				.OnClicked_Lambda([this]() {EditingAsset->TestData++; return FReply::Handled(); })
			]
		];
}


void FYaksueTestAssetToolkit::RegisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager)
{
	
	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);

	InTabManager->RegisterTabSpawner(TestTabId, FOnSpawnTab::CreateSP(this, &FYaksueTestAssetToolkit::SpawnTestTab))
		.SetDisplayName(LOCTEXT("YaksueTestAssetTestTab", "YaksueTestAssetTestTab"));
}

void FYaksueTestAssetToolkit::Initialize(const EToolkitMode::Type Mode, const TSharedPtr< class IToolkitHost >& InitToolkitHost, UYaksueTestAsset* Asset)
{
    EditingAsset = Asset;

	TSharedRef<FTabManager::FLayout> Layout = FTabManager::NewLayout("YaksueTestAssetEditor_Layout")
		->AddArea
		(
			FTabManager::NewPrimaryArea()->SetOrientation(Orient_Vertical)
			->Split
			(
				FTabManager::NewSplitter()->SetOrientation(Orient_Horizontal)->SetSizeCoefficient(0.9f)
				->Split
				(
					FTabManager::NewStack()
					->SetSizeCoefficient(0.7f)
					->AddTab(TestTabId, ETabState::OpenedTab)
				)
			)
		);

	const bool bCreateDefaultStandaloneMenu = true;
	const bool bCreateDefaultToolbar = true;
	const FName AppIdentifier = TEXT("YaksueTestAssetEditor");
	FAssetEditorToolkit::InitAssetEditor(Mode, InitToolkitHost, AppIdentifier, Layout, bCreateDefaultStandaloneMenu, bCreateDefaultToolbar, Asset);
}

#undef LOCTEXT_NAMESPACE
