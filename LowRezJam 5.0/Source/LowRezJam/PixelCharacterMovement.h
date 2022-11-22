// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PawnMovementComponent.h"
#include "PixelCharacterMovement.generated.h"

/**
 * 
 */
UCLASS()
class LOWREZJAM_API UPixelCharacterMovement : public UPawnMovementComponent
{
	GENERATED_BODY()
public:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	float movementTimer = 0.f;
	float movementSpeed = 0.1f;
	FVector CurrentMovement = FVector(0.f,0.f,0.f);
	bool isMoving = false;
	FVector LastLocation = FVector(0.f,0.f,0.f); 
};
