#pragma once

#include "CoreMinimal.h"
#include "DusterControl.h"
#include "EditorUtilityActorComponent.h"
#include "Duster3DComponent.generated.h"

UCLASS(ClassGroup=(Duster), meta=(BlueprintSpawnableComponent))
class DUSTER_API UDuster3DComponent : public UEditorUtilityActorComponent
{
	GENERATED_BODY()

public:
	UDuster3DComponent();
	
	void Delete() const;
	
	void CreateMesh();
	
	FLocalDusterInfo3D Settings;

	TObjectPtr<UDusterInfo3D> Profile;
	
private:
	UPROPERTY()
	TObjectPtr<UStaticMeshComponent> OriginalMeshComponent;
	
	UPROPERTY()
	TObjectPtr<UStaticMeshComponent> GeneratedMeshComponent;
	
	UPROPERTY()
	TObjectPtr<UStaticMesh> GeneratedMesh;
	
	FString GeneratedMeshName;
};
