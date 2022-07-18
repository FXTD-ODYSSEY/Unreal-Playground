// Copyright Epic Games, Inc. All Rights Reserved.

#include "TestLayoutWindowCommands.h"

#define LOCTEXT_NAMESPACE "FTestLayoutWindowModule"

void FTestLayoutWindowCommands::RegisterCommands()
{
	UI_COMMAND(OpenLayoutWindow, "TestLayoutWindow", "Bring up TestLayoutWindow window", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
