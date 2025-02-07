#include "DusterSubsystem.h"

void UDusterSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	DusterControl = MakeShareable(GetMutableDefault<UDusterControl>());
}

void UDusterSubsystem::Deinitialize() {}

TSharedPtr<UDusterControl>& UDusterSubsystem::GetDusterControl() 
{
	return DusterControl;
}
