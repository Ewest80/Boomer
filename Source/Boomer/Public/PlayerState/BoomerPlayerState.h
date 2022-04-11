// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "BoomerPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class BOOMER_API ABoomerPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	virtual void OnRep_Score() override;
	void AddToScore(float ScoreAmount);

private:
	class ABoomerCharacter* Character;
	class ABoomer_PlayerController* Controller;
};
