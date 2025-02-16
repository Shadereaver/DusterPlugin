#include "DusterSubsystem.h"

#include "ContentBrowserModule.h"
#include "LevelEditor.h"
#include "LevelEditorSubsystem.h"
#include "Elements/Framework/TypedElementSelectionSet.h"
#include "Duster3DComponent.h"
#include "IContentBrowserSingleton.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "UObject/SavePackage.h"

void UDusterSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	DusterControl = GetMutableDefault<UDusterControl>();
	
	FLevelEditorModule& LevelEditorModule = FModuleManager::GetModuleChecked<FLevelEditorModule>("LevelEditor");
	LevelEditorModule.OnLevelEditorCreated().AddUObject(this, &UDusterSubsystem::BindSelectionChanged);
}

void UDusterSubsystem::Deinitialize() {}

TObjectPtr<UDusterControl>& UDusterSubsystem::GetDusterControl() 
{
	return DusterControl;
}

void UDusterSubsystem::BindSelectionChanged(TSharedPtr<ILevelEditor> LevelEditor)
{
	ULevelEditorSubsystem* LevelEditorSubsystem = GEditor->GetEditorSubsystem<ULevelEditorSubsystem>();
	LevelEditorSubsystem->GetSelectionSet()->OnSelectionChange.AddUniqueDynamic(DusterControl, &UDusterControl::OnSelectionChanged);
}

void UDusterSubsystem::SaveAsset(const FString& PackageName, const TObjectPtr<UObject>& Object)
{
	const FContentBrowserModule& ContentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>("ContentBrowser");
	const FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry"));
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
