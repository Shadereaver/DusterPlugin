#include "DusterDetailsCustomization.h"

#include "DetailCategoryBuilder.h"
#include "DetailLayoutBuilder.h"
#include "DusterDetails.h"
#include "IDetailGroup.h"
#include "PropertyCustomizationHelpers.h"

void FDusterDetailsCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	IDetailCategoryBuilder& Category3D = DetailBuilder.EditCategory("3D");
	IDetailGroup& PresetGroup3D = Category3D.AddGroup(TEXT("PresetGroup"), FText::FromString("Preset"));
	IDetailGroup& SettingsGroup3D = Category3D.AddGroup(TEXT("Settings"), FText::FromString("Settings"));
	PresetGroup3D.EnableReset(true);
	SettingsGroup3D.EnableReset(true);

	PresetGroup3D.AddWidgetRow()
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
	
	PresetGroup3D.AddWidgetRow()
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
	
	SettingsGroup3D.AddPropertyRow(DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(UDusterDetails, Material)));
	SettingsGroup3D.AddPropertyRow(DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(UDusterDetails, Height)));
	SettingsGroup3D.AddPropertyRow(DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(UDusterDetails, Falloff)));

	SettingsGroup3D.AddWidgetRow()
	.ValueContent()
	[
		SNew(SButton)
		.Text(FText::FromString("Add"))
		.HAlign(HAlign_Center)
		.OnClicked(FOnClicked::CreateStatic(&UDusterDetails::Add))
	];

	IDetailCategoryBuilder& Category2D = DetailBuilder.EditCategory("2D");
	IDetailGroup& PresetGroup2D = Category2D.AddGroup(TEXT("PresetGroup"), FText::FromString("Preset"));
	IDetailGroup& SettingsGroup2D = Category2D.AddGroup(TEXT("Settings"), FText::FromString("Settings"));

	PresetGroup2D.AddWidgetRow()
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

	PresetGroup2D.AddWidgetRow()
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

	SettingsGroup2D.AddPropertyRow(DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(UDusterDetails, Texture)));
	SettingsGroup2D.AddPropertyRow(DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(UDusterDetails, Material2)));
	SettingsGroup2D.AddPropertyRow(DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(UDusterDetails, Density)));

	PresetGroup2D.EnableReset(true);
	SettingsGroup2D.EnableReset(true);

	SettingsGroup2D.AddPropertyRow(DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(UDusterDetails, Actor)));

	for (int i = 0; i < 6; i++)
	{
		IDetailGroup& SubGroup = SettingsGroup2D.AddGroup(*FString::Printf(TEXT("Side %d"), i), FText::FromString(FString::Printf(TEXT("Side %d"), i)));
		SubGroup.AddWidgetRow()
		.NameContent()
		[
			SNew(STextBlock)
			.Text(FText::FromString("Point to actor override"))
		]
		.ValueContent()
		[
			SNew(SCheckBox)
			.OnCheckStateChanged(FOnCheckStateChanged::CreateStatic(&UDusterDetails::Checkbox, i))
		];
		SubGroup.AddPropertyRow(DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(UDusterDetails, Actor))).DisplayName(FText::FromString("Override Actor"));
		SubGroup.AddPropertyRow(DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(UDusterDetails, Density))).DisplayName(FText::FromString("Override Density"));
	}
}

TSharedRef<IDetailCustomization> FDusterDetailsCustomization::MakeInstance()
{
	return MakeShareable(new FDusterDetailsCustomization);
}
