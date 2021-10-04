// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "PMCube.generated.h"

UCLASS()
class PROCGENTEST_API APMCube : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APMCube();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MeshParameters")
		FVector CubeRadius = FVector(100.f);

protected:

	UPROPERTY(VisibleAnywhere)
		USceneComponent* ThisScene;

	UPROPERTY(VisibleAnywhere)
		UProceduralMeshComponent* ProceduralMesh;

	virtual void PostActorCreated() override;

	virtual void PostLoad() override;

	void GenerateMesh();

private:

	TArray<FVector> Vertices;
	TArray<int32> Triangles;
	TArray<FVector> Normals;
	TArray<FProcMeshTangent> Tangents;
	TArray<FVector2D> UVs;
	TArray<FLinearColor> Colors;

	void AddTriangleMesh(FVector TopRight, FVector BottomRight, FVector BottomLeft, int32& TriIndex, FProcMeshTangent Tangent);
	void AddQuadMesh(FVector TopRight, FVector BottomRight, FVector TopLeft, FVector BottomLeft, int32& TriIndex, FProcMeshTangent Tangent);

};
