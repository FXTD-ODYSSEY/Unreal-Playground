// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "TestSPanelStyle.h"

class FTestSPanelCommands : public TCommands<FTestSPanelCommands>
{
public:
	FTestSPanelCommands()
		: TCommands<FTestSPanelCommands>(TEXT("TestSPanel"), NSLOCTEXT("Contexts", "TestSPanel", "TestSPanel Plugin"), NAME_None, FTestSPanelStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr<FUICommandInfo> OpenSPanel;
};