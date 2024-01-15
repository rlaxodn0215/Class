#include "CLineTrace.h"
#include "Global.h"
#include "Components/TextRenderComponent.h"
#include "CCylinder.h"
#include "CPlayer.h"

ACLineTrace::ACLineTrace()
{
 	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateComponent<USceneComponent>(this, &Scene, "Scene");
	CHelpers::CreateComponent<UTextRenderComponent>(this, &Text, "Text", Scene);

	Text->SetRelativeLocation(FVector(0, 0, 140));
	Text->SetRelativeRotation(FRotator(0, 90, 0));
	Text->SetRelativeScale3D(FVector(2));
	Text->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
	Text->TextRenderColor = FColor::Red;
	Text->Text = FText::FromString(GetName());

}

void ACLineTrace::BeginPlay()
{
	Super::BeginPlay();
	
	CHelpers::FindActors<ACCylinder>(GetWorld(), Cylinders); //맵의 Cylinders를 찾아서 배열에 저장

	OnTraceResult.AddDynamic(this, &ACLineTrace::StartJump);
}

void ACLineTrace::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector start = Cylinders[0]->GetActorLocation();
	FVector end = Cylinders[1]->GetActorLocation();
	start.Z -= 50;
	end.Z -= 50;
	DrawDebugLine(GetWorld(), start, end, FColor::Yellow,false);

	start.Z += 10;
	end.Z += 10;
	TArray<AActor*> ignoreActors; //무시할 엑터들
	ignoreActors.Add(Cylinders[0]); //실린더 기둥 두개가 무시되도록
	ignoreActors.Add(Cylinders[1]);

	FHitResult hitResult;
	if (UKismetSystemLibrary::LineTraceSingleByProfile(GetWorld(), start, end, "Pawn", false, //green선 생성해서 충돌시 Red로 
		ignoreActors, EDrawDebugTrace::ForOneFrame, hitResult, true, FLinearColor::Green,
		FLinearColor::Red))
	{
		//CLog::Log(hitResult.GetActor()->GetName());
		if (OnTraceResult.IsBound())
		{
			FLinearColor color;
			color.R = UKismetMathLibrary::RandomFloatInRange(0, 1);
			color.G = UKismetMathLibrary::RandomFloatInRange(0, 1);
			color.B = UKismetMathLibrary::RandomFloatInRange(0, 1);
			color.A = 1.0f;

			OnTraceResult.Broadcast(hitResult.GetActor(), color);
		}
	}
}

void ACLineTrace::RestorColor(ACPlayer* InPlayer)
{
	InPlayer->ChangeColor(FLinearColor(1, 1, 1));
}

void ACLineTrace::StartJump(AActor* InActor, FLinearColor InColor)
{
	ACPlayer* player = Cast<ACPlayer>(InActor);
	CheckNull(player);

	player->Jump();
}

