// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "TestLayoutWindowStyle.h"

class FTestLayoutWindowCommands : public TCommands<FTestLayoutWindowCommands>
{
public:
	FTestLayoutWindowCommands()
		: TCommands<FTestLayoutWindowCommands>(TEXT("TestLayoutWindow"), NSLOCTEXT("Contexts", "TestLayoutWindow", "TestLayoutWindow Plugin"), NAME_None, FTestLayoutWindowStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr<FUICommandInfo> OpenLayoutWindow;
};