// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/BoomerGameMode.h"

#include "Character/BoomerCharacter.h"

void ABoomerGameMode::PlayerEliminated(ABoomerCharacter* ElimCharacter, ABoomer_PlayerController* VictimController,
                                       ABoomer_PlayerController* AttackerController)
{
	if (ElimCharacter)
	{
		ElimCharacter->Elim();
	}
}