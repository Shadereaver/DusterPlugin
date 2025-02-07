#include "DusterDetailsCustomization.h"

#include "DetailLayoutBuilder.h"
#include "DusterSubsystem.h"
#include "IDetailGroup.h"

void FDusterDetailsCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	TSharedRef<UDusterControl> DusterControl = GEditor->GetEditorSubsystem<UDusterSubsystem>()->GetDusterControl().ToSharedRef();
	
	IDetailCategoryBuilder& Category3D = DetailBuilder.EditCategory("3D");
	IDetailGroup& PresetGroup3D = Category3D.AddGroup(TEXT("PresetGroup"), FText::FromString("Preset"));

	IDetailPropertyRow& Preset3D = PresetGroup3D.AddPropertyRow(DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(UDusterControl, Current3DPreset)));
	Preset3D.GetPropertyHandle()->SetOnPropertyValueChanged(FSimpleDelegate::CreateSP(DusterControl, &UDusterControl::Preset3DChanged));
	
	IDetailCategoryBuilder& Category2D = DetailBuilder.EditCategory("2D");
	IDetailGroup& PresetGroup2D = Category2D.AddGroup(TEXT("PresetGroup"), FText::FromString("Preset"));
	
	IDetailPropertyRow& Preset2D = PresetGroup2D.AddPropertyRow(DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(UDusterControl, Current2DPreset)));
	Preset2D.GetPropertyHandle()->SetOnPropertyValueChanged(FSimpleDelegate::CreateSP(DusterControl, &UDusterControl::Preset2DChanged));

	
	/*
	PresetGroup2D.AddWidgetRow()
	.ValueContent()
	[
		SNew(SHorizontalBox)
		+SHorizontalBox::Slot()
		[
			SNew(SProperty, DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(UDusterInfo2D, Name)))
			.ShouldDisplayName(false)
		]
		+SHorizontalBox::Slot()
		.AutoWidth()
		[
			SNew(SButton)
			.Text(FText::FromString("Save"))
			.HAlign(HAlign_Right)
			.OnClicked(FOnClicked::CreateStatic(&UDusterDetails::Save))
			.ToolTipText(FText::FromString("Save the current settings under the current name."))
			.ButtonColorAndOpacity(FSlateColor(FLinearColor(0, 5, 224)))
		]
	];
	
	
	PresetGroup3D.AddWidgetRow()
	.ValueContent()
	[
		SNew(SHorizontalBox)
		+SHorizontalBox::Slot()
		.AutoWidth()
		[
			SNew(SButton)
			.Text(FText::FromString("Save"))
			.HAlign(HAlign_Right)
			.OnClicked(FOnClicked::CreateStatic(&UDusterDetails::Save))
			.ToolTipText(FText::FromString("Save the current settings under the current name."))
			.ButtonColorAndOpacity(FSlateColor(FLinearColor(0, 5, 224)))
		]
	];

	*/
}

TSharedRef<IDetailCustomization> FDusterDetailsCustomization::MakeInstance()
{
	return MakeShareable(new FDusterDetailsCustomization);
}
