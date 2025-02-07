#include "DusterInfo2DCustomisation.h"

#include "DetailWidgetRow.h"
#include "DusterControl.h"
#include "IDetailChildrenBuilder.h"

void FDusterInfo2DCustomisation::CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle,
	FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils)
{
}

void FDusterInfo2DCustomisation::CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle,
	IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils)
{
	ChildBuilder.AddProperty(PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FLocalDusterInfo2D, Texture)).ToSharedRef())
	.GetPropertyHandle()->SetToolTipText(FText::FromString("The texture to use."));
	ChildBuilder.AddProperty(PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FLocalDusterInfo2D, Material)).ToSharedRef())
	.GetPropertyHandle()->SetToolTipText(FText::FromString("The material to use."));

	ChildBuilder.AddCustomRow(FText::FromString("2D Create material"))
	.ValueContent()
	[
		SNew(SButton)
		.Text(FText::FromString("Create material"))
		.HAlign(HAlign_Right)
		//.OnClicked(FOnClicked::CreateStatic(&UDusterDetails::Mat))
		.ToolTipText(FText::FromString("Create a new material with the required parameters."))
	];
	
	ChildBuilder.AddProperty(PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FLocalDusterInfo2D, Density)).ToSharedRef())
	.GetPropertyHandle()->SetToolTipText(FText::FromString("The density of coverage."));
	/*
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
	*/
}

TSharedRef<IPropertyTypeCustomization> FDusterInfo2DCustomisation::MakeInstance()
{
	return MakeShareable(new FDusterInfo2DCustomisation);
}
