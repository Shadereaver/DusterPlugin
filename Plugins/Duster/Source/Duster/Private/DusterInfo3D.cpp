#include "DusterInfo3D.h"

#include "DusterControl.h"

void UDusterInfo3D::SetData(const TObjectPtr<UDusterInfo3D>& Other)
{
	Falloff = Other->Falloff;
	Height = Other->Height;
	Material = Other->Material;
	Resolution = Other->Resolution;
	FalloffMultiplier = Other->FalloffMultiplier;
}

void UDusterInfo3D::SetData(const FLocalDusterInfo3D& Other)
{
	Falloff = Other.Falloff;
	Height = Other.Height;
	Material = Other.Material;
	Resolution = Other.Resolution;
	FalloffMultiplier = Other.FalloffMultiplier;
}
