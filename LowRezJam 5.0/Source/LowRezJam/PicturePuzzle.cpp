// Fill out your copyright notice in the Description page of Project Settings.


#include "PicturePuzzle.h"

#include <string>
#include <algorithm>

std::string ReplaceAll(std::string str, const std::string& from, const std::string& to) {
	size_t start_pos = 0;
	while((start_pos = str.find(from, start_pos)) != std::string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
	}
	return str;
}


// Sets default values
APicturePuzzle::APicturePuzzle()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BackgroundSprite = CreateDefaultSubobject<UPaperSpriteComponent>("BackgroundSprite");
	BackgroundSprite->SetupAttachment(RootComponent);

	ImageTileStartingSprite = CreateDefaultSubobject<UPaperSprite>("StartingSprite");

}

// Called when the game starts or when spawned
void APicturePuzzle::BeginPlay()
{
	Super::BeginPlay();

	if(ImageTileStartingSprite)
	{
		std::string test = std::string(TCHAR_TO_UTF8(*ImageTileStartingSprite->GetPathName()));
		std::size_t found = test.find_last_of("/");
		std::string spriteName = test.substr(found+1,test.length()-1);
		std::string spriteStart = test.substr(0,found+1);
		
		if(puzzleTile)
		{
			UWorld* world = GetWorld();
			if(world)
			{
				FActorSpawnParameters spawnParams;
				spawnParams.Owner = this;
				const FRotator rotator;

				int fileCountDown = 15;
				
				for(int i=0; i<4; i++)
				{
					std::vector<APuzzleTile*> Row; 
					for(int j=0; j<4; j++)
					{
					
						const FVector spawnLocation = this->GetActorLocation() + FVector(i*-15.f + 23,j*15.f - 23,.5f);
						Row.push_back(world->SpawnActor<APuzzleTile>(puzzleTile,spawnLocation,rotator,spawnParams));
						Row.back()->GridPosition = FVector2D(i,j);
						Row.back()->GridDestination = FVector2D(i,j); 


						//Get tile sprite
						std::string tileSpriteName = ReplaceAll(spriteName,std::string("0"),std::string(std::to_string(fileCountDown)));
						std::string combined = spriteStart + tileSpriteName; 
						Row.back()->TileImageSprite->SetSprite( Cast<UPaperSprite>(StaticLoadObject(UPaperSprite::StaticClass(), NULL, *FString(combined.c_str()))));
						
						//	UE_LOG(LogTemp,Warning,TEXT("Position %s"),*Row.back()->GridPosition.ToString());


						

						
						if(i == 3 && j ==3)
						{
							Row.back()->MakeEmptyTile(); 
						}
						
						 fileCountDown --; 
					}
					TileVector.push_back(Row);
				}

				//Generate empty tiles
				for(int i=0; i<NumberOfEmptyTiles;i++)
				{
					FVector2D position = FVector2D(FMath::RandRange(0,3),FMath::RandRange(0,3));
					TileVector.at(position.X).at(position.Y)->MakeEmptyTile(); 		
				}
				
				Shuffle_Tiles();

				//Only  choose non empty tile
				bool foundTile = false;
				while(foundTile ==  false)
				{
					FVector2D position = FVector2D(FMath::RandRange(0,3),FMath::RandRange(0,3));
					if(!(TileVector.at(position.X).at(position.Y)->IsEmptyTile)){
						TileVector.at(position.X).at(position.Y)->Highlight();
						foundTile = true;
						CurrentGridPosition = position; 
					}
				}
			}
		}
	}
	
}

// Called every frame
void APicturePuzzle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APicturePuzzle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction(TEXT("PuzzleUp"),IE_Pressed,this,&APicturePuzzle::GridInputUp);
	PlayerInputComponent->BindAction(TEXT("PuzzleRight"),IE_Pressed,this,&APicturePuzzle::GridInputRight);
	PlayerInputComponent->BindAction(TEXT("PuzzleLeft"),IE_Pressed,this,&APicturePuzzle::GridInputLeft);
	PlayerInputComponent->BindAction(TEXT("PuzzleDown"),IE_Pressed,this,&APicturePuzzle::GridInputDown);
	PlayerInputComponent->BindAction(TEXT("SelectionMode"),IE_Pressed,this,&APicturePuzzle::ChangeSelection);

}

bool APicturePuzzle::IsPuzzleComplete()
{
	bool complete = true; 
	for(int i =0; i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			
				if(!TileVector.at(i).at(j)->CheckInPlace()){complete = false;}
				UE_LOG(LogTemp, Warning, TEXT("Tile in place? %hs"),TileVector.at(i).at(j)->CheckInPlace()? "true" : "false" );

			}}
	return complete; 
}

