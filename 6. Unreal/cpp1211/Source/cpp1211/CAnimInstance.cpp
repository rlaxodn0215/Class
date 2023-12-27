
#include "CAnimInstance.h"
#include "Global.h"//
#include "GameFramework/Character.h"//

void UCAnimInstance::NativeBeginPlay()
{
	//부모클래스 base 부분 실행
	Super::NativeBeginPlay();

	OwnerCharacter = Cast<ACharacter>(TryGetPawnOwner());
}

void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	//부모클래스 base 부분 실행
	Super::NativeUpdateAnimation(DeltaSeconds);

	CheckNull(OwnerCharacter);

	Speed = OwnerCharacter->GetVelocity().Size2D();
}
