
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CEventTrigger.generated.h"

UCLASS()
class CPP1211_API ACEventTrigger : public AActor
{
	GENERATED_BODY()
	
public:
	//이벤트 선언은 안쪽에 선언 그리고 GENERATED_BODYclass 사이에 뭐 넣지 않기 이벤트는 리턴 값이 없다.
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
