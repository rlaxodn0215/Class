// Fill out your copyright notice in the Description page of Project Settings.


#include "CActorOverlap.h"
#include "Global.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"


// Sets default values
ACActorOverlap::ACActorOverlap()
{
	CHelpers::CreateComponent<USceneComponent>(this, &Scene, "Scene"); //UScene컴포넌트 생성과 동시에 Scene에 저장
	CHelpers::CreateComponent<UBoxComponent>(this, &Box, "Box", Scene);
	CHelpers::CreateComponent<UTextRenderComponent>(this, &Text, "Text", Scene);

	Box->SetRelativeScale3D(FVector(3));
	Box->bHiddenInGame = false;

	Text->SetRelativeLocation(FVector(0, 0, 100));
	Text->SetRelativeRotation(FRotator(0, 90, 0));
	Text->SetRelativeScale3D(FVector(2));
	Text->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
	Text->TextRenderColor = FColor::Red;
	Text->Text = FText::FromString(GetName());

}

void ACActorOverlap::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &ACActorOverlap::ActorBeginOverlap);
	OnActorEndOverlap.AddDynamic(this, &ACActorOverlap::ActorEndOverlap);

}

void ACActorOverlap::ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	FString str = "";
	str.Append(__FUNCTION__);
	str.Append(" : ");
	str.Append(OtherActor->GetName());
	CLog::Log(str);
}

void ACActorOverlap::ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	FString str = "";
	str.Append(__FUNCTION__);
	str.Append(" : ");
	str.Append(OtherActor->GetName());
	CLog::Log(str);
}

