// Copyright Epic Games, Inc. All Rights Reserved.

#include "DusterCommands.h"

#define LOCTEXT_NAMESPACE "FDusterModule"

void FDusterCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "Duster", "Open Duster", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
