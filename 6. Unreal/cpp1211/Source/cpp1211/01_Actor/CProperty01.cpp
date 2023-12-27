#include "CProperty01.h"

ACProperty01::ACProperty01()
{
	PrimaryActorTick.bCanEverTick = true;
	C = 55;
}

void ACProperty01::BeginPlay()
{
	Super::BeginPlay();
	
	//FString str;
	//str.Append("A : "); // str += "A: "; 같은거임
	//str.Append(FString::FromInt(A)); // A라는 변수를 스트링으로 변환
	//str.Append(", B: ");
	//str.Append(FString::FromInt(B)); // A라는 변수를 스트링으로 변환
	//str.Append(", C: ");
	//str.Append(FString::FromInt(C)); 
	//str.Append(", D: ");
	//str.Append(FString::FromInt(D)); 

	//GLog->Log(str);
}

// Called every frame
void ACProperty01::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
