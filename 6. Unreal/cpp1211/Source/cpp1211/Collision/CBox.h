#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CBox.generated.h"

UCLASS()
class CPP1211_API ACBox : public AActor
{
	GENERATED_BODY()
	
public:	
	ACBox();

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Scene; // root
	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* Mesh[3];
	UPROPERTY(VisibleDefaultsOnly)
		class UTextRenderComponent* Text;

private:
	UFUNCTION()
		void OnPhysics(int32 InIndex, FLinearColor InColor);
private:
	UMaterialInstanceDynamic* Materials[3];
	FVector				 WorldLocation[3];

protected:
	virtual void BeginPlay() override;
};
