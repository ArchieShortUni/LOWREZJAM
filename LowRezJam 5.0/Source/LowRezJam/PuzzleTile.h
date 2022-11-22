// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PaperSpriteComponent.h"
#include "PaperSprite.h"
#include "PuzzleTile.generated.h"

UCLASS()
class LOWREZJAM_API APuzzleTile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APuzzleTile();

	UPROPERTY(Instanced,EditAnywhere, BlueprintReadWrite,Category="Sprites")
	UPaperSpriteComponent*  TileBaseSprite;

	UPROPERTY(Instanced,EditAnywhere, BlueprintReadWrite,Category="Sprites")
	UPaperSpriteComponent*  TileImageSprite;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Sprites")
	UPaperSprite* HighlightSprite;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Sprites")
	UPaperSprite* SelectedSprite;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Sprites")
	UPaperSprite* DefaultSprite;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Sprites")
	UPaperSprite* EmptySprite;
	

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool IsEmptyTile = false; 

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	FVector2D GridPosition;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	FVector2D GridDestination = FVector2D(0.f,0.f); 

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void Highlight();
	
	UFUNCTION(BlueprintCallable)
	void ReturnToDefault();
	

	UFUNCTION(BlueprintCallable)
	void Select();
	
	UFUNCTION(BlueprintCallable)
	bool CheckInPlace();

	UFUNCTION(BlueprintCallable)
	void MakeEmptyTile(); 

};
