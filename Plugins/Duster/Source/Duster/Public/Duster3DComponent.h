#pragma once

#include "CoreMinimal.h"
#include "DusterControl.h"
#include "EditorUtilityActorComponent.h"
#include "Duster3DComponent.generated.h"

UCLASS(ClassGroup=(Duster), meta=(BlueprintSpawnableComponent))
class DUSTER_API UDuster3DComponent : public UEditorUtilityActorComponent
{
	GENERATED_BODY()

	virtual bool IsEditorOnly() const override;
	
public:
	UFUNCTION(BlueprintNativeEvent, CallInEditor)
	void CreateMesh();
	
	UFUNCTION(BlueprintCallable)
	FString CreateName(FString InName);

	UFUNCTION(BlueprintCallable)
	void SaveAsset(FString PackageName, UObject* Object);

	UFUNCTION(BlueprintCallable)
	UStaticMeshComponent* CreateMeshComponent(AActor* Actor, UStaticMeshComponent* OriginalMeshComponent);

	UPROPERTY(BlueprintReadOnly)
	FLocalDusterInfo3D LocalDusterInfo3D;

	FLocalDusterInfo3D Settings;
	
private:
	TObjectPtr<UStaticMeshComponent> OriginalMesh;

};
