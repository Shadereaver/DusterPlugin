#include "Duster.h"
#include "DusterStyle.h"
#include "DusterCommands.h"
#include "SMainWidget.h"
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
		FExecuteAction::CreateRaw(this, &FDusterModule::PluginButtonClicked), FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FDusterModule::RegisterMenus));

	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(DusterTabName, FOnSpawnTab::CreateRaw(this, &FDusterModule::OnSpawnPluginTab))
	.SetDisplayName(LOCTEXT("FDusterTabTitle", "Duster"))
	.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FDusterModule::ShutdownModule()
{
	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FDusterStyle::Shutdown();

	FDusterCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(DusterTabName);
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
			SNew(SMainWidget)
		];
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FDusterModule, Duster)