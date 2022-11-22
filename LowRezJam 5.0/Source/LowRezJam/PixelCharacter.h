// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "PaperSpriteComponent.h"
#include "PixelCharacterMovement.h"

#include "PaperFlipbookComponent.h" 
#include "GameFramework/Pawn.h"
#include "PixelCharacter.generated.h"

UCLASS()
class LOWREZJAM_API APixelCharacter : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APixelCharacter();

	UPROPERTY(EditAnywhere, Category="Components")
	UBoxComponent* HitBox;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Components")
	UPaperFlipbookComponent* CharacterFlipbook;

	UPROPERTY()
	UPixelCharacterMovement* PixelMovementComponent;

	UPROPERTY(BlueprintReadOnly, Category="Movement")
	FVector CurrentMovementVector;

	

	UPROPERTY(BlueprintReadOnly, Category="Movement")
	bool IsCharacterMoving = false; 
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual UPawnMovementComponent* GetMovementComponent() const override;

	


private:
	void MoveForward(float value);
	void MoveRight(float value);

	FVector LastMovement; 
	

};
