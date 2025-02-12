#pragma once

#include "CoreMinimal.h"
#include "DusterInfo2D.h"
#include "EditorUtilityObject.h"
#include "DusterControl.generated.h"

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
struct F2DSides
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	bool bOverrideActor;
	
	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<AActor> ActorToPointAt;

	UPROPERTY(EditAnywhere)
	bool bOverrideDensity;
	
	UPROPERTY(EditAnywhere)
	float DensityOverride;
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
	F2DSides Sides[6];

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
	FReply Add2D(int Side);
	FReply Remove2D(int Side);
	FReply CreateActor();

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
