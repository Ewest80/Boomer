// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "BoomerGameMode.generated.h"

/**
 * 
 */
UCLASS()
class BOOMER_API ABoomerGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	virtual void PlayerEliminated(class ABoomerCharacter* ElimCharacter, class ABoomer_PlayerController* VictimController, ABoomer_PlayerController* AttackerController);
	
};
