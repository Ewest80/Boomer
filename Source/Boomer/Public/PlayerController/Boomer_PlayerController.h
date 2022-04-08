// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Boomer_PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BOOMER_API ABoomer_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	void SetHUDHealth(float Health, float MaxHealth);

protected:
	virtual void BeginPlay() override;

private:
	class ABoomer_HUD* BoomerHUD;
};
