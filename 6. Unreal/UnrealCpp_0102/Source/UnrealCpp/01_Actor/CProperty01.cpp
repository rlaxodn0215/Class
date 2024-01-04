#include "CProperty01.h"


// Awake
ACProperty01::ACProperty01()
{
	PrimaryActorTick.bCanEverTick = true;

	C = 44;
}

// Start
void ACProperty01::BeginPlay() 
{
	Super::BeginPlay();
	
	/*FString str;
	str.Append("A: ");
	str.Append(FString::FromInt(A));
	str.Append(", B: ");
	str.Append(FString::FromInt(B));
	str.Append(", C: ");
	str.Append(FString::FromInt(C));
	str.Append(", D: ");
	str.Append(FString::FromInt(D));

	GLog->Log(str);*/
}

// Update
void ACProperty01::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);

}

