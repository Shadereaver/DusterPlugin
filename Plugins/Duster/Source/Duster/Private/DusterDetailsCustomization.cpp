#include "DusterDetailsCustomization.h"

#include "DetailLayoutBuilder.h"
#include "DetailWidgetRow.h"
#include "DusterSubsystem.h"
#include "IDetailGroup.h"

void FDusterDetailsCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	TObjectPtr<UDusterControl> DusterControl = GEditor->GetEditorSubsystem<UDusterSubsystem>()->GetDusterControl();

	FSimpleDelegate OnValueChanged = FSimpleDelegate::CreateLambda([&DetailBuilder]()
	{
		DetailBuilder.ForceRefreshDetails();
	});
	
	IDetailCategoryBuilder& Category3D = DetailBuilder.EditCategory("3D");
	IDetailGroup& ProfileGroup3D = Category3D.AddGroup(TEXT("ProfileGroup"), FText::FromString("Profile"));

	IDetailPropertyRow& Profile3D = ProfileGroup3D.AddPropertyRow(DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(UDusterControl, Current3DProfile)));
	Profile3D.GetPropertyHandle()->SetOnPropertyValueChanged(FSimpleDelegate::CreateUObject(DusterControl, &UDusterControl::Profile3DChanged));
	Profile3D.GetPropertyHandle()->SetOnChildPropertyValueChanged(OnValueChanged);
	Profile3D.DisplayName(FText::FromString("Profile"));

	ProfileGroup3D.AddWidgetRow()
	.ValueContent()
	[
		SNew(SHorizontalBox)
		+SHorizontalBox::Slot()
		.AutoWidth()
		[
			SNew(SVerticalBox)
			+SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew(SButton)
				.Text(FText::FromString("Create new"))
				.HAlign(HAlign_Center)
				.OnClicked(FOnClicked::CreateUObject(DusterControl, &UDusterControl::Create3D))
				.ToolTipText(FText::FromString("Create new profile"))
			]
			+SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew(SButton)
				.Text(FText::FromString("Save"))
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Center)
				.OnClicked(FOnClicked::CreateUObject(DusterControl, &UDusterControl::Save3D))
				.ToolTipText(FText::FromString("Save to current profile"))
			]
		]
		+SHorizontalBox::Slot()
		.AutoWidth()
		[
			SNew(SVerticalBox)
			+SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew(SButton)
				.Text(FText::FromString("Delete"))
				.HAlign(HAlign_Center)
				.OnClicked(FOnClicked::CreateUObject(DusterControl, &UDusterControl::Delete3D))
				.ButtonColorAndOpacity(FSlateColor(FLinearColor(255, 0, 0)))
				.ToolTipText(FText::FromString("Delete current profile"))
			]
			+SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew(SButton)
				.Text(FText::FromString("Copy"))
				.HAlign(HAlign_Center)
				.OnClicked(FOnClicked::CreateUObject(DusterControl, &UDusterControl::Copy3D))
				.ToolTipText(FText::FromString("Copy current profile"))
			]
		]
	];
	
	IDetailCategoryBuilder& Category2D = DetailBuilder.EditCategory("2D");
	IDetailGroup& ProfileGroup2D = Category2D.AddGroup(TEXT("ProfileGroup"), FText::FromString("Profile"));
	
	IDetailPropertyRow& Profile2D = ProfileGroup2D.AddPropertyRow(DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(UDusterControl, Current2DProfile)));
	Profile2D.GetPropertyHandle()->SetOnPropertyValueChanged(FSimpleDelegate::CreateUObject(DusterControl, &UDusterControl::Profile2DChanged));
	Profile2D.GetPropertyHandle()->SetOnChildPropertyValueChanged(OnValueChanged);
	Profile2D.DisplayName(FText::FromString("Profile"));

	ProfileGroup2D.AddWidgetRow()
	.ValueContent()
	[
		SNew(SHorizontalBox)
		+SHorizontalBox::Slot()
		.AutoWidth()
		[
			SNew(SVerticalBox)
			+SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew(SButton)
				.Text(FText::FromString("Create new"))
				.HAlign(HAlign_Center)
				.OnClicked(FOnClicked::CreateUObject(DusterControl, &UDusterControl::Create2D))
				.ToolTipText(FText::FromString("Create new profile"))
			]
			+SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew(SButton)
				.Text(FText::FromString("Save"))
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Center)
				.OnClicked(FOnClicked::CreateUObject(DusterControl, &UDusterControl::Save2D))
				.ToolTipText(FText::FromString("Save to current profile"))
			]
		]
		+SHorizontalBox::Slot()
		.AutoWidth()
		[
			SNew(SVerticalBox)
			+SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew(SButton)
				.Text(FText::FromString("Delete"))
				.HAlign(HAlign_Center)
				.OnClicked(FOnClicked::CreateUObject(DusterControl, &UDusterControl::Delete2D))
				.ButtonColorAndOpacity(FSlateColor(FLinearColor(255, 0, 0)))
				.ToolTipText(FText::FromString("Delete current profile"))
			]
			+SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew(SButton)
				.Text(FText::FromString("Copy"))
				.HAlign(HAlign_Center)
				.OnClicked(FOnClicked::CreateUObject(DusterControl, &UDusterControl::Copy2D))
				.ToolTipText(FText::FromString("Copy current profile"))
			]
		]
	];
}

TSharedRef<IDetailCustomization> FDusterDetailsCustomization::MakeInstance()
{
	return MakeShareable(new FDusterDetailsCustomization);
}
