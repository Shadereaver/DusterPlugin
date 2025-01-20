// Fill out your copyright notice in the Description page of Project Settings.


#include "SMainWidget.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SMainWidget::Construct(const FArguments& InArgs)
{
	SNew(SVerticalBox)
	+SVerticalBox::Slot()
	.AutoHeight()
	[
		SNew(SVerticalBox)
		+SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew(STextBlock)
			.Text(FText::FromString("3D"))
		]
		+SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew(STextBlock)
			.Text(FText::FromString("Preset"))
		]
	];
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