void APicturePuzzle::Swap_Tile_Positions(FVector2D position1, FVector2D position2)
{
	const FVector EmptyPosition = TileVector.at(position1.X).at(position1.Y)->GetActorLocation();
	const FVector CurrentPosition = TileVector.at(position2.X).at(position2.Y)->GetActorLocation();
			
	TileVector.at(position2.X).at(position2.Y)->GridPosition = position1;
	TileVector.at(position2.X).at(position2.Y)->SetActorLocation(EmptyPosition);

	TileVector.at(position1.X).at(position1.Y)->GridPosition = position2;
	TileVector.at(position1.X).at(position1.Y)->SetActorLocation(CurrentPosition);
			
	std::swap(TileVector[position2.X][position2.Y],TileVector[position1.X][position1.Y]);
}

void APicturePuzzle::Shuffle_Tiles()
{
	bool sufficientlyShuffled = false;

	for(int i=0;i<1;i++) 
	{
		const FVector2D FirstPosition = FVector2D(FMath::RandRange(0,3),FMath::RandRange(0,3));
		const FVector2D SecondPosition = FVector2D(FMath::RandRange(0,3),FMath::RandRange(0,3)); 
		Swap_Tile_Positions(FirstPosition,SecondPosition); 
	}
}

void APicturePuzzle::GridInputUp()
{
	UE_LOG(LogTemp,Warning,TEXT("Up Pressed"));
	if(selectMode)
	{
		SelectionMove(FVector2D(1.f,0.f));
	}
	else if(highlightMode)
	{
		HighlightMove(FVector2D(1.f,0.f));
	}
}

void APicturePuzzle::GridInputRight()
{
	UE_LOG(LogTemp,Warning,TEXT("Right Pressed"));
	if(selectMode)
	{
		SelectionMove(FVector2D(0.f,-1.f));
	}
	else if(highlightMode)
	{
		HighlightMove(FVector2D(0.f,-1.f));
	}
}

void APicturePuzzle::GridInputLeft()
{
	UE_LOG(LogTemp,Warning,TEXT("Left Pressed"));
	if(selectMode)
	{
		SelectionMove(FVector2D(0.f,1.f));
	}
	else if(highlightMode)
	{
		HighlightMove(FVector2D(0.f,1.f));
	}
}

void APicturePuzzle::GridInputDown()
{
	UE_LOG(LogTemp,Warning,TEXT("Down Pressed"));
	if(selectMode)
	{
		SelectionMove(FVector2D(-1.f,0.f));
	}
	else if(highlightMode)
	{
		HighlightMove(FVector2D(-1.f,0.f));
	}
}

void APicturePuzzle::SelectionMove(FVector2D Direction)
{
	const FVector2D nextPosition = CurrentGridPosition+Direction;
	UE_LOG(LogTemp,Warning,TEXT("New Direction %s"),*nextPosition.ToString());

	if(!(nextPosition.X <0 || nextPosition.Y <0 ||nextPosition.X >3|| nextPosition.Y >3))
	{
		UE_LOG(LogTemp,Warning,TEXT("In Bounds"));
		if(TileVector.at(nextPosition.X).at(nextPosition.Y)->IsEmptyTile)
		{
			Swap_Tile_Positions(nextPosition,CurrentGridPosition);
			
			CurrentGridPosition = nextPosition;
			IsPuzzleComplete(); 

		}
		else{UE_LOG(LogTemp,Warning,TEXT("Tile Not Empty"));}
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("Out of Bounds"));
	}
}

void APicturePuzzle::HighlightMove(FVector2D Direction)
{
	const FVector2D nextPosition = CurrentGridPosition+Direction;
	UE_LOG(LogTemp,Warning,TEXT("New Direction %s"),*nextPosition.ToString());

	if(!(nextPosition.X <0 || nextPosition.Y <0 ||nextPosition.X >3|| nextPosition.Y >3))
	{
		UE_LOG(LogTemp,Warning,TEXT("In Bounds"));
		
		if(TileVector.at(nextPosition.X).at(nextPosition.Y)->IsEmptyTile)
		{
			UE_LOG(LogTemp,Warning,TEXT("Empty Tile"));
			FVector2D TileAfter = nextPosition + Direction;
			
			if(!(TileAfter.X <0 || TileAfter.Y <0 ||TileAfter.X >3|| TileAfter.Y >3))
			{
				TileVector.at(CurrentGridPosition.X).at(CurrentGridPosition.Y)->ReturnToDefault();
				TileVector.at(TileAfter.X).at(TileAfter.Y)->Highlight();
				CurrentGridPosition = TileAfter;
			}
		}
		
		else{
		TileVector.at(CurrentGridPosition.X).at(CurrentGridPosition.Y)->ReturnToDefault();
		TileVector.at(nextPosition.X).at(nextPosition.Y)->Highlight();
		CurrentGridPosition = nextPosition;
			
	}}
	else{UE_LOG(LogTemp,Warning,TEXT("Out of Bounds"));}
}

void APicturePuzzle::ChangeSelection()
{
	if(highlightMode)
	{
		highlightMode = false;
		selectMode = true;

		TileVector.at(CurrentGridPosition.X).at(CurrentGridPosition.Y)->Select();

	}
	else if(selectMode)
	{
		highlightMode = true;
		selectMode = false;
		TileVector.at(CurrentGridPosition.X).at(CurrentGridPosition.Y)->Highlight();

	}
}
