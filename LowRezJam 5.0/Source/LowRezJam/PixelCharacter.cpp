// Fill out your copyright notice in the Description page of Project Settings.


#include "PixelCharacter.h"

#include "Misc/OutputDeviceNull.h"

// Sets default values
APixelCharacter::APixelCharacter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Default possession
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	HitBox = CreateDefaultSubobject<UBoxComponent>("CharacterHitbox");
	HitBox->SetBoxExtent(FVector(10.f,10.f,1.f),true);
	HitBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	HitBox->SetCollisionProfileName(TEXT("Pawn"));

	RootComponent = HitBox;
	SetRootComponent(HitBox);

	CharacterFlipbook = CreateDefaultSubobject<UPaperFlipbookComponent>("CharacterFlipbook");
	CharacterFlipbook->SetupAttachment(HitBox);

	PixelMovementComponent = CreateDefaultSubobject<UPixelCharacterMovement>("CMovementComponent");
	PixelMovementComponent->UpdatedComponent = RootComponent;
}

// Called when the game starts or when spawned
void APixelCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APixelCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	LastMovement = CurrentMovementVector; 
	CurrentMovementVector = PixelMovementComponent->CurrentMovement;

	if((!LastMovement.Equals(PixelMovementComponent->CurrentMovement)) || (IsCharacterMoving == true && PixelMovementComponent->isMoving == false))
	{
		IsCharacterMoving = PixelMovementComponent->isMoving;
		FOutputDeviceNull AR; 
		this->CallFunctionByNameWithArguments(TEXT("Movement_Change"),AR,NULL,true);
	}
	IsCharacterMoving = PixelMovementComponent->isMoving;

	
}

// Called to bind functionality to input
void APixelCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAxis("MoveForward", this, &APixelCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APixelCharacter::MoveRight); 

}

UPawnMovementComponent* APixelCharacter::GetMovementComponent() const
{
	return Super::GetMovementComponent();
}

void APixelCharacter::MoveForward(float value)
{
	if (PixelMovementComponent && (PixelMovementComponent->UpdatedComponent == RootComponent))
	{
		PixelMovementComponent->AddInputVector(GetActorForwardVector() * value);
		
	}
}

void APixelCharacter::MoveRight(float value)
{
	if (PixelMovementComponent && (PixelMovementComponent->UpdatedComponent == RootComponent))
	{
		PixelMovementComponent->AddInputVector(GetActorRightVector() * value);
	}
}

