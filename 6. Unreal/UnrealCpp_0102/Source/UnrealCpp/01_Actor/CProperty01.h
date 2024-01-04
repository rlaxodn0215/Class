#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CProperty01.generated.h"

UCLASS()
class UNREALCPP_API ACProperty01 : public AActor
{
	GENERATED_BODY()
	
public:	
	ACProperty01();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	// 매크로	   Alt + W
	// 매크로 변경 Alt + E
	UPROPERTY(EditAnywhere)		// 모두 표시
		int A = 10;
	UPROPERTY(EditInstanceOnly) // 에디터에서만 표시
		int B = 20;
	UPROPERTY(EditDefaultsOnly) // 블루프린트에서만 표시
		int C;
	
protected:
	UPROPERTY(VisibleAnywhere)	// 편집불가
		int E = 40;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		int D = 40;




};
