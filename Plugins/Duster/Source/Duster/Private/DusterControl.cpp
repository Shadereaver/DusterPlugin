#include "DusterControl.h"

#include "AssetToolsModule.h"
#include "Duster2DComponent.h"
#include "Duster3DComponent.h"
#include "DusterInfo2D.h"
#include "DusterInfo3D.h"
#include "DusterModalName.h"
#include "DusterSubsystem.h"
#include "DusterUtilityActor.h"
#include "EditorAssetLibrary.h"
#include "MaterialDomain.h"
#include "Selection.h"
#include "Editor/MaterialEditor/Public/MaterialEditingLibrary.h"
#include "Factories/DataAssetFactory.h"
#include "Factories/MaterialFactoryNew.h"
#include "Materials/MaterialExpressionAdd.h"
#include "Materials/MaterialExpressionDivide.h"
#include "Materials/MaterialExpressionMultiply.h"
#include "Materials/MaterialExpressionScalarParameter.h"
#include "Materials/MaterialExpressionTextureSampleParameter2D.h"

FReply UDusterControl::Add3D()
{
	for (TObjectPtr<AActor> Actor : SelectedActors)
	{
		if (!Actor->FindComponentByClass<UDuster3DComponent>())
		{
			UDuster3DComponent* Component3D = NewObject<UDuster3DComponent>(Actor);
			Actor->AddInstanceComponent(Component3D);
			GEditor->NoteSelectionChange();
			Component3D->Settings = LocalCurrent3DProfile;
			Component3D->Profile = Current3DProfile;
			Component3D->CreateMesh();
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
			Component3D->DestroyComponent();
			GEditor->NoteSelectionChange();
		}
	}
	return	FReply::Handled();
}

FReply UDusterControl::Create3D()
{
	FString Name;
	if (GetName(Name) == Cancel)
		return FReply::Handled();

	Validate3DName(Name);

	FString PackageName;
	UDusterInfo3D* New3DProfile = Create3DAsset(PackageName, Name);
	
	UDusterSubsystem::SaveAsset(PackageName, New3DProfile);
	
	Current3DProfile = New3DProfile;
	
	return FReply::Handled();
}

FReply UDusterControl::Delete3D() const
{
	UEditorAssetLibrary::DeleteAsset(Current3DProfile.GetPackage().GetName());
	return	FReply::Handled();
}

FReply UDusterControl::Copy3D()
{
	FString Name;
	if (GetName(Name) == Cancel)
		return FReply::Handled();

	Validate3DName(Name);

	FString PackageName;
	UDusterInfo3D* New3DProfile = Create3DAsset(PackageName, Name);
	
	if (Current3DProfile)
		New3DProfile->SetData(Current3DProfile);

	UDusterSubsystem::SaveAsset(PackageName, New3DProfile);

	Current3DProfile = New3DProfile;

	return	FReply::Handled();
}

FReply UDusterControl::Save3D() const
{
	if (!Current3DProfile)
		return FReply::Handled();
	
	Current3DProfile->SetData(LocalCurrent3DProfile);

	UDusterSubsystem::SaveAsset(Current3DProfile.GetPackage().GetName(), Current3DProfile);
	return	FReply::Handled();
}

void UDusterControl::UpdateMesh(const FPropertyChangedEvent&)
{
	for (const TObjectPtr<AActor> Actor : SelectedActors)
	{
		if (UDuster3DComponent* Component3D = Actor->FindComponentByClass<UDuster3DComponent>())
		{
			Component3D->Settings = LocalCurrent3DProfile;
			Component3D->Profile = Current3DProfile;
			Component3D->CreateMesh();
		}
	}
}

FReply UDusterControl::Create2D()
{
	FString Name;

	if (GetName(Name) == Cancel)
		return FReply::Handled();

	Validate2DName(Name);
	
	FString PackageName;
	UDusterInfo2D* New2DProfile = Create2DAsset(PackageName, Name);

	UDusterSubsystem::SaveAsset(PackageName, New2DProfile);

	Current2DProfile = New2DProfile;
	
	return	FReply::Handled();
}

FReply UDusterControl::Delete2D() const
{
	UEditorAssetLibrary::DeleteAsset(Current2DProfile.GetPackage().GetName());
	return	FReply::Handled();
}

