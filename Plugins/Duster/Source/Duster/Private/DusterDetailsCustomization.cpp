#include "DusterDetailsCustomization.h"

#include "DetailCategoryBuilder.h"
#include "DetailLayoutBuilder.h"
#include "DusterDetails.h"
#include "IDetailGroup.h"
#include "PropertyCustomizationHelpers.h"

void FDusterDetailsCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	IDetailCategoryBuilder& ThickCategory = DetailBuilder.EditCategory("3D");
	IDetailGroup& PresetGroup = ThickCategory.AddGroup(TEXT("PresetGroup"), FText::FromString("Preset"));

	PresetGroup.AddWidgetRow()
	.NameContent()
	[
		SNew(STextBlock)
		.Text(FText::FromString("Preset"))
	]
	.ValueContent()
	[
		SNew(SComboBox<TSharedPtr<UDusterDetails>>)
		[
			SNew(STextBlock)
			.Text(FText::FromString("Select preset"))
		]
	];
	PresetGroup.AddWidgetRow()
	.NameContent()
	[
		SNew(STextBlock)
		.Text(FText::FromString("Name"))
	]
	.ValueContent()
	[
		SNew(SHorizontalBox)
		+SHorizontalBox::Slot()
		[
			SNew(SProperty, DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(UDusterDetails, Name)))
			.ShouldDisplayName(false)
		]
		+SHorizontalBox::Slot()
		.AutoWidth()
		[
			SNew(SButton)
			.Text(FText::FromString("Save"))
			.HAlign(HAlign_Right)
			.OnClicked(FOnClicked::CreateStatic(&UDusterDetails::Save))
		]
	];
}

TSharedRef<IDetailCustomization> FDusterDetailsCustomization::MakeInstance()
{
	return MakeShareable(new FDusterDetailsCustomization);
}
