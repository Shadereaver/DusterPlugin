#include "DusterInfo2DCustomisation.h"

#include "DetailLayoutBuilder.h"
#include "DetailWidgetRow.h"
#include "DusterControl.h"
#include "DusterInfo2D.h"
#include "DusterSubsystem.h"
#include "IDetailChildrenBuilder.h"
#include "IDetailGroup.h"

void FDusterInfo2DCustomisation::CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle,
                                                 FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils)
{
}

void FDusterInfo2DCustomisation::CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle,
	IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils)
{
	TObjectPtr<UDusterControl> DusterControl = GEditor->GetEditorSubsystem<UDusterSubsystem>()->GetDusterControl();

	
	ChildBuilder.AddProperty(PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FLocalDusterInfo2D, Texture)).ToSharedRef())
	.GetPropertyHandle()->SetToolTipText(FText::FromString("The texture to use for the decal."));
	ChildBuilder.AddProperty(PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FLocalDusterInfo2D, Material)).ToSharedRef())
	.GetPropertyHandle()->SetToolTipText(FText::FromString("The material to use for the decal."));

	ChildBuilder.AddCustomRow(FText::FromString("2D Create material"))
	.ValueContent()
	[
		SNew(SButton)
		.Text(FText::FromString("Create material"))
		.HAlign(HAlign_Right)
		.OnClicked(FOnClicked::CreateUObject(DusterControl, &UDusterControl::Create2DMaterial))
		.ToolTipText(FText::FromString("Create a new material with the required parameters."))
	];
	
	ChildBuilder.AddProperty(PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FLocalDusterInfo2D, Density)).ToSharedRef())
	.GetPropertyHandle()->SetToolTipText(FText::FromString("The density of coverage."));

	IDetailLayoutBuilder& LayoutBuilder = ChildBuilder.GetParentCategory().GetParentLayout();

	const FSimpleDelegate OnValueChanged = FSimpleDelegate::CreateLambda([&LayoutBuilder]()
	{
		LayoutBuilder.ForceRefreshDetails();
	});
	
	
	IDetailPropertyRow& Sided = ChildBuilder.AddProperty(PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FLocalDusterInfo2D, bSided)).ToSharedRef());
	Sided.ToolTip(FText::FromString("Toggle between individual side control or a single decal pointing at an actor."));
	Sided.DisplayName(FText::FromString("Sided"));
	Sided.GetPropertyHandle()->SetOnPropertyValueChanged(OnValueChanged);

	bool bSided;
	Sided.GetPropertyHandle()->GetValue(bSided);
	
	IDetailPropertyRow& ActorPointAt = ChildBuilder.AddProperty(PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FLocalDusterInfo2D, ActorToPointAt)).ToSharedRef());
	ActorPointAt.ToolTip(FText::FromString("The Actor the dust will point at."));
	ActorPointAt.IsEnabled(!bSided);
	
	if (bSided)
	{
		for (int i = 0; i < 6; i++)
		{
			IDetailGroup& SubGroup = ChildBuilder.AddGroup(*FString::Printf(TEXT("Side %d"), i), FText::FromString(FString::Printf(TEXT("Side %d"), i)));

			
			IDetailPropertyRow& ActorOverride = SubGroup.AddPropertyRow(PropertyHandle->GetChildHandle(*FString::Printf(TEXT("Sides[%d].ActorToPointAt"), i)).ToSharedRef());
			ActorOverride.DisplayName(FText::FromString("Point to actor"));
			ActorOverride.ToolTip(FText::FromString("Point the decal at the give actor for this face"));
			
			TSharedPtr<IPropertyHandle> OverrideActor = PropertyHandle->GetChildHandle(*FString::Printf(TEXT("Sides[%d].bOverrideActor"), i));
			bool bOverrideActor;
			OverrideActor->GetValue(bOverrideActor);
			
			ActorOverride.EditCondition(bOverrideActor, FOnBooleanValueChanged::CreateLambda([&bOverrideActor](bool Edit)
			{
				bOverrideActor = Edit;
			}));
			
			IDetailPropertyRow& DensityOverride = SubGroup.AddPropertyRow(PropertyHandle->GetChildHandle(*FString::Printf(TEXT("Sides[%d].DensityOverride"), i)).ToSharedRef());
			DensityOverride.DisplayName(FText::FromString("Override Density"));
			DensityOverride.ToolTip(FText::FromString("Override the density for this face"));

			TSharedPtr<IPropertyHandle> OverrideDensity = PropertyHandle->GetChildHandle(*FString::Printf(TEXT("Sides[%d].bOverrideDensity"), i));
			bool bOverrideDensity;
			OverrideDensity->GetValue(bOverrideDensity);
			
			DensityOverride.EditCondition(bOverrideDensity, FOnBooleanValueChanged::CreateLambda([&bOverrideDensity](bool Edit)
			{
				bOverrideDensity = Edit;
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
					//.OnClicked(FOnClicked::CreateUObject(DusterControl)
					.ToolTipText(FText::FromString("Add a Decal to selected actors."))
					
				]
				+SHorizontalBox::Slot()
				.AutoWidth()
				[
					SNew(SButton)
					.Text(FText::FromString("Remove"))
					.HAlign(HAlign_Center)
					//.OnClicked(FOnClicked::CreateStatic(&UDusterDetails::Remove))
					.ToolTipText(FText::FromString("Remove Decal from selected actors."))
					.ButtonColorAndOpacity(FSlateColor(FLinearColor(255, 0 , 0)))
				]
			];
		}
	}
	else
	{
		ChildBuilder.AddCustomRow(FText::FromString("2D Controls"))
			.ValueContent()
			[
				SNew(SHorizontalBox)
				+SHorizontalBox::Slot()
				.AutoWidth()
				[
					SNew(SButton)
					.Text(FText::FromString(TEXT("Add")))
					.HAlign(HAlign_Center)
					//.OnClicked(FOnClicked::CreateUObject(DusterControl, &UDusterDetails::Add))
					.ToolTipText(FText::FromString("Add a Decal to selected actors."))
					
				]
				+SHorizontalBox::Slot()
				.AutoWidth()
				[
					SNew(SButton)
					.Text(FText::FromString("Remove"))
					.HAlign(HAlign_Center)
					//.OnClicked(FOnClicked::CreateStatic(&UDusterDetails::Remove))
					.ToolTipText(FText::FromString("Remove Decal from selected actors."))
					.ButtonColorAndOpacity(FSlateColor(FLinearColor(255, 0 , 0)))
				]
			];
	}
}

TSharedRef<IPropertyTypeCustomization> FDusterInfo2DCustomisation::MakeInstance()
{
	return MakeShareable(new FDusterInfo2DCustomisation);
}
