// Fill out your copyright notice in the Description page of Project Settings.


#include "CSpawnActor.h"
#include "Global.h"
//#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
ACSpawnActor::ACSpawnActor()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = Mesh;

	UStaticMesh* mesh;
	CHelpers::GetAsset<UStaticMesh>(&mesh, "StaticMesh'/Game/03_Meshs/Mesh_Cube.Mesh_Cube'");
	Mesh->SetStaticMesh(mesh);

	//ConstructorHelpers::FObjectFinder<UStaticMesh>
	//	mesh(L"StaticMesh'/Game/03_Meshs/Mesh_Cube.Mesh_Cube'");

	//if (mesh.Succeeded())
	//{
	//	Mesh->SetStaticMesh(mesh.Object);
	//}
}

// Called when the game starts or when spawned
void ACSpawnActor::BeginPlay()
{
	Super::BeginPlay();

	//UObject* obj = StaticLoadObject(UMaterialInstanceConstant::StaticClass(),
	//				NULL, 
	//				L"MaterialInstanceConstant'/Game/04_Materials/Material_Mesh_Inst.Material_Mesh_Inst'");

	//UMaterialInstanceConstant* material = Cast<UMaterialInstanceConstant>(obj);

	UMaterialInstanceConstant* material;
	CHelpers::GetAssetDynamic<UMaterialInstanceConstant>(&material,
		"MaterialInstanceConstant'/Game/04_Materials/Material_Mesh_Inst.Material_Mesh_Inst'");

	Material = UMaterialInstanceDynamic::Create(material, this);
	Mesh->SetMaterial(0, Material);

	UKismetSystemLibrary::K2_SetTimer(this, "ChangeColor", 1.0f, true);

	GLog->Log(Material->GetName());

}

void ACSpawnActor::ChangeColor()
{
	FLinearColor color;
	color.R = UKismetMathLibrary::RandomFloatInRange(0, 1);
	color.G = UKismetMathLibrary::RandomFloatInRange(0, 1);
	color.B = UKismetMathLibrary::RandomFloatInRange(0, 1);
	color.A = 1.0f;
	Material->SetVectorParameterValue("Color", color);

	FLinearColor outcolor;
	FHashedMaterialParameterInfo info;
	info.Name = L"Color";
	Material->GetVectorParameterValue(info, outcolor);

	GLog->Log("change" + color.ToString() + " mat " + outcolor.ToString());

}


