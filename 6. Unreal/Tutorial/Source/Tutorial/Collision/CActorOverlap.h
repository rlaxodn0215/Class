#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CActorOverlap.generated.h"

UCLASS()
class TUTORIAL_API ACActorOverlap : public AActor
{
	GENERATED_BODY()
	
public:	
	ACActorOverlap();

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
		void ActorBeginOverlap(AActor* OverlappedACtor, AActor* OtherActor);
	UFUNCTION()
		void ActorEndOverlap(AActor* OverlappedACtor, AActor* OtherActor);
};
