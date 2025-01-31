#include "DusterDetails.h"

FReply UDusterDetails::Save()
{

	UE_LOG(LogTemp, Display, TEXT("Save"));
	return FReply::Handled();
}

FReply UDusterDetails::Add()
{
	UE_LOG(LogTemp, Display, TEXT("Add"));
	return FReply::Handled();
}

FReply UDusterDetails::Mat()
{
	UE_LOG(LogTemp, Display, TEXT("Mat"));
	return FReply::Handled();
}

FReply UDusterDetails::Remove()
{
	UE_LOG(LogTemp, Display, TEXT("Remove"));
	return FReply::Handled();
}

void UDusterDetails::Checkbox(ECheckBoxState State, int side)
{
	switch (State)
	{
	case ECheckBoxState::Unchecked:
		Sides[side] = false;
		break;
	case ECheckBoxState::Checked:
		Sides[side] = true;
		break;
	case ECheckBoxState::Undetermined:
		Sides[side] = false;
		break;
	}
	UE_LOG(LogTemp, Display, TEXT("check: %d : %d"), side, Sides[side]);
}

TArray<bool> UDusterDetails::Sides = {false, false, false, false, false, false};
