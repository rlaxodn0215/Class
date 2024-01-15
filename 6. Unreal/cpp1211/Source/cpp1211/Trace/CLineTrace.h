#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CLineTrace.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FTraceResult, class AActor*, InActor, FLinearColor, InColor);


UCLASS()
class CPP1211_API ACLineTrace : public AActor
{
	GENERATED_BODY()
	
public:	
	ACLineTrace();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Scene;
	UPROPERTY(VisibleDefaultsOnly)
		class UTextRenderComponent* Text;
private:
	TArray<class ACCylinder*> Cylinders;

public:
	UPROPERTY(BlueprintAssignable)
		FTraceResult OnTraceResult;
	UFUNCTION(BlueprintCallable)
		void RestorColor(class ACPlayer* InPlayer);

private:
	UFUNCTION()
		void StartJump(class AActor* InActor, FLinearColor InColor);
};
