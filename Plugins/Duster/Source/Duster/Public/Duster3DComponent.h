#pragma once

#include "CoreMinimal.h"
#include "EditorUtilityActorComponent.h"
#include "Duster3DComponent.generated.h"


UCLASS(ClassGroup=(Duster), meta=(BlueprintSpawnableComponent))
class DUSTER_API UDuster3DComponent : public UEditorUtilityActorComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent, CallInEditor)
	void CreateMesh();
	
	UFUNCTION(BlueprintCallable)
	FString CreateName(FString InName);

	UFUNCTION(BlueprintCallable)
	void SaveAsset(FString PackageName, UObject* Object);
};
