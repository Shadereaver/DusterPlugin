#include "DusterInfo2DCustomisation.h"

#include "DetailLayoutBuilder.h"
#include "DetailWidgetRow.h"
#include "DusterControl.h"
#include "DusterSubsystem.h"
#include "IDetailChildrenBuilder.h"
#include "IDetailGroup.h"
#include "PropertyCustomizationHelpers.h"

void FDusterInfo2DCustomisation::CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle,
                                                 FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils)
{
}

void FDusterInfo2DCustomisation::CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle,
	IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils)
{
	TObjectPtr<UDusterControl> DusterControl = GEditor->GetEditorSubsystem<UDusterSubsystem>()->GetDusterControl();

	
	IDetailPropertyRow& Texture = ChildBuilder.AddProperty(PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FLocalDusterInfo2D, Texture)).ToSharedRef());
	Texture.GetPropertyHandle()->SetToolTipText(FText::FromString("The texture to use for the decal."));
	Texture.GetPropertyHandle()->SetOnPropertyValueChanged(FSimpleDelegate::CreateUObject(DusterControl, &UDusterControl::Update2D));
	
	IDetailPropertyRow& Material = ChildBuilder.AddProperty(PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FLocalDusterInfo2D, Material)).ToSharedRef());
	Material.GetPropertyHandle()->SetToolTipText(FText::FromString("The material to use for the decal."));
	Material.GetPropertyHandle()->SetOnPropertyValueChanged(FSimpleDelegate::CreateUObject(DusterControl, &UDusterControl::Update2D));

	ChildBuilder.AddCustomRow(FText::FromString("2D Create material"))
	.ValueContent()
	[
		SNew(SButton)
		.Text(FText::FromString("Create material"))
		.HAlign(HAlign_Right)
		.OnClicked(FOnClicked::CreateUObject(DusterControl, &UDusterControl::Create2DMaterial))
		.ToolTipText(FText::FromString("Create a new material with the required parameters."))
	];
	
	IDetailPropertyRow& Density = ChildBuilder.AddProperty(PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FLocalDusterInfo2D, Density)).ToSharedRef());
	Density.GetPropertyHandle()->SetToolTipText(FText::FromString("The density of coverage."));
	Density.GetPropertyHandle()->SetOnPropertyValueChanged(FSimpleDelegate::CreateUObject(DusterControl, &UDusterControl::Update2D));

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
	ActorPointAt.GetPropertyHandle()->SetOnPropertyValueChanged(FSimpleDelegate::CreateUObject(DusterControl, &UDusterControl::Update2D));


	ChildBuilder.AddCustomRow(FText::FromString("Create actor"))
	.ValueContent()
	[
		SNew(SButton)
		.Text(FText::FromString("Create Actor"))
		.ToolTipText(FText::FromString("Create an editor only actor for use with the point to actor system."))
		.OnClicked(FOnClicked::CreateUObject(DusterControl, &UDusterControl::CreateActor))
	];
	
	if (bSided)
	{
		for (int i = 0; i < 6; i++)
		{
			IDetailGroup& SubGroup = ChildBuilder.AddGroup(*FString::Printf(TEXT("Side %d"), i), FText::FromString(FString::Printf(TEXT("Side %d"), i)));
			
			TSharedPtr<IPropertyHandle> ActorOverrideHandle = PropertyHandle->GetChildHandle("Sides")->AsArray()->GetElement(i)->GetChildHandle("ActorToPointAtOverride");
			ActorOverrideHandle->SetOnPropertyValueChanged(FSimpleDelegate::CreateUObject(DusterControl, &UDusterControl::Update2D));

			TSharedPtr<IPropertyHandle> OverrideActorHandle = PropertyHandle->GetChildHandle("Sides")->AsArray()->GetElement(i)->GetChildHandle("bOverrideActor");

			OverrideActorHandle->SetOnPropertyValueChanged(OnValueChanged);
			
			bool bOverrideActor;
			OverrideActorHandle->GetValue(bOverrideActor);
			
			SubGroup.AddWidgetRow()
			.NameContent()
			[
				SNew(SHorizontalBox)
				+SHorizontalBox::Slot()
				.AutoWidth()
				[
					SNew(SProperty, OverrideActorHandle)
					.ShouldDisplayName(false)
				]
				+SHorizontalBox::Slot()
				.AutoWidth()
				[
					SNew(STextBlock)
					.Text(FText::FromString(" Override Actor to Point At"))
				]
			]
			.ValueContent()
			[
				SNew(SProperty, ActorOverrideHandle)
				.ShouldDisplayName(false)
				.ToolTipText(FText::FromString("The actor That this face will point at."))
				.IsEnabled(bOverrideActor)
			];

			TSharedPtr<IPropertyHandle> DensityOverrideHandle = PropertyHandle->GetChildHandle("Sides")->AsArray()->GetElement(i)->GetChildHandle("DensityOverride");
			DensityOverrideHandle->SetOnPropertyValueChanged(FSimpleDelegate::CreateUObject(DusterControl, &UDusterControl::Update2D));

			TSharedPtr<IPropertyHandle> OverrideDensityHandle = PropertyHandle->GetChildHandle("Sides")->AsArray()->GetElement(i)->GetChildHandle("bOverrideDensity");

			OverrideDensityHandle->SetOnPropertyValueChanged(OnValueChanged);
			
			bool bOverrideDensity;
			OverrideDensityHandle->GetValue(bOverrideDensity);
			
			SubGroup.AddWidgetRow()
			.NameContent()
			[
				SNew(SHorizontalBox)
				+SHorizontalBox::Slot()
				.AutoWidth()
				[
					SNew(SProperty, OverrideDensityHandle)
					.ShouldDisplayName(false)
				]
				+SHorizontalBox::Slot()
				.AutoWidth()
				[
					SNew(STextBlock)
					.Text(FText::FromString(" Override Density"))
				]
			]
			.ValueContent()
			[
				SNew(SProperty, DensityOverrideHandle)
				.ShouldDisplayName(false)
				.ToolTipText(FText::FromString("The density for this face."))
				.IsEnabled(bOverrideDensity)
			];

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
					.OnClicked(FOnClicked::CreateUObject(DusterControl, &UDusterControl::Add2D, i))
					.ToolTipText(FText::FromString("Add a Decal to selected actors."))
					
				]
				+SHorizontalBox::Slot()
				.AutoWidth()
				[
					SNew(SButton)
					.Text(FText::FromString("Remove"))
					.HAlign(HAlign_Center)
					.OnClicked(FOnClicked::CreateUObject(DusterControl, &UDusterControl::Remove2D, i))
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
					.OnClicked(FOnClicked::CreateUObject(DusterControl, &UDusterControl::Add2D, -1))
					.ToolTipText(FText::FromString("Add a Decal to selected actors."))
					
				]
				+SHorizontalBox::Slot()
				.AutoWidth()
				[
					SNew(SButton)
					.Text(FText::FromString("Remove"))
					.HAlign(HAlign_Center)
					.OnClicked(FOnClicked::CreateUObject(DusterControl, &UDusterControl::Remove2D, -1))
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
