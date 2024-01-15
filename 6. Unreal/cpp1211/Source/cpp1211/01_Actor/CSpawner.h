#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CSpawner.generated.h"

UCLASS()
class CPP1211_API ACSpawner : public AActor
{
	GENERATED_BODY()
private:
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class ACSpawnActor> spawnClass[3];

	class ACSpawnActor* spawnActors[3];


public:	
	ACSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

};
