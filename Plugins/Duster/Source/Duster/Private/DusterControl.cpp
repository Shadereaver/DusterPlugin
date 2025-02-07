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

FReply UDusterControl::Create3D()
{
	UE_LOG(LogTemp, Display, TEXT("Create3D"));
	return	FReply::Handled();
}

FReply UDusterControl::Delete3D()
{
	UE_LOG(LogTemp, Display, TEXT("Delete3D"));
	return	FReply::Handled();
}

FReply UDusterControl::Copy3D()
{
	UE_LOG(LogTemp, Display, TEXT("Copy3D"));
	return	FReply::Handled();
}

FReply UDusterControl::Save3D()
{
	UE_LOG(LogTemp, Display, TEXT("Save3D"));
	return	FReply::Handled();
}

FReply UDusterControl::Create2D()
{
	UE_LOG(LogTemp, Display, TEXT("Create2D"));
	return	FReply::Handled();
}

FReply UDusterControl::Create2DMaterial()
{
	UE_LOG(LogTemp, Display, TEXT("Create2DMaterial"));
	return	FReply::Handled();
}

FReply UDusterControl::Delete2D()
{
	UE_LOG(LogTemp, Display, TEXT("Delete2D"));
	return	FReply::Handled();
}

FReply UDusterControl::Copy2D()
{
	UE_LOG(LogTemp, Display, TEXT("Copy2D"));
	return	FReply::Handled();
}

FReply UDusterControl::Save2D()
{
	UE_LOG(LogTemp, Display, TEXT("Save2D"));
	return	FReply::Handled();
}

void UDusterControl::Profile3DChanged()
{
	LocalCurrent3DProfile.Material = Current3DProfile->Material;
	LocalCurrent3DProfile.Height = Current3DProfile->Height;
	LocalCurrent3DProfile.Falloff = Current3DProfile->Falloff;
}

void UDusterControl::Profile2DChanged()
{
	LocalCurrent2DProfile.Texture = Current2DProfile->Texture;
	LocalCurrent2DProfile.Material = Current2DProfile->Material;
	LocalCurrent2DProfile.Density = Current2DProfile->Density;
	LocalCurrent2DProfile.bSided = Current2DProfile->bSided;
	LocalCurrent2DProfile.Sides = Current2DProfile->Sides;
	LocalCurrent2DProfile.ActorToPointAt = Current2DProfile->ActorToPointAt;
}

