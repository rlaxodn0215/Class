
#include "CSpawnActor.h"
#include "Global.h"
#include "Components/StaticMeshComponent.h"		// << :
#include "Materials/MaterialInstanceConstant.h"	// << :
#include "Kismet/KismetMathLibrary.h"			// << : �ð������� ���

/*
StaticMesh'/Game/Meshes/Mesh_Cube.Mesh_Cube'
*/

// Sets default values
ACSpawnActor::ACSpawnActor()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = Mesh;

	//�����Ϳ��� ������ �Ž����� ��ũ��Ʈ�� �����ϱ� ���2.
	UStaticMesh* mesh;
	CHelpers::GetAsset<UStaticMesh>(&mesh, "StaticMesh'/Game/Meshes/Mesh_Cube.Mesh_Cube'");
	Mesh->SetStaticMesh(mesh);

	//�����Ϳ��� ������ �Ž����� ��ũ��Ʈ�� �����ϱ� ���1.
	//ConstructorHelpers::FObjectFinder<UStaticMesh> 
	//	mesh(L"StaticMesh'/Game/Meshes/Mesh_Cube.Mesh_Cube'"); // ConstructorHelpers�� �����ڿ����� ��밡��

	//if (mesh.Succeeded())
	//{
	//	Mesh->SetStaticMesh(mesh.Object);
	//}
}

// Called when the game starts or when spawned
void ACSpawnActor::BeginPlay()
{
	Super::BeginPlay();
	
	//������Ʈ�� �����Ҷ� �ַ� �Ϲ����� ��ƾ Helpers�� 
	/*UObject* obj = StaticLoadObject(UMaterialInstanceConstant::StaticClass(),
		NULL, L"MaterialInstanceConstant'/Game/Materials/Material_Mesh_Inst.Material_Mesh_Inst'");
	UMaterialInstance* material = Cast<UMaterialInstance>(obj);*/


	//�̷� �����ڵ�� �����ڿ��� �� ���� ������ ����÷��̿��� ���°� ����
	UMaterialInstanceConstant* material;
	CHelpers::GetAssetDynamic<UMaterialInstanceConstant>(&material,
		"MaterialInstanceConstant'/Game/Materials/Material_Mesh_Inst.Material_Mesh_Inst'"
		);
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
	//Color��°��� �������� ���� ���ϴ� ���̴�.
	Material->SetVectorParameterValue("Color", color);
}



