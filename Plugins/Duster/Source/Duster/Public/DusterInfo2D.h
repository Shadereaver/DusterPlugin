#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DusterInfo2D.generated.h"

USTRUCT()
struct F2DSides
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<AActor> ActorToPointAt;

	UPROPERTY(EditAnywhere)
	float DensityOverride;
};

UCLASS()
class DUSTER_API UDusterInfo2D : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FName Name;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UTexture> Texture;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UMaterial> Material;

	UPROPERTY(EditAnywhere)
	float Density;

	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<AActor> ActorToPointAt;

	UPROPERTY(EditAnywhere)
	TArray<F2DSides> Sides;
};
