#include "DusterSubsystem.h"

void UDusterSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	DusterControl = GetMutableDefault<UDusterControl>();
}

void UDusterSubsystem::Deinitialize() {}

TObjectPtr<UDusterControl>& UDusterSubsystem::GetDusterControl() 
{
	return DusterControl;
}
