
#include "CAnimInstance.h"
#include "Global.h"//
#include "GameFramework/Character.h"//

void UCAnimInstance::NativeBeginPlay()
{
	//�θ�Ŭ���� base �κ� ����
	Super::NativeBeginPlay();

	OwnerCharacter = Cast<ACharacter>(TryGetPawnOwner());
}

void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	//�θ�Ŭ���� base �κ� ����
	Super::NativeUpdateAnimation(DeltaSeconds);

	CheckNull(OwnerCharacter);

	Speed = OwnerCharacter->GetVelocity().Size2D();
}
