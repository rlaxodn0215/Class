
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CEventTrigger.generated.h"

UCLASS()
class CPP1211_API ACEventTrigger : public AActor
{
	GENERATED_BODY()
	
public:
	//�̺�Ʈ ������ ���ʿ� ���� �׸��� GENERATED_BODYclass ���̿� �� ���� �ʱ� �̺�Ʈ�� ���� ���� ����.
	DECLARE_EVENT_OneParam(ACEventTrigger, FEventTrigger, int32)

public:	
	ACEventTrigger();

protected:
	virtual void BeginPlay() override;

public:	


private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Scene;
	UPROPERTY(VisibleDefaultsOnly)
		class UBoxComponent* Box;
	UPROPERTY(VisibleDefaultsOnly)
		class UTextRenderComponent* Text;

private:
	UFUNCTION()
		void ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

public:
	FEventTrigger OnEventTrigger;

};
