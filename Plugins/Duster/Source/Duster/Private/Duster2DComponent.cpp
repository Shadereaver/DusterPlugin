#include "Duster2DComponent.h"

#include "Components/DecalComponent.h"
#include "Kismet/KismetMathLibrary.h"

UDuster2DComponent::UDuster2DComponent()
{
	bIsEditorOnly = true;
}

void UDuster2DComponent::Init()
{
	GEngine->OnActorMoving().AddUObject(this, &UDuster2DComponent::UpdateActor);
}

void UDuster2DComponent::AddToSide(const int Side)
{
	if (!ParentComponent)
	{
		ParentComponent = NewObject<USceneComponent>(GetOwner());
		GetOwner()->AddInstanceComponent(ParentComponent);
		ParentComponent->RegisterComponent();
		ParentComponent->AttachToComponent(GetOwner()->GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
	}
	
	if (!Settings.Material)
		return;

	if (!Decals[Side == -1 ? 0 : Side])
	{
		Decals[Side == -1 ? 0 : Side] = NewObject<UDecalComponent>(GetOwner());
		GetOwner()->AddInstanceComponent(Decals[Side == -1 ? 0 : Side]);
		Decals[Side == -1 ? 0 : Side]->RegisterComponent();
		Decals[Side == -1 ? 0 : Side]->AttachToComponent(ParentComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);
		GEditor->NoteSelectionChange();
	}
	
	Decals[Side == -1 ? 0 : Side == -1 ? 0 : Side]->SetDecalMaterial(Settings.Material);
	
	if (Settings.Texture)
		Decals[Side == -1 ? 0 : Side == -1 ? 0 : Side]->GetDecalMaterial()->GetMaterial()->SetTextureParameterValueEditorOnly("Texture", Settings.Texture);
	
	if (Side == -1)
	{
		Decals[0]->GetDecalMaterial()->GetMaterial()->SetScalarParameterValueEditorOnly("Density", Settings.Density);
		FVector Origin, Extent;
		GetOwner()->GetActorBounds(false, Origin, Extent);
		const float ActorRadius = (Extent.X + Extent.Y) / 2;
		Decals[0]->SetRelativeLocation(GetOwner()->GetActorForwardVector() * ActorRadius);
		
		if (!Settings.ActorToPointAt)
		{
			Decals[0]->SetWorldRotation(GetOwner()->GetActorForwardVector().Rotation());
			return;
		};
		const FRotator Rotate = UKismetMathLibrary::FindLookAtRotation(Decals[0]->GetComponentLocation(), Settings.ActorToPointAt->GetActorLocation());
		Decals[0]->SetWorldRotation(Rotate);
		return;
	}

	if (Settings.Sides[Side].bOverrideDensity)
		Decals[Side]->GetDecalMaterial()->GetMaterial()->SetScalarParameterValueEditorOnly("Density", Settings.Sides[Side].DensityOverride);
	else
		Decals[Side]->GetDecalMaterial()->GetMaterial()->SetScalarParameterValueEditorOnly("Density", Settings.Density);

	if (Settings.Sides[Side].bOverrideActor && Settings.Sides[Side].ActorToPointAtOverride)
	{
		const FRotator Rotate = UKismetMathLibrary::FindLookAtRotation(Decals[0]->GetComponentLocation(), Settings.Sides[Side].ActorToPointAtOverride->GetActorLocation());
		Decals[Side]->SetWorldRotation(Rotate);
	}
	else
	{
		FVector Origin, Extent;
		GetOwner()->GetActorBounds(false, Origin, Extent);
		
		switch (Side)
		{
		case 0:
			Decals[0]->SetRelativeLocation(GetOwner()->GetActorUpVector() * Extent.Z);
			Decals[0]->SetRelativeRotation(GetOwner()->GetActorUpVector().Rotation());
			break;
			
		case 1:
			Decals[1]->SetRelativeLocation(-GetOwner()->GetActorUpVector() * Extent.Z);
			Decals[1]->SetRelativeRotation((-GetOwner()->GetActorUpVector()).Rotation());
			break;
		
		case 2:
			Decals[2]->SetRelativeLocation(GetOwner()->GetActorRightVector() * Extent.Y);
			Decals[2]->SetRelativeRotation(GetOwner()->GetActorRightVector().Rotation());
			break;
		
		case 3:
			Decals[3]->SetRelativeLocation(-GetOwner()->GetActorRightVector() * Extent.Y);
			Decals[3]->SetRelativeRotation((-GetOwner()->GetActorRightVector()).Rotation());
			break;
		
		case 4:
			Decals[4]->SetRelativeLocation(GetOwner()->GetActorForwardVector() * Extent.X);
			Decals[4]->SetRelativeRotation(GetOwner()->GetActorForwardVector().Rotation());
			break;
		
		case 5:
			Decals[5]->SetRelativeLocation(-GetOwner()->GetActorForwardVector() * Extent.X);
			Decals[5]->SetRelativeRotation((-GetOwner()->GetActorForwardVector()).Rotation());
			break;

		default:
			Decals[Side]->SetRelativeLocation(GetOwner()->GetActorForwardVector() * Extent.X);
			Decals[Side]->SetRelativeRotation(GetOwner()->GetActorForwardVector().Rotation());
			break;
		}
	}
}

bool UDuster2DComponent::Delete(const int Side)
{
	if (Side == -1)
	{
		for (TObjectPtr<UDecalComponent>& DecalComponent : Decals)
		{
			if (DecalComponent)
			{
				DecalComponent->DestroyComponent();
				DecalComponent = nullptr;
			}
		}
		ParentComponent->DestroyComponent();
		return true;
	}
	
	if (TObjectPtr<UDecalComponent>& DecalComponent = Decals[Side])
	{
		DecalComponent->DestroyComponent();
		DecalComponent = nullptr;
	}
	
	for (TObjectPtr<UDecalComponent>& DecalComponent : Decals)
	{
		if (DecalComponent)
			return false;
	}
	ParentComponent->DestroyComponent();
	return true;
}

void UDuster2DComponent::Update()
{
	for (int i = 0; i < 6; ++i)
	{
		if (Decals[i])
		{
			AddToSide(i);
		}
	}
}

void UDuster2DComponent::UpdateActor(AActor* Actor)
{
	if (Settings.bSided)
	{
		for (int i = 0; i < 6; ++i)
		{
			if (Settings.Sides[i].bOverrideActor && Settings.Sides[i].ActorToPointAtOverride == Actor)
				Decals[i]->SetWorldRotation(UKismetMathLibrary::FindLookAtRotation(Decals[i]->GetComponentLocation(), Settings.Sides[i].ActorToPointAtOverride->GetActorLocation()));
		}
	}

	if (Settings.ActorToPointAt == Actor)
	{
		Decals[0]->SetWorldRotation(UKismetMathLibrary::FindLookAtRotation(Decals[0]->GetComponentLocation(), Settings.ActorToPointAt->GetActorLocation()));
	}
}
