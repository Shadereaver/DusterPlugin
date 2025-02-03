#include "DusterDetailsCustomization.h"

#include "DetailCategoryBuilder.h"
#include "DetailLayoutBuilder.h"
#include "DusterDetails.h"
#include "IDetailGroup.h"
#include "PropertyCustomizationHelpers.h"
#include "Widgets/Text/SRichTextBlock.h"

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
		.ToolTipText(FText::FromString("Name of the preset."))
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
			.ToolTipText(FText::FromString("Save the current settings under the current name."))
			.ButtonColorAndOpacity(FSlateColor(FLinearColor(0, 5, 224)))
		]
	];
	
	SettingsGroup3D.AddPropertyRow(DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(UDusterDetails, Material)))
	.GetPropertyHandle()->SetToolTipText(FText::FromString("The material applied to the generated mesh."));
	SettingsGroup3D.AddPropertyRow(DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(UDusterDetails, Height)))
	.GetPropertyHandle()->SetToolTipText(FText::FromString("The distance from the base mesh surface to the top of the generated mesh."));
	SettingsGroup3D.AddPropertyRow(DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(UDusterDetails, Falloff)))
	.GetPropertyHandle()->SetToolTipText(FText::FromString("The slope from the bottom to the top of the generated mesh."));

	SettingsGroup3D.AddWidgetRow()
	.ValueContent()
	[
		SNew(SHorizontalBox)
		+SHorizontalBox::Slot()
		.AutoWidth()
		[
			SNew(SButton)
			.Text(FText::FromString(TEXT("Add")))
			.HAlign(HAlign_Center)
			.OnClicked(FOnClicked::CreateStatic(&UDusterDetails::Add))
			.ToolTipText(FText::FromString("Add a mesh to selected actors."))
			
		]
		+SHorizontalBox::Slot()
		.AutoWidth()
		[
			SNew(SButton)
			.Text(FText::FromString("Remove"))
			.HAlign(HAlign_Center)
			.OnClicked(FOnClicked::CreateStatic(&UDusterDetails::Remove))
			.ToolTipText(FText::FromString("Remove generated mesh from selected actors."))
			.ButtonColorAndOpacity(FSlateColor(FLinearColor(255, 0 , 0)))
		]
	];

	IDetailCategoryBuilder& Category2D = DetailBuilder.EditCategory("2D");
	IDetailGroup& PresetGroup2D = Category2D.AddGroup(TEXT("PresetGroup"), FText::FromString("Preset"));
	IDetailGroup& SettingsGroup2D = Category2D.AddGroup(TEXT("Settings"), FText::FromString("Settings"));
	
	PresetGroup2D.EnableReset(true);
	SettingsGroup2D.EnableReset(true);

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
		.ToolTipText(FText::FromString("Name of the preset."))
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
			.ToolTipText(FText::FromString("Save the current settings under the current name."))
			.ButtonColorAndOpacity(FSlateColor(FLinearColor(0, 5, 224)))
		]
	];

	SettingsGroup2D.AddPropertyRow(DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(UDusterDetails, Texture)))
	.GetPropertyHandle()->SetToolTipText(FText::FromString("The texture to use."));
	SettingsGroup2D.AddPropertyRow(DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(UDusterDetails, Material2)))
	.GetPropertyHandle()->SetToolTipText(FText::FromString("The material to use."));

	SettingsGroup2D.AddWidgetRow()
	.ValueContent()
	[
		SNew(SButton)
		.Text(FText::FromString("Create material"))
		.HAlign(HAlign_Right)
		.OnClicked(FOnClicked::CreateStatic(&UDusterDetails::Mat))
		.ToolTipText(FText::FromString("Create a new material with the required parameters."))
	];
	
	SettingsGroup2D.AddPropertyRow(DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(UDusterDetails, Density)))
	.GetPropertyHandle()->SetToolTipText(FText::FromString("The density of coverage."));

	const FSimpleDelegate OnValueChanged = FSimpleDelegate::CreateLambda([&DetailBuilder]()
	{
		DetailBuilder.ForceRefreshDetails();
	});
	
	IDetailPropertyRow& Sided = SettingsGroup2D.AddPropertyRow(DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(UDusterDetails, bPointAt)));
	Sided.ToolTip(FText::FromString("Toggle between individual side control or a single decal pointing at an actor."));
	Sided.DisplayName(FText::FromString("Sided"));
	Sided.GetPropertyHandle()->SetOnPropertyValueChanged(OnValueChanged);

	bool bSided;
	Sided.GetPropertyHandle()->GetValue(bSided);
	
	IDetailPropertyRow& ActorPointAt = SettingsGroup2D.AddPropertyRow(DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(UDusterDetails, Actor)));
	ActorPointAt.ToolTip(FText::FromString("The Actor the dust will point at."));
	ActorPointAt.IsEnabled(!bSided);
	
	if (bSided)
	{
		for (int i = 0; i < 6; i++)
		{
			IDetailGroup& SubGroup = SettingsGroup2D.AddGroup(*FString::Printf(TEXT("Side %d"), i), FText::FromString(FString::Printf(TEXT("Side %d"), i)));
			
			IDetailPropertyRow& ActorOverride = SubGroup.AddPropertyRow(DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(UDusterDetails, Actor)));
			ActorOverride.DisplayName(FText::FromString("Point to actor"));
			ActorOverride.ToolTip(FText::FromString("Point the decal at the give actor for this face"));
			
			bool bEditActor;
			ActorOverride.EditCondition(bEditActor, FOnBooleanValueChanged::CreateLambda([&bEditActor, &DetailBuilder](bool Edit)
			{
				bEditActor = Edit;
				DetailBuilder.ForceRefreshDetails();
			}));
			
			IDetailPropertyRow& DensityOverride = SubGroup.AddPropertyRow(DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(UDusterDetails, OverrideDensity)));
			DensityOverride.DisplayName(FText::FromString("Override Density"));
			DensityOverride.ToolTip(FText::FromString("Override the density for this face"));

			bool bEditDensity;
			DensityOverride.EditCondition(bEditDensity, FOnBooleanValueChanged::CreateLambda([&bEditDensity, &DetailBuilder](bool Edit)
			{
				bEditDensity = Edit;
				DetailBuilder.ForceRefreshDetails();
			}));

			SubGroup.AddWidgetRow()
			.ValueContent()
			[
				SNew(SHorizontalBox)
				+SHorizontalBox::Slot()
				.AutoWidth()
				[
					SNew(SButton)
					.Text(FText::FromString(TEXT("Add")))
					.HAlign(HAlign_Center)
					.OnClicked(FOnClicked::CreateStatic(&UDusterDetails::Add))
					.ToolTipText(FText::FromString("Add a Decal to selected actors."))
					
				]
				+SHorizontalBox::Slot()
				.AutoWidth()
				[
					SNew(SButton)
					.Text(FText::FromString("Remove"))
					.HAlign(HAlign_Center)
					.OnClicked(FOnClicked::CreateStatic(&UDusterDetails::Remove))
					.ToolTipText(FText::FromString("Remove Decal from selected actors."))
					.ButtonColorAndOpacity(FSlateColor(FLinearColor(255, 0 , 0)))
				]
			];
		}
	}
	else
	{
		SettingsGroup2D.AddWidgetRow()
			.ValueContent()
			[
				SNew(SHorizontalBox)
				+SHorizontalBox::Slot()
				.AutoWidth()
				[
					SNew(SButton)
					.Text(FText::FromString(TEXT("Add")))
					.HAlign(HAlign_Center)
					.OnClicked(FOnClicked::CreateStatic(&UDusterDetails::Add))
					.ToolTipText(FText::FromString("Add a Decal to selected actors."))
					
				]
				+SHorizontalBox::Slot()
				.AutoWidth()
				[
					SNew(SButton)
					.Text(FText::FromString("Remove"))
					.HAlign(HAlign_Center)
					.OnClicked(FOnClicked::CreateStatic(&UDusterDetails::Remove))
					.ToolTipText(FText::FromString("Remove Decal from selected actors."))
					.ButtonColorAndOpacity(FSlateColor(FLinearColor(255, 0 , 0)))
				]
			];
	}
}

TSharedRef<IDetailCustomization> FDusterDetailsCustomization::MakeInstance()
{
	return MakeShareable(new FDusterDetailsCustomization);
}
