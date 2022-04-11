// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerController/Boomer_PlayerController.h"

#include "Character/BoomerCharacter.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "HUD/Boomer_HUD.h"
#include "HUD/CharacterOverlay.h"

void ABoomer_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	BoomerHUD = Cast<ABoomer_HUD>(GetHUD());
}

void ABoomer_PlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	ABoomerCharacter* BoomerCharacter = Cast<ABoomerCharacter>(InPawn);
	if (BoomerCharacter)
	{
		SetHUDHealth(BoomerCharacter->GetHealth(), BoomerCharacter->GetMaxHealth());
	}
}

void ABoomer_PlayerController::SetHUDHealth(float Health, float MaxHealth)
{
	BoomerHUD = BoomerHUD == nullptr ? Cast<ABoomer_HUD>(GetHUD()) : BoomerHUD;

	bool bHUDValid = BoomerHUD &&
		BoomerHUD->CharacterOverlay &&
		BoomerHUD->CharacterOverlay->HealthBar &&
		BoomerHUD->CharacterOverlay->HealthText;
	if (bHUDValid)
	{
		const float HealthPercentage = Health / MaxHealth;
		BoomerHUD->CharacterOverlay->HealthBar->SetPercent(HealthPercentage);
		FString HealthText = FString::Printf(TEXT("%d / %d"), FMath::CeilToInt(Health), FMath::CeilToInt(MaxHealth));
		BoomerHUD->CharacterOverlay->HealthText->SetText(FText::FromString(HealthText));
	}
}

void ABoomer_PlayerController::SetHUDScore(float Score)
{
	BoomerHUD = BoomerHUD == nullptr ? Cast<ABoomer_HUD>(GetHUD()) : BoomerHUD;
	
	bool bHUDValid = BoomerHUD &&
		BoomerHUD->CharacterOverlay &&
		BoomerHUD->CharacterOverlay->ScoreAmount;
	if (bHUDValid)
	{
		FString ScoreText = FString::Printf(TEXT("%d"), FMath::FloorToInt(Score));
		BoomerHUD->CharacterOverlay->ScoreAmount->SetText(FText::FromString(ScoreText));
	}
	
}

void ABoomer_PlayerController::SetHUDDefeats(int32 Defeats)
{
	BoomerHUD = BoomerHUD == nullptr ? Cast<ABoomer_HUD>(GetHUD()) : BoomerHUD;
	
	bool bHUDValid = BoomerHUD &&
		BoomerHUD->CharacterOverlay &&
		BoomerHUD->CharacterOverlay->DefeatsAmount;
	if (bHUDValid)
	{
		FString DefeatsText = FString::Printf(TEXT("%d"), Defeats);
		BoomerHUD->CharacterOverlay->DefeatsAmount->SetText(FText::FromString(DefeatsText));
	}
}
