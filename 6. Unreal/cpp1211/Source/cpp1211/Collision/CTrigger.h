#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CTrigger.generated.h"

DECLARE_DELEGATE(FBoxLightBeginOverlap);
DECLARE_DELEGATE(FBoxLightEndOverlap);
DECLARE_DELEGATE_RetVal_OneParam(FString, FBoxLightRandomBeingOverlap, FLinearColor);

UCLASS()
class CPP1211_API ACTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	ACTrigger();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Scene; // root
	UPROPERTY(VisibleDefaultsOnly)
		class UBoxComponent* Box; // �浹ü
	UPROPERTY(VisibleDefaultsOnly)
		class UTextRenderComponent* Text;

private:
	UFUNCTION()
		void ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);
	UFUNCTION()
		void ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor);

public:
	FBoxLightBeginOverlap		OnBoxLightBeginOverlap;
	FBoxLightEndOverlap			OnBoxLightEndOverlap;
	FBoxLightRandomBeingOverlap OnBoxLightRandomBeingOverlap;
};
