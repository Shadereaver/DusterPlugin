#include "DusterInfo2D.h"

#include "DusterControl.h"

void UDusterInfo2D::SetData(const TObjectPtr<UDusterInfo2D>& Other)
{
	Texture = Other->Texture;
	Material = Other->Material;
	Density = Other->Density;
}

void UDusterInfo2D::SetData(const FLocalDusterInfo2D& Other)
{
	Texture = Other.Texture;
	Material = Other.Material;
	Density = Other.Density;
}
