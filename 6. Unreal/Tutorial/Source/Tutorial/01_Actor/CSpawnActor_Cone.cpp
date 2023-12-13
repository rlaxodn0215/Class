// Fill out your copyright notice in the Description page of Project Settings.


#include "CSpawnActor_Cone.h"
#include "Global.h"

ACSpawnActor_Cone::ACSpawnActor_Cone()
{
	UStaticMesh* mesh;
	CHelpers::GetAsset<UStaticMesh>(&mesh, "StaticMesh'/Game/03_Meshs/Mesh_Cone.Mesh_Cone'");
	Mesh->SetStaticMesh(mesh);
}