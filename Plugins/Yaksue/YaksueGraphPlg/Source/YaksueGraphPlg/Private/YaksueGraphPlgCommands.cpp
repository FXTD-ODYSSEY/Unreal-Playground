// Copyright Epic Games, Inc. All Rights Reserved.

#include "YaksueGraphPlgCommands.h"

#define LOCTEXT_NAMESPACE "FYaksueGraphPlgModule"

void FYaksueGraphPlgCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "YaksueGraphPlg", "Bring up YaksueGraphPlg window", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
