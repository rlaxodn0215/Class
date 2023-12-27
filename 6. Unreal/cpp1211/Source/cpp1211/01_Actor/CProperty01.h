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
	UPROPERTY(EditAnywhere) // ������ �߰��Ұǵ� vc�� ������ ��𼭵� ������ �� �ְ� ����
		int A = 10; 
	UPROPERTY(EditInstanceOnly) // �÷��� â���� ���� (�������Ʈ ����â������ �Ⱥ���)
		int B = 20; 
	UPROPERTY(EditDefaultsOnly) // �������Ʈâ���� ���� (�÷��� ������ �Ⱥ���) 
		int C;
protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		int D = 40;


};
