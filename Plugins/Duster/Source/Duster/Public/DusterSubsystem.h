#pragma once

#include "CoreMinimal.h"
#include "DusterControl.h"
#include "EditorSubsystem.h"
#include "DusterSubsystem.generated.h"

UCLASS()
class DUSTER_API UDusterSubsystem : public UEditorSubsystem
{
	GENERATED_BODY()
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	TSharedPtr<UDusterControl>& GetDusterControl();

private:
	TSharedPtr<UDusterControl> DusterControl;
};
