// Fill out your copyright notice in the Description page of Project Settings.


#include "ProceduralRoom.h"
#include "Components/StaticMeshComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values
AProceduralRoom::AProceduralRoom()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Floor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FloorComponent"));
	SetRootComponent(Floor);

	GridHeight = 1.f;
	RoomLength = 1000.f;
	RoomWidth = 1000.f;
	GridSizeX = 5;
	GridSizeY = 5;
	SquareWidth = 200.f;

	TopLeft = FVector(0.f);
	BottomRight = FVector(1000.f, 1000.f, 0.f);

	Radius = 25;
}

// Called when the game starts or when spawned
void AProceduralRoom::BeginPlay()
{
	Super::BeginPlay();

	//CreateGrid();
	PlacePointsOnGrid();
}

// Called every frame
void AProceduralRoom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProceduralRoom::SpawnItem(UClass* ItemToSpawn)
{
	float XCoordinate = FMath::FRandRange(-500.f, 500.f);
	float YCoordinate = FMath::FRandRange(-500.f, 500.f);

	float Yaw = FMath::FRandRange(0.f, 360.f);

	FVector Location(XCoordinate, YCoordinate, 0.f);
	FRotator Rotation(0.f, Yaw, 0.f);

	//Spawn the actor in game world
	GetWorld()->SpawnActor<AActor>(ItemToSpawn, Location, Rotation);
	UE_LOG(LogTemp, Warning, TEXT("Chair spawned"));
	GetWorld()->SpawnActor<AActor>(ItemToSpawn, FVector(0.f), FRotator(0.f));
}

void AProceduralRoom::CreateGrid()
{
	for(int32 i = 0; i < GridSizeX+1; i++)
	{
		FVector Start = TopLeft + FVector(i * SquareWidth, 0.f, GridHeight);
		FVector End = Start + FVector(0.f, RoomLength, GridHeight);
		DrawDebugLine(GetWorld(), Start, End, FColor::Blue, true);
	}

	for (int32 i = 0; i < GridSizeX + 1; i++)
	{
		FVector Start = TopLeft + FVector(0.f, i * SquareWidth, GridHeight);
		FVector End = Start + FVector(RoomWidth, 0.f, GridHeight);
		DrawDebugLine(GetWorld(), Start, End, FColor::Blue, true);
	}
}

FVector AProceduralRoom::GetRandomPointInSquare(const FVector& UpperLeft, const FVector& LowerRight)
{
	float RandomX = FMath::FRandRange(UpperLeft.X, LowerRight.X);
	float RandomY = FMath::FRandRange(UpperLeft.Y, LowerRight.Y);

	return(FVector(RandomX, RandomY, 0.f));
}

void AProceduralRoom::PlacePointsOnGrid()
{
	for(int32 i=0;i<GridSizeX;i++)
	{
		for(int32 j=0;j<GridSizeY;j++)
		{
			FVector UpperLeft(i * SquareWidth + Radius, j * SquareWidth + Radius, GridHeight);
			FVector LowerRight(i * SquareWidth + SquareWidth + -Radius, j * SquareWidth + SquareWidth + -Radius, GridHeight);
			FVector RandomPointInSquare = GetRandomPointInSquare(UpperLeft, LowerRight);

			//DrawDebugPoint(GetWorld(), RandomPointInSquare, 5.f, FColor::Red, true);
			//DrawDebugCircle(GetWorld(), RandomPointInSquare, Radius, 48, FColor::Red, true, -1.f, 0, 2.5f, FVector(0.f, 1.f, 0.f), FVector(1.f, 0.f, 0.f), true);

			float RandomYaw = FMath::FRandRange(0.f, 360.f);
			GetWorld()->SpawnActor<AActor>(ChairClass, RandomPointInSquare, FRotator(0.f,RandomYaw,0.f));
		}
	}
}

