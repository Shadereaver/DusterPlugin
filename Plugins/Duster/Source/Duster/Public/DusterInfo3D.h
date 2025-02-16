#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DusterInfo3D.generated.h"

struct FLocalDusterInfo3D;

UCLASS()
class DUSTER_API UDusterInfo3D : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category = "UDusterInfo3D")
	TObjectPtr<UMaterial> Material;

	UPROPERTY(EditAnywhere, Category = "UDusterInfo3D")
	float Height;

	UPROPERTY(EditAnywhere, Category = "UDusterInfo3D")
	TObjectPtr<UCurveFloat> Falloff;

	UPROPERTY(EditAnywhere, Category = "UDusterInfo3D")
	float FalloffMultiplier;

	UPROPERTY(EditAnywhere, Category = "UDusterInfo3D")
	int Resolution;

	void SetData(const TObjectPtr<UDusterInfo3D>& Other);
	void SetData(const FLocalDusterInfo3D& Other);
};
