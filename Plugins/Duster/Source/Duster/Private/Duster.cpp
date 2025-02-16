#include "Duster.h"
#include "DusterStyle.h"
#include "DusterCommands.h"
#include "DusterControl.h"
#include "DusterDetailsCustomization.h"
#include "DusterInfo2DCustomisation.h"
#include "DusterInfo3DCustomisation.h"
#include "DusterWidget.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"

static const FName DusterTabName("Duster");

#define LOCTEXT_NAMESPACE "FDusterModule"

void FDusterModule::StartupModule()
{
	FDusterStyle::Initialise();
	FDusterStyle::ReloadTextures();
	FDusterCommands::Register();

	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(FDusterCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateStatic(&FDusterModule::PluginButtonClicked), FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FDusterModule::RegisterMenus));

	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(DusterTabName, FOnSpawnTab::CreateStatic(&FDusterModule::OnSpawnPluginTab))
	.SetDisplayName(LOCTEXT("FDusterTabTitle", "Duster"))
	.SetMenuType(ETabSpawnerMenuType::Hidden);

	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

	PropertyModule.RegisterCustomClassLayout(UDusterControl::StaticClass()->GetFName(), FOnGetDetailCustomizationInstance::CreateStatic(&FDusterDetailsCustomization::MakeInstance));

	PropertyModule.RegisterCustomPropertyTypeLayout(FLocalDusterInfo3D::StaticStruct()->GetFName(), FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FDusterInfo3DCustomisation::MakeInstance));
	PropertyModule.RegisterCustomPropertyTypeLayout(FLocalDusterInfo2D::StaticStruct()->GetFName(), FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FDusterInfo2DCustomisation::MakeInstance));
}

void FDusterModule::ShutdownModule()
{
	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FDusterStyle::Shutdown();

	FDusterCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(DusterTabName);

	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

	PropertyModule.UnregisterCustomClassLayout(UDusterControl::StaticClass()->GetFName());

	PropertyModule.UnregisterCustomPropertyTypeLayout(FLocalDusterInfo3D::StaticStruct()->GetFName());
	PropertyModule.UnregisterCustomPropertyTypeLayout(FLocalDusterInfo2D::StaticStruct()->GetFName());
}

void FDusterModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(DusterTabName);
}

void FDusterModule::RegisterMenus()
{
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FDusterCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FDusterCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

TSharedRef<SDockTab> FDusterModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	return SNew(SDockTab)
		.TabRole(NomadTab)
		[
			SNew(SDusterWidget)
		];
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FDusterModule, Duster)