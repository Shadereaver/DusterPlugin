#pragma once

#include "CoreMinimal.h"
#include "DusterInfo2D.h"
#include "EditorUtilityObject.h"
#include "DusterControl.generated.h"

enum EButtonValue : int;
class SDusterWidget;
class UDuster3DComponent;
class UDusterInfo2D;
class UDusterInfo3D;

USTRUCT(BlueprintType)
struct FLocalDusterInfo3D
{
	GENERATED_BODY()

	TWeakObjectPtr<UDusterInfo3D> Profile;

	UPROPERTY(EditAnywhere, Category = "LocalDusterInfo3D")
	TObjectPtr<UMaterial> Material;

	UPROPERTY(EditAnywhere, Category = "LocalDusterInfo3D")
	float Height = 1;

	UPROPERTY(EditAnywhere, Category = "LocalDusterInfo3D")
	TObjectPtr<UCurveFloat> Falloff;

	UPROPERTY(EditAnywhere, Category = "LocalDusterInfo3D")
	int Resolution = 3;

	UPROPERTY(EditAnywhere, Category = "LocalDusterInfo3D")
	float FalloffMultiplier = 1;
};

USTRUCT(BlueprintType)
struct F2DSides
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "F2DSides")
	bool bOverrideActor = false;
	
	UPROPERTY(EditAnywhere, Category = "F2DSides")
	TSoftObjectPtr<AActor> ActorToPointAtOverride;

	UPROPERTY(EditAnywhere, Category = "F2DSides")
	bool bOverrideDensity = false;
	
	UPROPERTY(EditAnywhere, Category = "F2DSides")
	float DensityOverride = 1;
};

USTRUCT(BlueprintType)
struct FLocalDusterInfo2D
{
	GENERATED_BODY()

	TWeakObjectPtr<UDusterInfo2D> Profile;
	
	UPROPERTY(EditAnywhere, Category = "LocalDusterInfo2D")
	TObjectPtr<UTexture> Texture;

	UPROPERTY(EditAnywhere, Category = "LocalDusterInfo2D")
	TObjectPtr<UMaterial> Material;

	UPROPERTY(EditAnywhere, Category = "LocalDusterInfo2D")
	float Density = 1;

	UPROPERTY(EditAnywhere, Category = "LocalDusterInfo2D")
	TSoftObjectPtr<AActor> ActorToPointAt;

	UPROPERTY(EditAnywhere, Category = "LocalDusterInfo2D")
	F2DSides Sides[6];

	UPROPERTY(EditAnywhere, Category = "LocalDusterInfo2D")
	bool bSided = false;
};

UCLASS(Abstract)
class DUSTER_API UDusterControl : public UEditorUtilityObject
{
	GENERATED_BODY()

public:
	FReply Add3D();
	FReply Remove3D();
	FReply Create3D();
	FReply Delete3D() const;
	FReply Copy3D();
	FReply Save3D() const;
	void UpdateMesh(const FPropertyChangedEvent&);
	
	FReply Create2D();
	FReply Create2DMaterial();
	FReply Delete2D() const;
	FReply Copy2D();
	FReply Save2D() const;
	FReply Add2D(int Side);
	FReply Remove2D(int Side);
	FReply CreateActor();
	void Update2D();

	void Profile3DChanged();
	void Profile2DChanged();

	void UpdateLocal3D(const FLocalDusterInfo3D& Local);
	void UpdateLocal2D(const FLocalDusterInfo2D& Local);

	UFUNCTION()
	void OnSelectionChanged(const UTypedElementSelectionSet* SelectionSet);
	
	TArray<TObjectPtr<AActor>> SelectedActors;
	
	UPROPERTY(EditAnywhere, Category = "3D|Profile")
	TObjectPtr<UDusterInfo3D> Current3DProfile;

	UPROPERTY(EditAnywhere, Category = "3D|Settings")
	FLocalDusterInfo3D LocalCurrent3DProfile;
	
	UPROPERTY(EditAnywhere, Category = "2D|Profile")
	TObjectPtr<UDusterInfo2D> Current2DProfile;
	
	UPROPERTY(EditAnywhere, Category = "2D|Settings")
	FLocalDusterInfo2D LocalCurrent2DProfile;
	
private:
	static EButtonValue GetName(FString& Name);
	
	static void Validate3DName(FString& InName);
	static UDusterInfo3D* Create3DAsset(FString& OutPackageName, const FString& Name);
	
	static void Validate2DName(FString& InName);
	static UDusterInfo2D* Create2DAsset(FString& OutPackageName, const FString& Name);
};
