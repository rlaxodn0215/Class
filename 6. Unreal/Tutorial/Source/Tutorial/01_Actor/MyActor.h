// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

UCLASS()
class TUTORIAL_API AMyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


private:
	UPROPERTY(EditAnywhere)
		int A = 10;
	UPROPERTY(EditInstanceOnly)		// ������ �󿡸� ����
		int B = 20;
	UPROPERTY(EditDefaultsOnly)		// ��� ����Ʈ �ȿ����� ����
		int C;

protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		int D = 40;

};
