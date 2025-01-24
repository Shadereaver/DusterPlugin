#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

class FMenus
{
public:
	static void Fill3DMenu(FMenuBuilder& MenuBuilder);

protected:
	static void Fill3DPresetMenu(FMenuBuilder& MenuBuilder);
	static void Fill3DSettingsMenu(FMenuBuilder& MenuBuilder);
};

class DUSTER_API SMainWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SMainWidget)
	{}
	SLATE_END_ARGS()

	SMainWidget() : CommandList(new FUICommandList){}

	void Construct(const FArguments& InArgs);

protected:
	TSharedRef<FUICommandList> CommandList;
};
