#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "DusterStyle.h"

struct FDusterCommands : TCommands<FDusterCommands>
{
public:
	FDusterCommands() : TCommands<FDusterCommands>(TEXT("Duster"), NSLOCTEXT("Contexts", "Duster", "Duster Plugin"),
		NAME_None, FDusterStyle::GetStyleSetName())
	{
	}

	virtual void RegisterCommands() override;

	TSharedPtr<FUICommandInfo> OpenPluginWindow;
};
