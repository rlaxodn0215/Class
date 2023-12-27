
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CSpawnLight.generated.h"

UCLASS()
class CPP1211_API ACSpawnLight : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACSpawnLight();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Scene; // root
	UPROPERTY(VisibleDefaultsOnly)
		class UTextRenderComponent* Text;
	UPROPERTY(VisibleDefaultsOnly)
		class USpotLightComponent* SpotLights[3];

private:
	UFUNCTION()
		void OnLightColor(int32 InIndex, FLinearColor InColor);

};