FReply UDusterControl::Copy2D()
{
	FString Name;
	if (GetName(Name) == Cancel)
		return FReply::Handled();

	Validate2DName(Name);

	FString PackageName;
	UDusterInfo2D* New2DProfile = Create2DAsset(PackageName, Name);
	
	if (Current2DProfile)
		New2DProfile->SetData(Current2DProfile);

	UDusterSubsystem::SaveAsset(PackageName, New2DProfile);

	Current2DProfile = New2DProfile;
	return	FReply::Handled();
}

FReply UDusterControl::Save2D() const
{
	if (!Current2DProfile)
		return FReply::Handled();
	
	Current2DProfile->SetData(LocalCurrent2DProfile);
	
	UDusterSubsystem::SaveAsset(Current2DProfile.GetPackage().GetName(), Current2DProfile);
	
	return	FReply::Handled();
}

FReply UDusterControl::Add2D(const int Side)
{
	for (TObjectPtr<AActor> Actor : SelectedActors)
	{
		if (!Actor->FindComponentByClass<UDuster2DComponent>())
		{
			UDuster2DComponent* Component2D = NewObject<UDuster2DComponent>(Actor);
			Actor->AddInstanceComponent(Component2D);
			GEditor->NoteSelectionChange();
			Component2D->Settings = LocalCurrent2DProfile;
			Component2D->Profile = Current2DProfile;
		}
		if (UDuster2DComponent* Component2D = Actor->FindComponentByClass<UDuster2DComponent>())
		{
			Component2D->Settings = LocalCurrent2DProfile;
			Component2D->Profile = Current2DProfile;
			Component2D->Init();
			Component2D->AddToSide(Side);
		}
	}
	return	FReply::Handled();
}

FReply UDusterControl::Remove2D(const int Side)
{
	for (TObjectPtr<AActor> Actor : SelectedActors)
	{
		if (UDuster2DComponent* Component2D = Actor->FindComponentByClass<UDuster2DComponent>())
		{
			if (Component2D->Delete(Side))
				Component2D->DestroyComponent();
			
			GEditor->NoteSelectionChange();
		}
	}
	return	FReply::Handled();
}

FReply UDusterControl::Create2DMaterial()
{
	const FAssetToolsModule& AssetToolsModule = FModuleManager::Get().LoadModuleChecked<FAssetToolsModule>("AssetTools");

	UMaterialFactoryNew* Factory = NewObject<UMaterialFactoryNew>();
	UMaterial* Material = Cast<UMaterial>(AssetToolsModule.Get().CreateAssetWithDialog(UMaterial::StaticClass(), Factory));
	
	UMaterialExpressionAdd* Add = Cast<UMaterialExpressionAdd>(UMaterialEditingLibrary::CreateMaterialExpression(Material, UMaterialExpressionAdd::StaticClass()));
	UMaterialExpressionDivide* Divide = Cast<UMaterialExpressionDivide>(UMaterialEditingLibrary::CreateMaterialExpression(Material, UMaterialExpressionDivide::StaticClass()));
	UMaterialExpressionTextureSampleParameter2D* Texture = Cast<UMaterialExpressionTextureSampleParameter2D>(UMaterialEditingLibrary::CreateMaterialExpression(Material, UMaterialExpressionTextureSampleParameter2D::StaticClass()));
	UMaterialExpressionScalarParameter* Density = Cast<UMaterialExpressionScalarParameter>(UMaterialEditingLibrary::CreateMaterialExpression(Material, UMaterialExpressionScalarParameter::StaticClass()));
	UMaterialExpressionMultiply* Multiply = Cast<UMaterialExpressionMultiply>(UMaterialEditingLibrary::CreateMaterialExpression(Material, UMaterialExpressionMultiply::StaticClass()));

	Material->AddExpressionParameter(Multiply, Material->EditorParameters);
	Multiply->MaterialExpressionEditorX = -500;
	Multiply->MaterialExpressionEditorY = 100;
	
	Material->AddExpressionParameter(Add, Material->EditorParameters);
	Add->MaterialExpressionEditorX = -250;
	
	Material->AddExpressionParameter(Divide, Material->EditorParameters);
	Divide->ConstB = 10;
	Divide->MaterialExpressionEditorX = -700;
	Divide->MaterialExpressionEditorY = 200;
	
	Material->AddExpressionParameter(Texture, Material->EditorParameters);
	Texture->ParameterName = "Texture";
	Texture->MaterialExpressionEditorX = -800;
	Texture->MaterialExpressionEditorY = -50;
	
	Material->AddExpressionParameter(Density, Material->EditorParameters);
	Density->ParameterName = "Density";
	Density->MaterialExpressionEditorX = -800;
	Density->MaterialExpressionEditorY = 200;
	
	Density->ConnectExpression(&Divide->A, 0);
	Divide->ConnectExpression(&Multiply->B, 0);
	Texture->ConnectExpression(&Add->A, 0);
	Texture->ConnectExpression(&Multiply->A, 0);
	Multiply->ConnectExpression(&Add->B, 0);

	Material->GetEditorOnlyData()->BaseColor.Connect(0, Add);
	Material->GetEditorOnlyData()->Opacity.Connect(0, Add);
	Material->MaterialDomain = MD_DeferredDecal;
	Material->BlendMode = BLEND_Translucent;

	UDusterSubsystem::SaveAsset(Material->GetPackage()->GetName(), Material);
	
	return	FReply::Handled();
}

