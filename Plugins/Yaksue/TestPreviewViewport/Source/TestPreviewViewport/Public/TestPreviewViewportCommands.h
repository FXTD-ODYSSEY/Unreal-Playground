// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "TestPreviewViewportStyle.h"

class FTestPreviewViewportCommands : public TCommands<FTestPreviewViewportCommands>
{
public:

	FTestPreviewViewportCommands()
		: TCommands<FTestPreviewViewportCommands>(TEXT("TestPreviewViewport"), NSLOCTEXT("Contexts", "TestPreviewViewport", "TestPreviewViewport Plugin"), NAME_None, FTestPreviewViewportStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPreviewViewportWindow;
};