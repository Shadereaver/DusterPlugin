#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DusterInfo2D.generated.h"

UCLASS()
class DUSTER_API UDusterInfo2D : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UTexture> Texture;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UMaterial> Material;

	UPROPERTY(EditAnywhere)
	float Density;
};
