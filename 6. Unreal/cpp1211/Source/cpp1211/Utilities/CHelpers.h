#pragma once

#include "CoreMinimal.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/World.h"

class CPP1211_API CHelpers
{
public:
	template<typename T> static void GetAsset(T** outObject, FString inPath)
	{
		ConstructorHelpers::FObjectFinder<T> asset(*inPath);
		verifyf(asset.Succeeded(), L"asset.Succeeded()");
		*outObject = asset.Object;
	}

	template<typename T> static void GetAssetDynamic(T** outObject, FString inPath)
	{
		T* obj = Cast<T>(StaticLoadObject(T::StaticClass(), NULL, *inPath));
		verifyf(!!obj, L"!!asset");// !!obj 는 asset.Succeeded와 비슷한 기능 obj != nullptr 이라는 뜻
		*outObject = obj;
	}

	template<typename T> static void CreateComponent(AActor* inActor, T** inComponent, FName inName, USceneComponent* inParent = NULL)
	{
		*inComponent = inActor->CreateDefaultSubobject<T>(inName);
		if (!!inParent)
		{
			(*inComponent)->SetupAttachment(inParent);
			return;
		}

		inActor->SetRootComponent(*inComponent);//parent가 null일때
	}

	template<typename T> static void GetClass(TSubclassOf<T>* outClass, FString inPath)
	{
		ConstructorHelpers::FClassFinder<T> asset(*inPath);
		verifyf(asset.Succeeded(), L"asset.Succeeded()");

		*outClass = asset.Class;
	}

	template<typename T> static void FindActors(class UWorld* InWorld, TArray<T*>& OutActors)
	{
		OutActors.Empty();

		TArray<AActor*> actors;
		UGameplayStatics::GetAllActorsOfClass(InWorld, T::StaticClass(), actors);
		for (AActor* actor : actors)
			OutActors.Add(Cast<T>(actor));
	}

};