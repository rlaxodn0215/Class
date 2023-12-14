#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CSpawnActor.generated.h"

// StaticMesh'/Game/03_Meshs/Mesh_Cube.Mesh_Cube'

UCLASS()
class TUTORIAL_API ACSpawnActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACSpawnActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* Mesh;

private:
	UFUNCTION()
		void ChangeColor();

private:
	class UMaterialInstanceDynamic* Material;

};
