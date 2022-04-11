// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/BoomerGameMode.h"

#include "Character/BoomerCharacter.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerController/Boomer_PlayerController.h"
#include "PlayerState/BoomerPlayerState.h"

void ABoomerGameMode::PlayerEliminated(ABoomerCharacter* ElimCharacter, ABoomer_PlayerController* VictimController,
                                       ABoomer_PlayerController* AttackerController)
{
	ABoomerPlayerState* AttackerPlayerState = AttackerController ? Cast<ABoomerPlayerState>(AttackerController->PlayerState) : nullptr;
	ABoomerPlayerState* VictimPlayerState = VictimController ? Cast<ABoomerPlayerState>(VictimController->PlayerState) : nullptr;

	if (AttackerPlayerState && AttackerPlayerState != VictimPlayerState)
	{
		AttackerPlayerState->AddToScore(1.f);
	}
	if (VictimPlayerState)
	{
		VictimPlayerState->AddToDefeats(1);
	}
	
	if (ElimCharacter)
	{
		ElimCharacter->Elim();
	}
}

void ABoomerGameMode::RequestRespawn(ACharacter* ElimmedCharacter, AController* ElimmedController)
{
	if (ElimmedCharacter)
	{
		ElimmedCharacter->Reset();
		ElimmedCharacter->Destroy();
	}
	if (ElimmedController)
	{
		TArray<AActor*> PlayerStarts;
		UGameplayStatics::GetAllActorsOfClass(this, APlayerStart::StaticClass(), PlayerStarts);
		int32 Selection = FMath::RandRange(0, PlayerStarts.Num() - 1);
		RestartPlayerAtPlayerStart(ElimmedController, PlayerStarts[Selection]);
	}
}
