// Fill out your copyright notice in the Description page of Project Settings.


#include "Cameras/SI_DialogueCamera.h"
#include "ATPCCameraComponent.h"
#include "Camera/CameraComponent.h"
#include "Characters/SI_Character.h"
#include "Characters/SI_Nick.h"


// Sets default values
ASI_DialogueCamera::ASI_DialogueCamera()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Create a camera boom (pulls in towards the player if there is a collision)
	ATPCCamera = CreateDefaultSubobject<UATPCCameraComponent>(TEXT("ATPCCamera"));
	ATPCCamera->SetupAttachment(RootComponent);

	// Create a follow camera
	DialogueCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("DialogueFollowCam"));
	DialogueCamera->SetupAttachment(ATPCCamera);

	SetActorEnableCollision(false);
}

void ASI_DialogueCamera::SetNewFocusedCharacter(ASI_Character* InNewFocusedCharacter)
{
	if(!IsValid(InNewFocusedCharacter) || InNewFocusedCharacter == FocusedCharacter) {return;}
	
	FocusedCharacter = InNewFocusedCharacter;
	OnFocusedCharacterChanged();
}

FVector ASI_DialogueCamera::GetOffsetLocation(float InSpawnForwardOffset, float InSpawnRightOffset, float InZOffset)
{
	if(!IsValid(FocusedCharacter)) {return FVector();}

	const USkeletalMeshComponent* CharacterSkeletalMesh = FocusedCharacter->GetMesh();
	if(!IsValid(CharacterSkeletalMesh)) {return FVector();}

	const FVector HeadLocation = CharacterSkeletalMesh->GetBoneLocation(FName(TEXT("head")));

	const FVector CharacterForwardVector = FocusedCharacter->GetActorForwardVector();
	const FVector CharacterRightVector = FocusedCharacter->GetActorRightVector();

	const FVector ForwardOffset = CharacterForwardVector * InSpawnForwardOffset;
	const FVector RightOffset = CharacterRightVector * InSpawnRightOffset;
	
	FVector OffsetLocation = FVector(HeadLocation.X + ForwardOffset.X, HeadLocation.Y + ForwardOffset.Y, HeadLocation.Z);
	OffsetLocation = FVector(OffsetLocation.X + RightOffset.X, OffsetLocation.Y + RightOffset.Y, OffsetLocation.Z + InZOffset);
	
	return OffsetLocation;
}

FRotator ASI_DialogueCamera::GetOffsetRotation(float InYawRotationOffset, float InPitchRotationOffset)
{
	if(!IsValid(FocusedCharacter)) {return FRotator();}

	const FRotator CharacterRotation = FocusedCharacter->GetActorRotation();
	FRotator OffsetRotation = CharacterRotation;

	float LocalYawOffset = InYawRotationOffset;
	if(OffsetRotation.Yaw < 0)
	{
		LocalYawOffset *= -1;
	}
	float LocalPitchOffset = InPitchRotationOffset;
	if(OffsetRotation.Pitch < 0)
	{
		LocalPitchOffset *= -1;
	}

	const float RotationAmount = 90.0f;
	OffsetRotation.Yaw += RotationAmount;
	OffsetRotation = FRotator(OffsetRotation.Pitch + LocalPitchOffset, OffsetRotation.Yaw + LocalYawOffset, OffsetRotation.Roll);
	
	return OffsetRotation;
}

void ASI_DialogueCamera::OnFocusedCharacterChanged()
{
	if(!IsValid(FocusedCharacter)) {return;}
	const ASI_Nick* FocusedNick = Cast<ASI_Nick>(FocusedCharacter);
	
	const FVector OffsetLocation = IsValid(FocusedNick) ? GetOffsetLocation(NickSpawnForwardOffset, NickSpawnRightOffset, NickSpawnZOffset) : GetOffsetLocation(NPCSpawnForwardOffset, NPCSpawnRightOffset, NPCSpawnZOffset);
	const FRotator OffsetRotation = IsValid(FocusedNick) ? GetOffsetRotation(NickYawRotationOffset, NickPitchRotationOffset) : GetOffsetRotation(NPCYawRotationOffset, NPCPitchRotationOffset);
	
	SetActorLocation(OffsetLocation);
	DialogueCamera->SetRelativeRotation(OffsetRotation);
}

// Called when the game starts or when spawned
void ASI_DialogueCamera::BeginPlay()
{
	Super::BeginPlay();
}

