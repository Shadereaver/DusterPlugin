#include "DusterInfo3DCustomisation.h"

#include "DetailWidgetRow.h"
#include "DusterControl.h"
#include "DusterSubsystem.h"
#include "IDetailChildrenBuilder.h"

void FDusterInfo3DCustomisation::CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle,
	FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils)
{
}

void FDusterInfo3DCustomisation::CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle,
	IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils)
{
	if (!PropertyHandle->IsValidHandle())
		return;

	TObjectPtr<UDusterControl> DusterControl = GEditor->GetEditorSubsystem<UDusterSubsystem>()->GetDusterControl();
	
	ChildBuilder.AddProperty(PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FLocalDusterInfo3D, Material)).ToSharedRef())
	.GetPropertyHandle()->SetToolTipText(FText::FromString("The material applied to the generated mesh."));
	ChildBuilder.AddProperty(PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FLocalDusterInfo3D, Height)).ToSharedRef())
	.GetPropertyHandle()->SetToolTipText(FText::FromString("The distance from the base mesh surface to the top of the generated mesh."));
	ChildBuilder.AddProperty(PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FLocalDusterInfo3D, Falloff)).ToSharedRef())
	.GetPropertyHandle()->SetToolTipText(FText::FromString("The slope from the bottom to the top of the generated mesh."));

	ChildBuilder.AddCustomRow(FText::FromString("3D Controls"))
	.ValueContent()
	[
		SNew(SHorizontalBox)
		+SHorizontalBox::Slot()
		.AutoWidth()
		[
			SNew(SButton)
			.Text(FText::FromString(TEXT("Add")))
			.HAlign(HAlign_Center)
			.OnClicked(FOnClicked::CreateUObject(DusterControl, &UDusterControl::Add3D))
			.ToolTipText(FText::FromString("Add a mesh to selected actors."))
			
		]
		+SHorizontalBox::Slot()
		.AutoWidth()
		[
			SNew(SButton)
			.Text(FText::FromString("Remove"))
			.HAlign(HAlign_Center)
			.OnClicked(FOnClicked::CreateUObject(DusterControl, &UDusterControl::Remove3D))
			.ToolTipText(FText::FromString("Remove generated mesh from selected actors."))
			.ButtonColorAndOpacity(FSlateColor(FLinearColor(255, 0 , 0)))
		]
	];
}

TSharedRef<IPropertyTypeCustomization> FDusterInfo3DCustomisation::MakeInstance()
{
	return MakeShareable(new FDusterInfo3DCustomisation);
}
