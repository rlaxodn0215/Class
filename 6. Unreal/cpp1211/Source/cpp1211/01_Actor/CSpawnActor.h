#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CSpawnActor.generated.h"

UCLASS()
class CPP1211_API ACSpawnActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ACSpawnActor();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* Mesh;

private:
	UFUNCTION()
		void ChangeColor();

private:
	class UMaterialInstanceDynamic* Material; // Dynamic이 들어가면 동적으로 생성한다는 뜻인데 실제로는 저장되어있는걸 불러온다고 생각하면 됨

};
