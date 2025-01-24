#include "SMainWidget.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void FMenus::Fill3DMenu(FMenuBuilder& MenuBuilder)
{
	MenuBuilder.BeginSection("3D");
	{
		MenuBuilder.AddSubMenu(FText::FromString("Preset"), FText::FromString("Manage presets"), FNewMenuDelegate::CreateStatic(&FMenus::Fill3DPresetMenu));
		MenuBuilder.AddSubMenu(FText::FromString("Settings"), FText::FromString("Manage settings"), FNewMenuDelegate::CreateStatic(&FMenus::Fill3DSettingsMenu));
	}
	MenuBuilder.EndSection();
}

void FMenus::Fill3DPresetMenu(FMenuBuilder& MenuBuilder)
{
}

void FMenus::Fill3DSettingsMenu(FMenuBuilder& MenuBuilder)
{
}

void SMainWidget::Construct(const FArguments& InArgs)
{
	FMenuBarBuilder MenuBarBuilder (CommandList);
	{
		MenuBarBuilder.AddPullDownMenu(FText::FromString("3D"), FText::FromString("Settings related to 3D dusting"), FNewMenuDelegate::CreateStatic(&FMenus::Fill3DMenu));
		
	}
	
	ChildSlot
	[
		SNew()
	];
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
