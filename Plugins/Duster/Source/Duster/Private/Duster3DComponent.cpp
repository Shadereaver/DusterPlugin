#include "Duster3DComponent.h"

#include "AssetToolsModule.h"
#include "ContentBrowserModule.h"
#include "IContentBrowserSingleton.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "UObject/SavePackage.h"
#include "UDynamicMesh.h"
#include "GeometryScript/MeshAssetFunctions.h"
#include "GeometryScript/MeshSelectionFunctions.h"
#include "GeometryScript/MeshBasicEditFunctions.h"
#include "GeometryScript/MeshModelingFunctions.h"
#include "GeometryScript/MeshSubdivideFunctions.h"
#include "GeometryScript/MeshNormalsFunctions.h"
#include "GeometryScript/ListUtilityFunctions.h"

void UDuster3DComponent::CreateMesh_Implementation()
{
	OriginalMesh = GetOwner()->FindComponentByClass<UStaticMeshComponent>();
	UDynamicMesh* DynamicMesh = NewObject<UDynamicMesh>();

	EGeometryScriptOutcomePins Outcome = EGeometryScriptOutcomePins::Failure;
	FGeometryScriptCopyMeshFromAssetOptions CopyFromOptions{true,true,true,true};
	FGeometryScriptMeshReadLOD LODSetings{EGeometryScriptLODType::MaxAvailable, 0};
	
	DynamicMesh = UGeometryScriptLibrary_StaticMeshFunctions::CopyMeshFromStaticMesh(OriginalMesh->GetStaticMesh(), DynamicMesh, CopyFromOptions, LODSetings, Outcome);

	if (Outcome == EGeometryScriptOutcomePins::Failure)
		return;

	FGeometryScriptMeshSelection Selection;
	DynamicMesh = UGeometryScriptLibrary_MeshSelectionFunctions::SelectMeshElementsByNormalAngle(DynamicMesh, Selection, FVector::UpVector, 5, EGeometryScriptMeshSelectionType::Triangles, true);

	int NumDeleted;
	DynamicMesh = UGeometryScriptLibrary_MeshBasicEditFunctions::DeleteSelectedTrianglesFromMesh(DynamicMesh, Selection, NumDeleted);

	DynamicMesh = UGeometryScriptLibrary_MeshSelectionFunctions::CreateSelectAllMeshSelection(DynamicMesh, Selection);

	FGeometryScriptMeshEditPolygroupOptions GroupOptions{EGeometryScriptMeshEditPolygroupMode::PreserveExisting, 0};
	FGeometryScriptMeshLinearExtrudeOptions ExtrudeOptions{LocalDusterInfo3D.Height, EGeometryScriptLinearExtrudeDirection::AverageFaceNormal, FVector::UpVector, EGeometryScriptPolyOperationArea::EntireSelection, GroupOptions, 1, false};
	DynamicMesh = UGeometryScriptLibrary_MeshModelingFunctions::ApplyMeshLinearExtrudeFaces(DynamicMesh, ExtrudeOptions, Selection);

	DynamicMesh = UGeometryScriptLibrary_MeshSubdivideFunctions::ApplyUniformTessellation(DynamicMesh, LocalDusterInfo3D.Resolution);

	FGeometryScriptVectorList FlattenedNormals;
	bool bIsValid, bHasIDGaps;
	DynamicMesh = UGeometryScriptLibrary_MeshNormalsFunctions::GetMeshPerVertexNormals(DynamicMesh, FlattenedNormals,bIsValid, bHasIDGaps);

	TArray<FVector> NormalVectors;
	UGeometryScriptLibrary_ListUtilityFunctions::ConvertVectorListToArray(FlattenedNormals, NormalVectors);

	
}

bool UDuster3DComponent::IsEditorOnly() const
{
	return true;
}

FString UDuster3DComponent::CreateName(FString InName)
{
	FAssetToolsModule& AssetToolsModule = FModuleManager::Get().LoadModuleChecked<FAssetToolsModule>("AssetTools");

	FString Name, PackageName;
	AssetToolsModule.Get().CreateUniqueAssetName(TEXT("/Game/Duster/GeneratedMeshes/"), InName + TEXT("_DGM"), PackageName, Name);
	
	return PackageName;
}

void UDuster3DComponent::SaveAsset(FString PackageName, UObject* Object)
{
	FContentBrowserModule& ContentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>("ContentBrowser");
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry"));
	IAssetRegistry& AssetRegistry = AssetRegistryModule.Get();

	UPackage* Package = CreatePackage(*PackageName);

	FSavePackageArgs Args;
	Args.TopLevelFlags = RF_Public | RF_Standalone;

	UPackage::Save(Package, Object, *FPackageName::LongPackageNameToFilename(PackageName, FPackageName::GetAssetPackageExtension()), Args);

	AssetRegistry.AssetCreated(Object);
 
	TArray<UObject*> Objects;
	Objects.Add(Object);
	ContentBrowserModule.Get().SyncBrowserToAssets(Objects);
}

UStaticMeshComponent* UDuster3DComponent::CreateMeshComponent(AActor* Actor, UStaticMeshComponent* OriginalMeshComponent)
{
	UStaticMeshComponent* GeneratedMeshComponent = NewObject<UStaticMeshComponent>(Actor);
	Actor->AddInstanceComponent(GeneratedMeshComponent);
	GeneratedMeshComponent->RegisterComponent();
	GeneratedMeshComponent->AttachToComponent(OriginalMeshComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);
	GEditor->NoteSelectionChange();
	return GeneratedMeshComponent;
}
