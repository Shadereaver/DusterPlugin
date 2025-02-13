#include "DusterSubsystem.h"

#include "LevelEditor.h"
#include "LevelEditorSubsystem.h"
#include "Elements/Framework/TypedElementSelectionSet.h"
#include "Duster3DComponent.h"

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
