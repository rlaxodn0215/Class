// Fill out your copyright notice in the Description page of Project Settings.


#include "CSpawnActor.h"
#include "Global.h"
#include "Components/StaticMeshComponent.h" // <<
#include "Materials/MaterialInstanceConstant.h" //<<"
#include "Kismet/KismetMathLibrary.h" // 시간관련한 헤더

/*
StaticMesh'/Game/Meshes/Mesh_Cube.Mesh_Cube'
*/

// Sets default values
ACSpawnActor::ACSpawnActor()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = Mesh;

	//에디터에서 가져온 매쉬파일 스크립트로 수정하기 방법2.
	UStaticMesh* mesh;
	CHelpers::GetAsset<UStaticMesh>(&mesh, "StaticMesh'/Game/Meshes/Mesh_Cube.Mesh_Cube'");
	Mesh->SetStaticMesh(mesh);

	//에디터에서 가져온 매쉬파일 스크립트로 수정하기 방법1.
	//ConstructorHelpers::FObjectFinder<UStaticMesh> 
	//	mesh(L"StaticMesh'/Game/Meshes/Mesh_Cube.Mesh_Cube'"); // ConstructorHelpers는 생성자에서만 사용가능

	//if (mesh.Succeeded())
	//{
	//	Mesh->SetStaticMesh(mesh.Object);
	//}
}

// Called when the game starts or when spawned
void ACSpawnActor::BeginPlay()
{
	Super::BeginPlay();
	
	//오브젝트를 생성할때 주로 일반적인 루틴 Helpers에 
	/*UObject* obj = StaticLoadObject(UMaterialInstanceConstant::StaticClass(),
		NULL, L"MaterialInstanceConstant'/Game/Materials/Material_Mesh_Inst.Material_Mesh_Inst'");
	UMaterialInstance* material = Cast<UMaterialInstance>(obj);*/


	//이런 생성코드는 생성자에서 쓸 수도 있지만 비긴플레이에서 쓰는게 좋음
	UMaterialInstanceConstant* material;
	CHelpers::GetAssetDynamic<UMaterialInstanceConstant>(&material,
		"MaterialInstanceConstant'/Game/Materials/Material_Mesh_Inst.Material_Mesh_Inst'");

	Material = UMaterialInstanceDynamic::Create(material, this);
	Mesh->SetMaterial(0, Material);

	UKismetSystemLibrary::K2_SetTimer(this, "ChangeColor", 1.0f, true);
	
}

void ACSpawnActor::ChangeColor()
{
	FLinearColor color;
	color.R = UKismetMathLibrary::RandomFloatInRange(0, 1);
	color.G = UKismetMathLibrary::RandomFloatInRange(0, 1);
	color.B = UKismetMathLibrary::RandomFloatInRange(0, 1);
	color.A = 1.0f;
	Material->SetVectorParameterValue("Color", color);
}



