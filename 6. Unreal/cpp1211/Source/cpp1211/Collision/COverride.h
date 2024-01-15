#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "COverride.generated.h"

UCLASS()
class CPP1211_API ACOverride : public AActor
{
   GENERATED_BODY()
   
public:   
   ACOverride();

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
   //델리데이트 여서 자체로 호출
   UFUNCTION()
      void ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);
   UFUNCTION()
      void ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor);

protected:
   UFUNCTION(BlueprintImplementableEvent)
      void ChangeColorRed();
   UFUNCTION(BlueprintNativeEvent) // 해당함수 실행 시 _Implementation가 붙은 함수를 자동실행 
      void ChangeColorWhite();
      void ChangeColorWhite_Implementation();


};