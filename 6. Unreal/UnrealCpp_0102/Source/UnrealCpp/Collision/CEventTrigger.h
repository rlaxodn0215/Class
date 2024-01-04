#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CEventTrigger.generated.h"

// << �� ������ ����
UCLASS()
class UNREALCPP_API ACEventTrigger : public AActor
{
	GENERATED_BODY()
// >> �� ���Ŀ� ����

public:
	// event�� class ���ο� ������
	DECLARE_EVENT_OneParam(ACEventTrigger, FEventTrigger, int32)

	
public:	
	ACEventTrigger();

protected:
	virtual void BeginPlay() override;


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
