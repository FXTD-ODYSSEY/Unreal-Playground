// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "YaksueGraphPlgStyle.h"

class FYaksueGraphPlgCommands : public TCommands<FYaksueGraphPlgCommands>
{
public:

	FYaksueGraphPlgCommands()
		: TCommands<FYaksueGraphPlgCommands>(TEXT("YaksueGraphPlg"), NSLOCTEXT("Contexts", "YaksueGraphPlg", "YaksueGraphPlg Plugin"), NAME_None, FYaksueGraphPlgStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};