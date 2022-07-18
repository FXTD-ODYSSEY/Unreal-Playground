// Copyright Epic Games, Inc. All Rights Reserved.

#include "TestPreviewViewportCommands.h"

#define LOCTEXT_NAMESPACE "FTestPreviewViewportModule"

void FTestPreviewViewportCommands::RegisterCommands()
{
	UI_COMMAND(OpenPreviewViewportWindow, "TestPreviewViewport", "Bring up TestPreviewViewport window", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
