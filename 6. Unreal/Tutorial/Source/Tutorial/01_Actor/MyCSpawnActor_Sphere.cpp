// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCSpawnActor_Sphere.h"
#include "Global.h"

AMyCSpawnActor_Sphere::AMyCSpawnActor_Sphere()
{
	UStaticMesh* mesh;
	CHelpers::GetAsset<UStaticMesh>(&mesh, "StaticMesh'/Game/03_Meshs/Mesh_Sphere.Mesh_Sphere'");
	Mesh->SetStaticMesh(mesh);
}

