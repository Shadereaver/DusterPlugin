#include "Duster3DComponent.h"

#include "AssetToolsModule.h"
#include "ContentBrowserModule.h"
#include "IContentBrowserSingleton.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "UObject/SavePackage.h"
#include "UDynamicMesh.h"
#include "AssetRegistry/AssetRegistryHelpers.h"
#include "GeometryScript/MeshAssetFunctions.h"
#include "GeometryScript/MeshSelectionFunctions.h"
#include "GeometryScript/MeshBasicEditFunctions.h"
#include "GeometryScript/MeshModelingFunctions.h"
#include "GeometryScript/MeshSubdivideFunctions.h"
#include "GeometryScript/MeshNormalsFunctions.h"
#include "GeometryScript/ListUtilityFunctions.h"
#include "GeometryScript/MeshSelectionQueryFunctions.h"
#include "GeometryScript/MeshDeformFunctions.h"
#include "GeometryScript/MeshSimplifyFunctions.h"
#include "GeometryScriptingEditor/Public/GeometryScript/CreateNewAssetUtilityFunctions.h"
#include "Kismet/KismetMathLibrary.h"
#include "EditorScriptingUtilities/Public/EditorAssetLibrary.h"

void UDuster3DComponent::CreateMesh_Implementation()
{
	OriginalMeshComponent = GetOwner()->FindComponentByClass<UStaticMeshComponent>();
	UDynamicMesh* DynamicMesh = NewObject<UDynamicMesh>();

	EGeometryScriptOutcomePins Outcome = EGeometryScriptOutcomePins::Failure;
	FGeometryScriptCopyMeshFromAssetOptions CopyFromOptions{true,true,true,true};
	FGeometryScriptMeshReadLOD ReadLOD{EGeometryScriptLODType::MaxAvailable, 0};
	
	DynamicMesh = UGeometryScriptLibrary_StaticMeshFunctions::CopyMeshFromStaticMesh(OriginalMeshComponent->GetStaticMesh(), DynamicMesh, CopyFromOptions, ReadLOD, Outcome);

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

	for (FVector& NormalVector : NormalVectors)
	{
		NormalVector = NormalVector.GetSafeNormal2D();
	}

	UGeometryScriptLibrary_ListUtilityFunctions::ConvertArrayToVectorList(NormalVectors, FlattenedNormals);

	DynamicMesh = UGeometryScriptLibrary_MeshSelectionFunctions::CreateSelectAllMeshSelection(DynamicMesh, Selection);

	TArray<FGeometryScriptIndexList> IndexLoops;
	TArray<FGeometryScriptPolyPath> PathLoops;
	int NumLoops;
	bool bFoundErrors;
	DynamicMesh = UGeometryScriptLibrary_MeshSelectionQueryFunctions::GetMeshSelectionBoundaryLoops(DynamicMesh, Selection, IndexLoops, PathLoops, NumLoops, bFoundErrors);

	FGeometryScriptMeshSelection AccumulatedRingSelect;
	DynamicMesh = UGeometryScriptLibrary_MeshSelectionFunctions::ConvertIndexListToMeshSelection(DynamicMesh, IndexLoops[0], EGeometryScriptMeshSelectionType::Vertices, AccumulatedRingSelect);

	for (FGeometryScriptIndexList IndexList : IndexLoops)
	{
		DynamicMesh = UGeometryScriptLibrary_MeshSelectionFunctions::ConvertIndexListToMeshSelection(DynamicMesh, IndexList, EGeometryScriptMeshSelectionType::Vertices, Selection);
		UGeometryScriptLibrary_MeshSelectionFunctions::CombineMeshSelections(AccumulatedRingSelect, Selection, AccumulatedRingSelect);
	}

	FGeometryScriptMeshSelection SingleRing = AccumulatedRingSelect;
	FGeometryScriptMeshSelection FullRing = AccumulatedRingSelect;

	for (int i = 0; i < LocalDusterInfo3D.Resolution + 1; ++i)
	{
		float MinTime, MaxTime;
		LocalDusterInfo3D.Falloff->GetTimeRange(MinTime, MaxTime);
		float ClampedValue = UKismetMathLibrary::MapRangeClamped(i, 0.0f, LocalDusterInfo3D.Resolution + 1, MinTime, MaxTime);
		float FalloffValue = LocalDusterInfo3D.Falloff->GetFloatValue(ClampedValue) - LocalDusterInfo3D.Falloff->GetFloatValue(0);

		DynamicMesh = UGeometryScriptLibrary_MeshDeformFunctions::ApplyDisplaceFromPerVertexVectors(DynamicMesh, SingleRing, FlattenedNormals, FalloffValue * LocalDusterInfo3D.FalloffMultiplier);
		
		DynamicMesh = UGeometryScriptLibrary_MeshSelectionFunctions::InvertMeshSelection(DynamicMesh, FullRing, Selection);

		DynamicMesh = UGeometryScriptLibrary_MeshSelectionFunctions::ExpandContractMeshSelection(DynamicMesh, FullRing, FullRing);

		UGeometryScriptLibrary_MeshSelectionFunctions::CombineMeshSelections(FullRing, Selection, SingleRing, EGeometryScriptCombineSelectionMode::Intersection);
	}

	FGeometryScriptPlanarSimplifyOptions SimplifyOptions{0.001f, true};
	DynamicMesh = UGeometryScriptLibrary_MeshSimplifyFunctions::ApplySimplifyToPlanar(DynamicMesh, SimplifyOptions);

	FGeometryScriptCalculateNormalsOptions RecomputeOptions{true, true};
	DynamicMesh = UGeometryScriptLibrary_MeshNormalsFunctions::RecomputeNormals(DynamicMesh, RecomputeOptions, false);

	if (GeneratedMesh)
	{
		FGeometryScriptCopyMeshToAssetOptions CopyMeshToAssetOptions{false, false, false, true, false};
		FGeometryScriptMeshWriteLOD WriteLOD{false, 0};
		UGeometryScriptLibrary_StaticMeshFunctions::CopyMeshToStaticMesh(DynamicMesh, GeneratedMesh, CopyMeshToAssetOptions, WriteLOD, Outcome);
		if (Outcome == EGeometryScriptOutcomePins::Failure)
			return;
	}
	else
	{
		FAssetToolsModule& AssetToolsModule = FModuleManager::Get().LoadModuleChecked<FAssetToolsModule>("AssetTools");

		FString Name;
		AssetToolsModule.Get().CreateUniqueAssetName(TEXT("/Game/Duster/GeneratedMeshes/"), OriginalMeshComponent->GetStaticMesh().GetName() + TEXT("_DGM"), GeneratedMeshName, Name);
		
		FGeometryScriptCreateNewStaticMeshAssetOptions NewStaticMeshAssetOptions{};
		GeneratedMesh = UGeometryScriptLibrary_CreateNewAssetFunctions::CreateNewStaticMeshAssetFromMesh(DynamicMesh, GeneratedMeshName, NewStaticMeshAssetOptions, Outcome);
		if (Outcome == EGeometryScriptOutcomePins::Failure)
			return;

		FContentBrowserModule& ContentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>("ContentBrowser");
		FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry"));
		IAssetRegistry& AssetRegistry = AssetRegistryModule.Get();

		UPackage* Package = CreatePackage(*GeneratedMeshName);

		FSavePackageArgs Args;
		Args.TopLevelFlags = RF_Public | RF_Standalone;

		UPackage::Save(Package, GeneratedMesh, *FPackageName::LongPackageNameToFilename(GeneratedMeshName, FPackageName::GetAssetPackageExtension()), Args);

		AssetRegistry.AssetCreated(GeneratedMesh);
 
		TArray<UObject*> Objects;
		Objects.Add(GeneratedMesh);
		ContentBrowserModule.Get().SyncBrowserToAssets(Objects);
	}

	GeneratedMesh->SetMaterial(0, LocalDusterInfo3D.Material);

	if (!GeneratedMeshComponent)
	{
		
		GeneratedMeshComponent = NewObject<UStaticMeshComponent>(GetOwner());
		GetOwner()->AddInstanceComponent(GeneratedMeshComponent);
		GeneratedMeshComponent->RegisterComponent();
		GeneratedMeshComponent->AttachToComponent(OriginalMeshComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);
		GEditor->NoteSelectionChange();
	}
	
	GeneratedMeshComponent->SetStaticMesh(GeneratedMesh);
}

bool UDuster3DComponent::IsEditorOnly() const
{
	return true;
}

void UDuster3DComponent::Delete()
{
	UEditorAssetLibrary::DeleteAsset(GeneratedMeshName);
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

UStaticMeshComponent* UDuster3DComponent::CreateMeshComponent(AActor* Actor, UStaticMeshComponent* MeshComponent)
{
	GeneratedMeshComponent = NewObject<UStaticMeshComponent>(Actor);
	Actor->AddInstanceComponent(GeneratedMeshComponent);
	GeneratedMeshComponent->RegisterComponent();
	GeneratedMeshComponent->AttachToComponent(MeshComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);
	GEditor->NoteSelectionChange();
	return GeneratedMeshComponent;
}
