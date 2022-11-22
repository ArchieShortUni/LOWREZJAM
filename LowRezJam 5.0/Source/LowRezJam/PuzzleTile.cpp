// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleTile.h"

// Sets default values
APuzzleTile::APuzzleTile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	TileBaseSprite = CreateDefaultSubobject<UPaperSpriteComponent>("Background Sprite");
	//TileBaseSprite->SetRelativeRotation(FRotator(90.f,0.f,0.f));
	TileBaseSprite->SetupAttachment(RootComponent);

	TileImageSprite= CreateDefaultSubobject<UPaperSpriteComponent>("Image Sprite");
	TileImageSprite->SetupAttachment(TileBaseSprite);
	TileImageSprite->SetRelativeLocation(FVector(0.f,0.1f,0.f));

	SelectedSprite = CreateDefaultSubobject<UPaperSprite>("Select Sprite");
	HighlightSprite = CreateDefaultSubobject<UPaperSprite>("Highlight Sprite");
	DefaultSprite = CreateDefaultSubobject<UPaperSprite>("Default Sprite");


	UE_LOG(LogTemp,Warning,TEXT("ChangedTile"));

}

// Called when the game starts or when spawned
void APuzzleTile::BeginPlay()
{
	Super::BeginPlay();
	SetActorRotation(FRotator(0.f,-90.f, -90.f)); 

}

// Called every frame
void APuzzleTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APuzzleTile::Highlight()
{
	TileBaseSprite->SetSprite(HighlightSprite);
}

void APuzzleTile::ReturnToDefault()
{
	TileBaseSprite->SetSprite(DefaultSprite);

}

void APuzzleTile::Select()
{
	TileBaseSprite->SetSprite(SelectedSprite); 
}

bool APuzzleTile::CheckInPlace()
{
	return (GridPosition == GridDestination); 
}

void APuzzleTile::MakeEmptyTile()
{
	IsEmptyTile = true;
	TileImageSprite->SetSprite(EmptySprite); 
}