FReply UDusterControl::CreateActor()
{
	ADusterUtilityActor* SpawnedActor;
	if (TObjectPtr<AActor> Actor = SelectedActors[0])
		SpawnedActor = GEditor->GetEditorWorldContext().World()->SpawnActor<ADusterUtilityActor>(Actor->GetActorLocation(), Actor->GetActorRotation());
	else
		SpawnedActor = GEditor->GetEditorWorldContext().World()->SpawnActor<ADusterUtilityActor>(FVector::Zero(), FRotator::ZeroRotator);

	GEditor->SelectNone(true, true);
	GEditor->SelectActor(SpawnedActor, true, true);
	return	FReply::Handled();
}

void UDusterControl::Update2D()
{
	for (TObjectPtr<AActor> Actor : SelectedActors)
	{
		if (UDuster2DComponent* Component2D = Actor->FindComponentByClass<UDuster2DComponent>())
		{
			Component2D->Settings = LocalCurrent2DProfile;
			Component2D->Profile = Current2DProfile;
			Component2D->Update();
		}
	}
}

void UDusterControl::Profile3DChanged()
{
	if (!Current3DProfile)
	{
		LocalCurrent3DProfile.Material = nullptr;
		LocalCurrent3DProfile.Height = 0;
		LocalCurrent3DProfile.Falloff = nullptr;
		LocalCurrent3DProfile.Resolution = 0;
		LocalCurrent3DProfile.FalloffMultiplier = 1;
		return;
	}
	LocalCurrent3DProfile.Material = Current3DProfile->Material;
	LocalCurrent3DProfile.Height = Current3DProfile->Height;
	LocalCurrent3DProfile.Falloff = Current3DProfile->Falloff;
	LocalCurrent3DProfile.Resolution = Current3DProfile->Resolution;
	LocalCurrent3DProfile.FalloffMultiplier = Current3DProfile->FalloffMultiplier;
	LocalCurrent3DProfile.Profile = Current3DProfile;
}

