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
	//str.Append("A : "); // str += "A: "; ��������
	//str.Append(FString::FromInt(A)); // A��� ������ ��Ʈ������ ��ȯ
	//str.Append(", B: ");
	//str.Append(FString::FromInt(B)); // A��� ������ ��Ʈ������ ��ȯ
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
