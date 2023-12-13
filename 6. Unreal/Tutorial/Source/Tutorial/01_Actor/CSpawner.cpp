// Fill out your copyright notice in the Description page of Project Settings.


#include "CSpawner.h"
#include "Global.h"
#include "CSpawnActor.h"

// Sets default values
ACSpawner::ACSpawner()
{


}

// Called when the game starts or when spawned
void ACSpawner::BeginPlay()
{
	Super::BeginPlay();

	for (int32 i = 0; i < 3; i++)
	{
		FTransform trasform;
		FVector location = GetActorLocation();
		spawnActors[i] = GetWorld()->SpawnActor<ACSpawnActor>(spawnClass[i], trasform);

		spawnActors[i]->SetActorLocation(FVector(location.X + i * 400, location.Y, location.Z));

	}
	
}

