#pragma once
#include "CoreMinimal.h"
#include "IDetailCustomization.h"

class UDusterControl;

class FDusterDetailsCustomization : public IDetailCustomization
{
public:
	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;

	static TSharedRef<IDetailCustomization> MakeInstance();
};
