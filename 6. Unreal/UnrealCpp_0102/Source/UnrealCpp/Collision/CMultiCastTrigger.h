#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CMultiCastTrigger.generated.h"

// delegate�� class �ܺο� ������
DECLARE_MULTICAST_DELEGATE_TwoParams(FMultiLightBeginOverlap, int32, FLinearColor);

UCLASS()
class UNREALCPP_API ACMultiCastTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	ACMultiCastTrigger();

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
	UFUNCTION()
		void ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor);

public:
	FMultiLightBeginOverlap OnMultiLightBeginOverlap;
};
