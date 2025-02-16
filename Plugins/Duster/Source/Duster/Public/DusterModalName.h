#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

enum EButtonValue
{
	Ok,
	Cancel
};

class DUSTER_API SDusterModalName : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SDusterModalName)
		{
		}

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs) ;

	void SetWindow(TSharedPtr<SWindow> InWindow);

	FReply OnOkClicked();

	FReply OnCancelClicked();
	
	EButtonValue GetResult(FString& OutString);
	
private:
	TSharedPtr<SWindow> Window;

	FString Result;
	
	EButtonValue ButtonClicked = Cancel;
	
	void OnTextChanged(const FText& Text);
};
