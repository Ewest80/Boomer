// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BoomerAnimInstance.h"

#include "Character/BoomerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Weapon/Weapon.h"

void UBoomerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	BoomerCharacter = Cast<ABoomerCharacter>(TryGetPawnOwner());
}

void UBoomerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (BoomerCharacter == nullptr)
	{
		BoomerCharacter = Cast<ABoomerCharacter>(TryGetPawnOwner());
	}
	if (BoomerCharacter == nullptr) { return; }

	FVector Velocity = BoomerCharacter->GetVelocity();
	Velocity.Z = 0.f;
	Speed = Velocity.Size();

	bIsInAir = BoomerCharacter->GetCharacterMovement()->IsFalling();
	bIsAccelerating = BoomerCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0 ? true : false;
	bWeaponEquipped = BoomerCharacter->IsWeaponEquipped();
	EquippedWeapon = BoomerCharacter->GetEquippedWeapon();
	bIsCrouched = BoomerCharacter->bIsCrouched;
	bAiming = BoomerCharacter->IsAiming();
	TurningInPlace = BoomerCharacter->GetTurningInPlace();
	bRotateRootbone = BoomerCharacter->ShouldRotateRootBone();

	// Offset Yaw for Strafing
	FRotator AimRotation = BoomerCharacter->GetBaseAimRotation();
	FRotator MovementRotation = UKismetMathLibrary::MakeRotFromX(BoomerCharacter->GetVelocity());
	FRotator DeltaRot = UKismetMathLibrary::NormalizedDeltaRotator(MovementRotation, AimRotation);
	DeltaRotation = FMath::RInterpTo(DeltaRotation, DeltaRot, DeltaSeconds, 6.f);
	YawOffset = DeltaRotation.Yaw;

	CharacterRotationLastFrame = CharacterRotation;
	CharacterRotation = BoomerCharacter->GetActorRotation();
	const FRotator Delta = UKismetMathLibrary::NormalizedDeltaRotator(CharacterRotation, CharacterRotationLastFrame);
	const float Target = Delta.Yaw / DeltaSeconds;
	const float Interp = FMath::FInterpTo(Lean, Target, DeltaSeconds, 6.f);
	Lean = FMath::Clamp(Interp, -90.f, 90.f);

	AO_Yaw = BoomerCharacter->GetAOYaw();
	AO_Pitch = BoomerCharacter->GetAOPitch();

	// Setup left hand to LeftHandWeaponSocket
	if (bWeaponEquipped && EquippedWeapon && EquippedWeapon->GetWeaponMesh() && BoomerCharacter->GetMesh())
	{
		LeftHandTransform = EquippedWeapon->GetWeaponMesh()->GetSocketTransform(FName("LeftHandSocket"), RTS_World);

		FVector OutPosition;
		FRotator OutRotation;
		BoomerCharacter->GetMesh()->TransformToBoneSpace(FName("hand_r"), LeftHandTransform.GetLocation(),
		                                                 FRotator::ZeroRotator, OutPosition, OutRotation);
		LeftHandTransform.SetLocation(OutPosition);
		LeftHandTransform.SetRotation(FQuat(OutRotation));

		if (BoomerCharacter->IsLocallyControlled())
		{
			bLocallyControlled = true;
			FTransform RightHandTransform = EquippedWeapon->GetWeaponMesh()->GetSocketTransform(FName("Hand_R"), RTS_World);
			FRotator LookAtRocation = UKismetMathLibrary::FindLookAtRotation(RightHandTransform.GetLocation(), RightHandTransform.GetLocation() + (RightHandTransform.GetLocation() - BoomerCharacter->GetHitTarget()));
			RightHandRotation = FMath::RInterpTo(RightHandRotation, LookAtRocation, DeltaSeconds, 30.f);
		}

		// FTransform MuzzleTipTransform = EquippedWeapon->GetWeaponMesh()->GetSocketTransform(FName("MuzzleFlash"), RTS_World);
		// FVector MuzzleX(FRotationMatrix(MuzzleTipTransform.GetRotation().Rotator()).GetUnitAxis(EAxis::X));
		// DrawDebugLine(GetWorld(), MuzzleTipTransform.GetLocation(), MuzzleTipTransform.GetLocation() + MuzzleX * 1000.f, FColor::Red);
		// DrawDebugLine(GetWorld(), MuzzleTipTransform.GetLocation(), BoomerCharacter->GetHitTarget(), FColor::Orange);
	}
}
