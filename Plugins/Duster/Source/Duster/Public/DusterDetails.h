#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DusterDetails.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCustomDetailsSaveSignature);

UCLASS(BlueprintType)
class DUSTER_API UDusterDetails : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	FName Name;
	
	static FReply Save();
};
