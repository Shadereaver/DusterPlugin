#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

class UDusterControl;

class DUSTER_API SDusterWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SDusterWidget)
	{}
	SLATE_END_ARGS()

	SDusterWidget() : CommandList(new FUICommandList){}

	void Construct(const FArguments& InArgs);
	
	TSharedPtr<class IDetailsView> PropertyWidget;
protected:
	TSharedRef<FUICommandList> CommandList;
};
