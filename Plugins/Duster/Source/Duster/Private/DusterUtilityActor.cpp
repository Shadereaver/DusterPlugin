#include "DusterUtilityActor.h"

ADusterUtilityActor::ADusterUtilityActor()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	
	bIsEditorOnlyActor = true;
}
