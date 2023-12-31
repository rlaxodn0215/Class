#include "CCylinder.h"
#include "Global.h"
#include "Components/TextRenderComponent.h"
#include "Components/StaticMeshComponent.h"

ACCylinder::ACCylinder()
{
	CHelpers::CreateComponent<USceneComponent>(this, &Scene, "Scene");
	CHelpers::CreateComponent<UTextRenderComponent>(this, &Text, "Text", Scene);
	CHelpers::CreateComponent<UStaticMeshComponent>(this, &Mesh, "Mesh", Scene);

	Text->SetRelativeLocation(FVector(0, 0, 140));
	Text->SetRelativeRotation(FRotator(0, 90, 0));
	Text->SetRelativeScale3D(FVector(2));
	Text->TextRenderColor = FColor::Red;
	Text->HorizontalAlignment = EHorizontalAlignment::EHTA_Center;
	Text->Text = FText::FromString(GetName());

	UStaticMesh* mesh;
	CHelpers::GetAsset<UStaticMesh>(&mesh,
		"StaticMesh'/Game/Meshes/Mesh_Cylinder.Mesh_Cylinder'");

	Mesh->SetStaticMesh(mesh);
	//Mesh->SetRelativeScale
}

void ACCylinder::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACCylinder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

