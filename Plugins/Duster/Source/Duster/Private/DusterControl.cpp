#include "DusterControl.h"

#include "DusterInfo2D.h"
#include "DusterInfo3D.h"

FReply UDusterControl::Add3D()
{
	UE_LOG(LogTemp, Display, TEXT("Add3D"));
	return	FReply::Handled();
}

FReply UDusterControl::Remove3D()
{
	UE_LOG(LogTemp, Display, TEXT("Remove3D"));
	return	FReply::Handled();
}

void UDusterControl::Preset3DChanged()
{
	LocalCurrent3DPreset.Material = Current3DPreset->Material;
	LocalCurrent3DPreset.Height = Current3DPreset->Height;
	LocalCurrent3DPreset.Falloff = Current3DPreset->Falloff;
}

void UDusterControl::Preset2DChanged()
{
	LocalCurrent2DPreset.Texture = Current2DPreset->Texture;
	LocalCurrent2DPreset.Material = Current2DPreset->Material;
	LocalCurrent2DPreset.Density = Current2DPreset->Density;
	LocalCurrent2DPreset.ActorToPointAt = Current2DPreset->ActorToPointAt;
	LocalCurrent2DPreset.Sides = Current2DPreset->Sides;
}

