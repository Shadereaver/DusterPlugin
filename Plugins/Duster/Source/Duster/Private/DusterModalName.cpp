#include "DusterModalName.h"

#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SDusterModalName::Construct(const FArguments& InArgs)
{
	this->ChildSlot
	[
		SNew(SVerticalBox)
		+SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew(STextBlock)
			.Text(FText::FromString("Enter File Name"))
		]
		+SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew(SEditableTextBox)
			.HintText(FText::FromString("Name"))
			.OnTextChanged(this, &SDusterModalName::OnTextChanged)
		]
		+SVerticalBox::Slot()
		.FillHeight(1)
		+SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew(SHorizontalBox)
			+SHorizontalBox::Slot()
			.AutoWidth()
			[
				SNew(SButton)
				.Text(FText::FromString("Cancel"))
				.OnClicked(this, &SDusterModalName::OnCancelClicked)
			]
			+SHorizontalBox::Slot()
			.FillWidth(1)
			+SHorizontalBox::Slot()
			.AutoWidth()
			[
				SNew(SButton)
				.Text(FText::FromString("Ok"))
				.OnClicked(this, &SDusterModalName::OnOkClicked)
			]
		]
	];
}

void SDusterModalName::OnTextChanged(const FText& Text)
{
	Result = Text.ToString();
}

void SDusterModalName::SetWindow(TSharedPtr<SWindow> InWindow)
{
	Window = InWindow;
}

FReply SDusterModalName::OnOkClicked()
{
	ButtonClicked = Ok;
	Window->RequestDestroyWindow();
	return FReply::Handled();
}

FReply SDusterModalName::OnCancelClicked()
{
	ButtonClicked = Cancel;
	Window->RequestDestroyWindow();
	return FReply::Handled();
}

EButtonValue SDusterModalName::GetResult(FString& OutString)
{
	OutString = Result;
	return ButtonClicked;
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

