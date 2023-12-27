#include "CPlayer.h"
#include "Global.h"//<<
#include "CAnimInstance.h"//
#include "GameFrameWork/SpringArmComponent.h"//<<
#include "GameFrameWork/CharacterMovementComponent.h"//
#include "Camera/CameraComponent.h"//
#include "Components/CapsuleComponent.h"//

ACPlayer::ACPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	//�Ϲ����� �������
	//SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	//SpringArm->SetupAttachment(GetCapsuleComponent());

	//Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	//Camera->SetupAttachment(SpringArm);

	//CHelpers�� ������Ʈ ������ �Լ�ȭ�ؼ� ���� �ڵ带 ���ٷ� ���̴� ���
	CHelpers::CreateComponent<USpringArmComponent>(this, &SpringArm, "SpringArm", GetCapsuleComponent());
	CHelpers::CreateComponent<UCameraComponent>(this, &Camera, "Camera", SpringArm);


	bUseControllerRotationYaw = false; //z�� ȸ���� ���Ƽ� ī�޶� ���⸸ ���󰡰�, �¿� �������°� yaw ��� �� ���Ʒ��� pitch
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = 400.0f;
	
	//���̷���Ž� ����
	USkeletalMesh* mesh;
	CHelpers::GetAsset<USkeletalMesh>(&mesh,
		"SkeletalMesh'/Game/Character/Mesh/SK_Mannequin.SK_Mannequin'");
	GetMesh()->SetSkeletalMesh(mesh);

	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	//ABP(�ִϸ��̼� �������Ʈ) ������ �÷��̾ �����ϱ�
	TSubclassOf<UAnimInstance> animInstance;
	CHelpers::GetClass<UAnimInstance>(&animInstance, "AnimBlueprint'/Game/ABP_CPlayer.ABP_CPlayer_C'");
	GetMesh()->SetAnimInstanceClass(animInstance);

	//ī�޶����ε�
	SpringArm->SetRelativeLocation(FVector(0, 0, 60));
	SpringArm->TargetArmLength = 200.0f;
	SpringArm->bDoCollisionTest = false; //�߰��� ��ü�� ������ �浹ó�� �Ұ�����
	SpringArm->bUsePawnControlRotation = true; //ĳ���� ����ٴϰ� �Ұ�����

}

void ACPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//������Ʈ ��ǲ������ �ڵ带 ���ε�
	//�� ����
	PlayerInputComponent->BindAxis("MoveForward", this, &ACPlayer::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACPlayer::OnMoveRight);
	PlayerInputComponent->BindAxis("HorizontalLook", this, &ACPlayer::OnHorizontalLook);
	PlayerInputComponent->BindAxis("VerticalLook", this, &ACPlayer::OnVerticalLook);

	//�׼� ����
	//Running �̶�� �׼ǿ� ���� ������ ������ OnRunning �����ϰ� ������ ������ OffRunning ����
	PlayerInputComponent->BindAction("Running", EInputEvent::IE_Pressed, this, &ACPlayer::OnRunning);
	PlayerInputComponent->BindAction("Running", EInputEvent::IE_Released, this, &ACPlayer::OffRunning);

}

//Ű���� ��ǲ
void ACPlayer::OnMoveForward(float Axis)
{
	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetForwardVector().GetSafeNormal2D();
	AddMovementInput(direction, Axis);
}

void ACPlayer::OnMoveRight(float Axis)
{
	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetRightVector().GetSafeNormal2D();
	AddMovementInput(direction, Axis);
}

//���콺 ��ǲ
void ACPlayer::OnHorizontalLook(float Axis)
{
	AddControllerYawInput(Axis);
}

void ACPlayer::OnVerticalLook(float Axis)
{
	AddControllerPitchInput(Axis);
}

void ACPlayer::OnRunning()
{
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
}

void ACPlayer::OffRunning()
{
	GetCharacterMovement()->MaxWalkSpeed = 400.0f;
}

