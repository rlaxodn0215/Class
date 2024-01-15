// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CProperty01.generated.h"

UCLASS()
class CPP1211_API ACProperty01 : public AActor
{
	GENERATED_BODY()
	
public:	
	ACProperty01();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;



private:
	UPROPERTY(EditAnywhere) // 변수를 추가할건데 vc나 에디터 어디서든 수정할 수 있게 하자
		int A = 10; 
	UPROPERTY(EditInstanceOnly) // 플레이 창에서 보임 (블루프린트 수정창에서는 안보임)
		int B = 20; 
	UPROPERTY(EditDefaultsOnly) // 블루프린트창에서 보임 (플레이 에서는 안보임) 
		int C;
protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		int D = 40;


};
