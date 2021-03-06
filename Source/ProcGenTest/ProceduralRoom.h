// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralRoom.generated.h"

UCLASS()
class PROCGENTEST_API AProceduralRoom : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProceduralRoom();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	//NOTE: meta = (AllowPrivateAccess = "true") makes this work like [SerializedField] private variable in Unity, when in private or protected section.
	/** Mesh Component for the floor */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Room", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Floor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Room", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> ChairClass;

	void SpawnItem(UClass* ItemToSpawn);

	float GridHeight;
	float SquareWidth;
	float RoomLength;
	float RoomWidth;

	FVector TopLeft;
	FVector BottomRight;
	int32 GridSizeX;
	int32 GridSizeY;

	float Radius;

	void CreateGrid();

	FVector GetRandomPointInSquare(const FVector& UpperLeft, const FVector& LowerRight);

	void PlacePointsOnGrid();
};
