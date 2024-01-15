#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CExplosionTrigger.generated.h"

UCLASS()
class CPP1211_API ACExplosionTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	ACExplosionTrigger();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Scene;
	UPROPERTY(VisibleDefaultsOnly)
		class UBoxComponent* Box;
	UPROPERTY(VisibleDefaultsOnly)
		class UTextRenderComponent* Text;

};
