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
	class UMaterialInstanceDynamic* Material;// Dynamic�� ���� �������� �����Ѵٴ� ���ε� �����δ� ����Ǿ��ִ°� �ҷ��´ٰ� �����ϸ� ��


};
