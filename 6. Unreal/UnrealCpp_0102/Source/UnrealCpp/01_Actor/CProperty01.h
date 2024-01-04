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
	// ��ũ��	   Alt + W
	// ��ũ�� ���� Alt + E
	UPROPERTY(EditAnywhere)		// ��� ǥ��
		int A = 10;
	UPROPERTY(EditInstanceOnly) // �����Ϳ����� ǥ��
		int B = 20;
	UPROPERTY(EditDefaultsOnly) // �������Ʈ������ ǥ��
		int C;
	
protected:
	UPROPERTY(VisibleAnywhere)	// �����Ұ�
		int E = 40;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		int D = 40;




};
