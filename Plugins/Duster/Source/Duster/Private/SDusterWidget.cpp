#include "SDusterWidget.h"

#include "DusterControl.h"
#include "DusterSubsystem.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SDusterWidget::Construct(const FArguments& InArgs)
{
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

	FDetailsViewArgs Args;

	Args.bHideSelectionTip = true;

	PropertyWidget = PropertyModule.CreateDetailView(Args);
	
	PropertyWidget->SetObject(GEditor->GetEditorSubsystem<UDusterSubsystem>()->GetDusterControl());
	
	ChildSlot
	[
		PropertyWidget.ToSharedRef()
	];
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
