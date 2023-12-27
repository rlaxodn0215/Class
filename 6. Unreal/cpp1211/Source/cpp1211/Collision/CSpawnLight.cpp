#include "CSpawnLight.h"
#include "Global.h"
#include "CMultiCastTrigger.h"
#include "Components/TextRenderComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SpotLightComponent.h"

// Sets default values
ACSpawnLight::ACSpawnLight()
{
	CHelpers::CreateComponent<USceneComponent>(this, &Scene, "Scene");
	CHelpers::CreateComponent<UTextRenderComponent>(this, &Text, "Text", Scene);

	Text->SetRelativeLocation(FVector(0, 0, 100));
	Text->SetRelativeRotation(FRotator(0, 90, 0));
	Text->SetRelativeScale3D(FVector(2));
	Text->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
	Text->TextRenderColor = FColor::Red;
	Text->Text = FText::FromString(GetName());

	for (int32 i = 0; i < 3; i++)
	{
		FString str;
		str.Append("SpawnLight_");
		str.Append(FString::FromInt(i + 1));

		CHelpers::CreateComponent<USpotLightComponent>(this, &SpotLights[i],
			FName(str), Scene);

		SpotLights[i]->SetRelativeLocation(FVector(i * 150, 0, 0));
		SpotLights[i]->SetRelativeRotation(FRotator(-90, 0, 0));
		SpotLights[i]->Intensity = 1e+5f;
		SpotLights[i]->OuterConeAngle = 25.0f;

	}
}

void ACSpawnLight::BeginPlay()
{
	Super::BeginPlay();
	TArray<ACMultiCastTrigger*> triggers;
	CHelpers::FindActors<ACMultiCastTrigger>(GetWorld(), triggers);
	// 이게 원인으로 언리얼 터짐
	triggers[0]->OnMultiLightBeginOverlap.AddUFunction(this, "OnLightColor");

}

void ACSpawnLight::OnLightColor(int32 InIndex, FLinearColor InColor)
{
	for (int32 i = 0; i < 3; i++)
	{
		SpotLights[i]->SetLightColor(FLinearColor(1,1,1));
	}

	SpotLights[InIndex]->SetLightColor(InColor);
}


