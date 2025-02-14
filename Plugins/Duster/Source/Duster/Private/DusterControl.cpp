#include "DusterControl.h"

#include "AssetSelection.h"
#include "Duster3DComponent.h"
#include "DusterInfo2D.h"
#include "DusterInfo3D.h"
#include "Selection.h"

FReply UDusterControl::Add3D()
{
	for (TObjectPtr<AActor> Actor : SelectedActors)
	{
		if (!Actor->FindComponentByClass<UDuster3DComponent>())
		{
			UDuster3DComponent* Component3D = NewObject<UDuster3DComponent>(Actor);
			Actor->AddInstanceComponent(Component3D);
			GEditor->NoteSelectionChange();
			Component3D->LocalDusterInfo3D = LocalCurrent3DProfile;
			Component3D->CreateMesh_Implementation();
		}
	}
	return	FReply::Handled();
}

FReply UDusterControl::Remove3D()
{
	for (TObjectPtr<AActor> Actor : SelectedActors)
	{
		if (UDuster3DComponent* Component3D = Actor->FindComponentByClass<UDuster3DComponent>())
		{
			Component3D->Delete();
			Actor->RemoveInstanceComponent(Component3D);
			GEditor->NoteSelectionChange();
		}
	}
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

FReply UDusterControl::Add2D(int Side)
{
	UE_LOG(LogTemp, Display, TEXT("Add2D, %d"), Side);
	return	FReply::Handled();
}

FReply UDusterControl::Remove2D(int Side)
{
	UE_LOG(LogTemp, Display, TEXT("Remove2D, %d"), Side);
	return	FReply::Handled();
}

FReply UDusterControl::CreateActor()
{
	UE_LOG(LogTemp, Display, TEXT("CreateActor"));
	return	FReply::Handled();
}

void UDusterControl::Profile3DChanged()
{
	LocalCurrent3DProfile.Material = Current3DProfile->Material;
	LocalCurrent3DProfile.Height = Current3DProfile->Height;
	LocalCurrent3DProfile.Falloff = Current3DProfile->Falloff;
	LocalCurrent3DProfile.Resolution = Current3DProfile->Resolution;
	LocalCurrent3DProfile.FalloffMultiplier = Current3DProfile->FalloffMultiplier;
	LocalCurrent3DProfile.Profile = Current3DProfile;
}

void UDusterControl::Profile2DChanged()
{
	LocalCurrent2DProfile.Texture = Current2DProfile->Texture;
	LocalCurrent2DProfile.Material = Current2DProfile->Material;
	LocalCurrent2DProfile.Density = Current2DProfile->Density;
}

void UDusterControl::UpdateLocal3D(const FLocalDusterInfo3D& Local)
{
	LocalCurrent3DProfile.Material = Local.Material;
	LocalCurrent3DProfile.Height = Local.Height;
	LocalCurrent3DProfile.Falloff = Local.Falloff;
	LocalCurrent3DProfile.Resolution = Local.Resolution;
	LocalCurrent3DProfile.FalloffMultiplier = Local.FalloffMultiplier;
	LocalCurrent3DProfile.Profile = Local.Profile;
}

void UDusterControl::OnSelectionChanged(const UTypedElementSelectionSet* SelectionSet)
{
	SelectedActors = SelectionSet->GetSelectedObjects<AActor>();

	for (TObjectPtr<AActor> Actor : SelectedActors)
	{
		if (TObjectPtr<UDuster3DComponent> Component3D = Actor->FindComponentByClass<UDuster3DComponent>())
		{
			UpdateLocal3D(Component3D->LocalDusterInfo3D);
			break;
		}
	}
}

