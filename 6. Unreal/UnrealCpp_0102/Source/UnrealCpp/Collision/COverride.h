#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "COverride.generated.h"

UCLASS()
class UNREALCPP_API ACOverride : public AActor
{
	GENERATED_BODY()
	
public:	
	ACOverride();

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
	
protected:
	UFUNCTION(BlueprintImplementableEvent)
		void ChangeColorRed();
	UFUNCTION(BlueprintNativeEvent)
		void ChangeColorWhite();
		void ChangeColorWhite_Implementation();

};
