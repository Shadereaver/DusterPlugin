#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DusterInfo2D.generated.h"

struct FLocalDusterInfo2D;

UCLASS()
class DUSTER_API UDusterInfo2D : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "UDusterInfo2D")
	TObjectPtr<UTexture> Texture;

	UPROPERTY(EditAnywhere, Category = "UDusterInfo2D")
	TObjectPtr<UMaterial> Material;

	UPROPERTY(EditAnywhere, Category = "UDusterInfo2D")
	float Density;

	void SetData(const TObjectPtr<UDusterInfo2D>& Other);
	void SetData(const FLocalDusterInfo2D& Other);
};
