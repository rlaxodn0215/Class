#pragma once

#include "CoreMinimal.h" // 언리얼 어디서든 추가해야하는 헤더파일
#include "UObject/ConstructorHelpers.h" 
#include "Engine/World.h"


class UNREALCPP_API CHelpers
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
		verifyf(!!obj, L"!!asset"); // !!obj는 obj != nullptr이란 표현
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

		inActor->SetRootComponent(*inComponent);
	}

	template<typename T> static void GetClass(TSubclassOf<T>* outClass, FString inPath)
	{
		ConstructorHelpers::FClassFinder<T> asset(*inPath);
		verifyf(asset.Succeeded(), L"asset.Succeded()");

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