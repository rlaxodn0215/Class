// Fill out your copyright notice in the Description page of Project Settings.


#include "CSpawnActor.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ACSpawnActor::ACSpawnActor()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = Mesh;

	ConstructorHelpers::FObjectFinder<UStaticMesh>
		mesh(L"StaticMesh'/Game/03_Meshs/Mesh_Cube.Mesh_Cube'");

	if (mesh.Succeeded())
	{
		Mesh->SetStaticMesh(mesh.Object);
	}
}

// Called when the game starts or when spawned
void ACSpawnActor::BeginPlay()
{
	Super::BeginPlay();
	
}


