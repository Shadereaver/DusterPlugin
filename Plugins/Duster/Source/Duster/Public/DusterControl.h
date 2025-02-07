#pragma once

#include "CoreMinimal.h"
#include "EditorUtilityObject.h"
#include "DusterControl.generated.h"

struct F2DSides;
class UDusterInfo2D;
class UDusterInfo3D;

USTRUCT(BlueprintType)
struct FLocalDusterInfo3D
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TObjectPtr<UMaterial> Material;

	UPROPERTY(EditAnywhere)
	float Height;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UCurveFloat> Falloff;
};

USTRUCT(BlueprintType)
struct FLocalDusterInfo2D
{
	GENERATED_BODY()
	
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

UCLASS(Abstract)
class DUSTER_API UDusterControl : public UEditorUtilityObject
{
	GENERATED_BODY()

public:
	FReply Add3D();
	FReply Remove3D();

	void Preset3DChanged();
	void Preset2DChanged();
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UDusterInfo3D> Current3DPreset;

	UPROPERTY(EditAnywhere, Category = "3D|Settings")
	FLocalDusterInfo3D LocalCurrent3DPreset;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UDusterInfo2D> Current2DPreset;
	
	UPROPERTY(EditAnywhere, Category = "2D|Settings")
	FLocalDusterInfo2D LocalCurrent2DPreset;
};
