// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicShapes.h"
#include "Engine.h"

// Sets default values
ABasicShapes::ABasicShapes()
{
	ThisScene = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = ThisScene;

	ProceduralMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("GeneratedMesh"));
	ProceduralMesh->SetupAttachment(RootComponent);
}

void ABasicShapes::PostActorCreated()
{
	Super::PostActorCreated();
	GenerateMesh();
}

void ABasicShapes::PostLoad()
{
	Super::PostLoad();
	GenerateMesh();
}

void ABasicShapes::GenerateMesh()
{
	Vertices.Reset();
	Triangles.Reset();
	Normals.Reset();
	Tangents.Reset();
	UVs.Reset();
	Colors.Reset();

	int32 TriangleIndexCount = 0;
	FVector DefinedShape[4];
	FProcMeshTangent TangentSetup;

	DefinedShape[0] = FVector(CubeRadius.X, CubeRadius.Y, CubeRadius.Z);			//Forward TopRight
	DefinedShape[1] = FVector(CubeRadius.X, CubeRadius.Y, -CubeRadius.Z);		//Forward BottomLeft
	DefinedShape[2] = FVector(CubeRadius.X, -CubeRadius.Y, CubeRadius.Z);		//Forward TopLeft
	DefinedShape[3] = FVector(CubeRadius.X, -CubeRadius.Y, -CubeRadius.Z);	//Forward BottomRight

	TangentSetup = FProcMeshTangent(0.f, 1.f, 0.f);
	AddTriangleMesh(DefinedShape[0], DefinedShape[1], DefinedShape[2], TriangleIndexCount, TangentSetup);
	AddQuadMesh(DefinedShape[0], DefinedShape[1], DefinedShape[2], DefinedShape[3], TriangleIndexCount, TangentSetup);

	ProceduralMesh->CreateMeshSection_LinearColor(0, Vertices, Triangles, Normals, UVs, Colors, Tangents, true);

}


void ABasicShapes::AddTriangleMesh(FVector TopRight, FVector BottomRight, FVector BottomLeft, int32& TriIndex, FProcMeshTangent Tangent)
{
	int32 Point1 = TriIndex++;
	int32 Point2 = TriIndex++;
	int32 Point3 = TriIndex++;

	Vertices.Add(TopRight);
	Vertices.Add(BottomRight);
	Vertices.Add(BottomLeft);

	Triangles.Add(Point1);
	Triangles.Add(Point2);
	Triangles.Add(Point3);

	FVector Normal = FVector::CrossProduct(TopRight, BottomRight).GetSafeNormal();
	for(int32 i = 0; i < 3; i++)
	{
		Normals.Add(Normal);
		Tangents.Add(Tangent);
		Colors.Add(FLinearColor::Green);
	}
	UVs.Add(FVector2D(0.f, 1.f));	//TopLeft
	UVs.Add(FVector2D(0.f, 0.f));	//BotomRight
	UVs.Add(FVector2D(1.f, 0.f));	//BottomLeft
}

void ABasicShapes::AddQuadMesh(FVector TopRight, FVector BottomRight, FVector TopLeft, FVector BottomLeft, int32& TriIndex, FProcMeshTangent Tangent)
{
	int32 Point1 = TriIndex++;
	int32 Point2 = TriIndex++;
	int32 Point3 = TriIndex++;
	int32 Point4 = TriIndex++;

	Vertices.Add(TopRight);
	Vertices.Add(BottomRight);
	Vertices.Add(TopLeft);
	Vertices.Add(BottomLeft);

	Triangles.Add(Point1);
	Triangles.Add(Point2);
	Triangles.Add(Point3);

	Triangles.Add(Point4);
	Triangles.Add(Point3);
	Triangles.Add(Point2);

	FVector Normal = FVector::CrossProduct(TopLeft - BottomRight, TopLeft - TopRight).GetSafeNormal();
	for (int32 i = 0; i < 4; i++)
	{
		Normals.Add(Normal);
		Tangents.Add(Tangent);
		Colors.Add(FLinearColor::Green);
	}
	UVs.Add(FVector2D(0.f, 1.f));	//TopLeft
	UVs.Add(FVector2D(0.f, 0.f));	//BottomRight
	UVs.Add(FVector2D(1.f, 1.f));	//TopRight
	UVs.Add(FVector2D(1.f, 0.f));	//BottomLeft

}


