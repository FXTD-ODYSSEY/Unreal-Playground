// Copyright Epic Games, Inc. All Rights Reserved.

#include "TestSPanelCommands.h"

#define LOCTEXT_NAMESPACE "FTestSPanelModule"

void FTestSPanelCommands::RegisterCommands()
{
	UI_COMMAND(OpenSPanel, "TestSPanel", "Bring up TestSPanel window", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
