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
   //��������Ʈ ���� ��ü�� ȣ��
   UFUNCTION()
      void ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);
   UFUNCTION()
      void ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor);

protected:
   UFUNCTION(BlueprintImplementableEvent)
      void ChangeColorRed();
   UFUNCTION(BlueprintNativeEvent) // �ش��Լ� ���� �� _Implementation�� ���� �Լ��� �ڵ����� 
      void ChangeColorWhite();
      void ChangeColorWhite_Implementation();


};