#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DusterDetails.generated.h"

UCLASS(BlueprintType)
class DUSTER_API UDusterDetails : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	FName Name;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UMaterial> Material;

	UPROPERTY(EditAnywhere)
	float Height;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UCurveFloat> Falloff;


	UPROPERTY(EditAnywhere)
	TObjectPtr<UTexture> Texture;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UMaterial> Material2;

	UPROPERTY(EditAnywhere)
	float Density;

	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<AActor> Actor;

	UPROPERTY(EditAnywhere)
	bool bPointAt = false;

	UPROPERTY(EditAnywhere)
	float OverrideDensity;
	
	static TArray<bool> Sides;
	
	
	static FReply Save();
	
	static FReply Remove();
	
	static FReply Add();
	
	static FReply Mat();

	static void Checkbox(ECheckBoxState State, int side);
};