void UDusterControl::Profile2DChanged()
{
	if (!Current2DProfile)
	{
		LocalCurrent2DProfile.Texture = nullptr;
		LocalCurrent2DProfile.Material = nullptr;
		LocalCurrent2DProfile.Density = 0;
		return;;
	}
	LocalCurrent2DProfile.Texture = Current2DProfile->Texture;
	LocalCurrent2DProfile.Material = Current2DProfile->Material;
	LocalCurrent2DProfile.Density = Current2DProfile->Density;
	LocalCurrent2DProfile.Profile = Current2DProfile;
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

void UDusterControl::UpdateLocal2D(const FLocalDusterInfo2D& Local)
{
	LocalCurrent2DProfile.Texture = Local.Texture;
	LocalCurrent2DProfile.Material = Local.Material;
	LocalCurrent2DProfile.Density = Local.Density;
	LocalCurrent2DProfile.Profile = Local.Profile;
}

void UDusterControl::OnSelectionChanged(const UTypedElementSelectionSet* SelectionSet)
{
	SelectedActors = SelectionSet->GetSelectedObjects<AActor>();

	for (TObjectPtr<AActor> Actor : SelectedActors)
	{
		if (TObjectPtr<UDuster3DComponent> Component3D = Actor->FindComponentByClass<UDuster3DComponent>())
		{
			Current3DProfile = Component3D->Profile;
			UpdateLocal3D(Component3D->Settings);
			break;
		}
	}
	for (TObjectPtr<AActor> Actor : SelectedActors)
	{
		if (TObjectPtr<UDuster2DComponent> Component2D = Actor->FindComponentByClass<UDuster2DComponent>())
		{
			Current2DProfile = Component2D->Profile;
			UpdateLocal2D(Component2D->Settings);
			break;
		}
	}
}

EButtonValue UDusterControl::GetName(FString& Name)
{
	const TSharedRef<SDusterModalName> DusterModalName = SNew(SDusterModalName);
	const TSharedRef<SWindow> ModalWindow = SNew(SWindow)
		.Title(FText::FromString("Pick name"))
		.MinHeight(100)
		.ClientSize(FVector2d(800, 500))
		[
			DusterModalName
		];

	DusterModalName->SetWindow(ModalWindow);
	
	FSlateApplication::Get().AddModalWindow(ModalWindow, DusterModalName->AsShared());
	
	return DusterModalName->GetResult(Name);
}

void UDusterControl::Validate3DName(FString& InName)
{
	if (InName == "")
		InName = "DA_Duster3DProfile_Untitled";

	if (!InName.StartsWith("DA_Duster3DProfile_"))
	{
		if (InName.StartsWith("DA_"))
			InName.InsertAt(3, "Duster3DProfile_");
		else if (InName.StartsWith("Duster3DProfile_"))
			InName = "DA_" + InName;
		else
			InName = "DA_Duster3DProfile_" + InName;
	}
}

UDusterInfo3D* UDusterControl::Create3DAsset(FString& OutPackageName, const FString& Name)
{
	const FAssetToolsModule& AssetToolsModule = FModuleManager::Get().LoadModuleChecked<FAssetToolsModule>("AssetTools");

	FString AssetName;
	AssetToolsModule.Get().CreateUniqueAssetName(TEXT("/Duster/3DSettings/"), Name, OutPackageName, AssetName);
	const FString PackagePath = FPackageName::GetLongPackagePath(OutPackageName);

	UDataAssetFactory* Factory = NewObject<UDataAssetFactory>(UDataAssetFactory::StaticClass());
	Factory->DataAssetClass = UDusterInfo3D::StaticClass();
	
	return Cast<UDusterInfo3D>(AssetToolsModule.Get().CreateAsset(AssetName, PackagePath, UDusterInfo3D::StaticClass(), Factory));
}

void UDusterControl::Validate2DName(FString& InName)
{
	if (InName == "")
		InName = "DA_Duster2DProfile_Untitled";

	if (!InName.StartsWith("DA_Duster2DProfile_"))
	{
		if (InName.StartsWith("DA_"))
			InName.InsertAt(3, "Duster2DProfile_");
		else if (InName.StartsWith("Duster2DProfile_"))
			InName = "DA_" + InName;
		else
			InName = "DA_Duster2DProfile_" + InName;
	}
}

UDusterInfo2D* UDusterControl::Create2DAsset(FString& OutPackageName, const FString& Name)
{
	const FAssetToolsModule& AssetToolsModule = FModuleManager::Get().LoadModuleChecked<FAssetToolsModule>("AssetTools");

	FString AssetName;
	AssetToolsModule.Get().CreateUniqueAssetName(TEXT("/Duster/2DSettings/"), Name, OutPackageName, AssetName);
	const FString PackagePath = FPackageName::GetLongPackagePath(OutPackageName);

	UDataAssetFactory* Factory = NewObject<UDataAssetFactory>(UDataAssetFactory::StaticClass());
	Factory->DataAssetClass = UDusterInfo2D::StaticClass();
	
	return Cast<UDusterInfo2D>(AssetToolsModule.Get().CreateAsset(AssetName, PackagePath, UDusterInfo2D::StaticClass(), Factory));
}

