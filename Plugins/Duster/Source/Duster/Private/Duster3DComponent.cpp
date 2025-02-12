#include "Duster3DComponent.h"

#include "AssetToolsModule.h"
#include "ContentBrowserModule.h"
#include "IContentBrowserSingleton.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "UObject/SavePackage.h"


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
