// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include <vector> 
#include "GameFramework/Pawn.h"
#include "PaperSpriteComponent.h"
#include "PuzzleTile.h"
#include "PicturePuzzle.generated.h"

UCLASS()
class LOWREZJAM_API APicturePuzzle : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APicturePuzzle();

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Sprites")
	UPaperSpriteComponent* BackgroundSprite;


	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Logic")
	APuzzleTile* testTile;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FVector2D CurrentGridPosition = FVector2D(0,0);
	
	std::vector<std::vector<APuzzleTile*>> TileVector;
	std::vector<std::vector<bool>> FilledVector;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Logic")
	int NumberOfEmptyTiles = 3; 

	//Tile Images
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Sprites")
	UPaperSprite* ImageTileStartingSprite;


protected:
	                        // Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<class APuzzleTile> puzzleTile;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
private:
	bool selectMode = false;
	bool highlightMode = true;
	bool IsPuzzleComplete();

	void Swap_Tile_Positions(FVector2D position1, FVector2D position2);
	void Shuffle_Tiles(); 

	void GridInputUp();
	void GridInputRight();
	void GridInputLeft();
	void GridInputDown();

	void SelectionMove(FVector2D Direction);
	void HighlightMove(FVector2D Direction);

	void ChangeSelection();

};
