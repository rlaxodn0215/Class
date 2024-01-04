
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CCylinder.generated.h"

UCLASS()
class UNREALCPP_API ACCylinder : public AActor
{
	GENERATED_BODY()
	
public:	
	ACCylinder();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Scene;
	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* Mesh;
	UPROPERTY(VisibleDefaultsOnly)
		class UTextRenderComponent* Text;

};
