// Fill out your copyright notice in the Description page of Project Settings.


#include "PixelCharacterMovement.h"

void UPixelCharacterMovement::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Make sure that everything is still valid, and that we are allowed to move.
	if (!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime))
	{
		return;
	}
	
	isMoving = false; 

	//UE_LOG(LogTemp, Warning, TEXT("Is Falling %hs"),IsFalling()? "true" : "false" );
	// Get (and then clear) the movement vector that we set in ACollidingPawn::Tick
	FVector DesiredMovementThisFrame = ConsumeInputVector().GetClampedToMaxSize(1.0f) * DeltaTime;
	//UE_LOG(LogTemp, Warning, TEXT("Direction %s" ),*DesiredMovementThisFrame.ToString());

	if (!DesiredMovementThisFrame.IsNearlyZero())
	{
		isMoving = true; 


		if(movementTimer <= movementSpeed)
		{movementTimer += DeltaTime;}
		
		else
		{

			FVector Direction;
			float Length; 
			DesiredMovementThisFrame.ToDirectionAndLength(Direction,Length);

			//Diagonal Movement 
			if(Direction.X > 0.5f ){Direction.X = 1;}
			else if(Direction.X < -0.5f){Direction.X = -1;}
			if(Direction.Y > 0.5f){Direction.Y = 1;}
			else if(Direction.Y <-0.5f){Direction.Y = -1;}
			
			CurrentMovement = Direction;
			LastLocation = GetActorLocation();
			FHitResult Hit;
			SafeMoveUpdatedComponent(Direction, UpdatedComponent->GetComponentRotation(), true, Hit);
			if (Hit.IsValidBlockingHit()){
				UpdatedComponent->SetWorldLocation(LastLocation);
				//Actual movement against a wall and surface
				//float moved = SlideAlongSurface(DesiredMovementThisFrame, 1.f - Hit.Time, Hit.Normal, Hit);
				//Extra friction as its against multiple surfaces 
			}
			movementTimer = 0.f;
		}
		
		
		// If we bumped into something, try to slide along it
		
		//	UE_LOG(LogTemp, Warning, TEXT("Impact Normal Of Hit: %s"),*Hit.ImpactNormal.ToString());
		}
	else
	{
		isMoving = false; 

		if(movementTimer >= 0.f)
		{
			movementTimer -= DeltaTime*3; 
		}
	}

	}