#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DusterInfo3D.generated.h"

UCLASS()
class DUSTER_API UDusterInfo3D : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UMaterial> Material;

	UPROPERTY(EditAnywhere)
	float Height;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UCurveFloat> Falloff;

	UPROPERTY(EditAnywhere)
	float FalloffMultiplier;

	UPROPERTY(EditAnywhere)
	int Resolution;
};
