// Copyright Epic Games, Inc. All Rights Reserved.

#include "UI_ProjectGameMode.h"
#include "UI_ProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUI_ProjectGameMode::AUI_ProjectGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
