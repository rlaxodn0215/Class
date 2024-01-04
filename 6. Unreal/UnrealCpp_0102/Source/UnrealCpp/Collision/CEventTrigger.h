#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CEventTrigger.generated.h"

// << 이 이전에 쓰기
UCLASS()
class UNREALCPP_API ACEventTrigger : public AActor
{
	GENERATED_BODY()
// >> 이 이후에 쓰기

public:
	// event는 class 내부에 선언함
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
