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

	UPROPERTY(EditAnywhere)
	bool bSided;
};

UCLASS(Abstract)
class DUSTER_API UDusterControl : public UEditorUtilityObject
{
	GENERATED_BODY()

public:
	FReply Add3D();
	FReply Remove3D();
	FReply Create3D();
	FReply Delete3D();
	FReply Copy3D();
	FReply Save3D();
	
	FReply Create2D();
	FReply Create2DMaterial();
	FReply Delete2D();
	FReply Copy2D();
	FReply Save2D();

	void Profile3DChanged();
	void Profile2DChanged();
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UDusterInfo3D> Current3DProfile;

	UPROPERTY(EditAnywhere, Category = "3D|Settings")
	FLocalDusterInfo3D LocalCurrent3DProfile;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UDusterInfo2D> Current2DProfile;
	
	UPROPERTY(EditAnywhere, Category = "2D|Settings")
	FLocalDusterInfo2D LocalCurrent2DProfile;
};
