#pragma once

#include "CoreMinimal.h"
#include "DusterControl.h"
#include "EditorUtilityActorComponent.h"
#include "Duster2DComponent.generated.h"

UCLASS(ClassGroup=(Duster), meta=(BlueprintSpawnableComponent))
class DUSTER_API UDuster2DComponent : public UEditorUtilityActorComponent
{
	GENERATED_BODY()

public:
	UDuster2DComponent();

	void Init();
	
	void AddToSide(const int Side);

	bool Delete(const int Side);

	void Update();

	void UpdateActor(AActor* Actor);
	
	FLocalDusterInfo2D Settings;
	
	TObjectPtr<UDusterInfo2D> Profile;

private:
	TObjectPtr<UDecalComponent> Decals[6];

	TObjectPtr<USceneComponent> ParentComponent;
};
