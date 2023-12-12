// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	C = 35;
	D = 44;
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();

	FString str;

	str.Append("A: ");
	str.Append(FString::FromInt(A));
	str.Append(", B: ");
	str.Append(FString::FromInt(B));
	str.Append(", C: ");
	str.Append(FString::FromInt(C));
	str.Append(", D: ");
	str.Append(FString::FromInt(D));

	GLog->Log(str);

	
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

