// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AoS_Nick.h"
#include "ATPCCameraComponent.h"
#include "AI/AoS_AIPerceptionStimuliSource.h"
#include "AoS_GameInstance.h"
#include "Camera/CameraActor.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Data/Characters/AoS_NickCharacterData.h"
#include "Perception/AISense_Hearing.h"
#include "Perception/AISense_Sight.h"
#include "UI/AoS_HUD.h"
#include "Data/Maps/AoS_MapData.h"
#include "Levels/AoS_LevelManager.h"

AAoS_Nick::AAoS_Nick()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	ATPCCamera = CreateDefaultSubobject<UATPCCameraComponent>(TEXT("ATPCCamera"));
	ATPCCamera->SetupAttachment(RootComponent);

	// Create a follow camera
	NickFollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("NickFollowCamera"));
	NickFollowCamera->SetupAttachment(ATPCCamera);
	
	// Create an AI Perception Stimuli Source component
	PerceptionStimuliSourceComponent = CreateDefaultSubobject<UAoS_AIPerceptionStimuliSource>(TEXT("Perception Stimuli Source Component"));
	PerceptionStimuliSourceComponent->RegisterSense(UAISense_Sight::StaticClass());
	PerceptionStimuliSourceComponent->RegisterSense(UAISense_Hearing::StaticClass());
}

void AAoS_Nick::PostInitializeComponents()
{
	Super::PostInitializeComponents();

}

void AAoS_Nick::HideMeshes(bool Value)
{
	TArray<USceneComponent*> Meshes;
	GetMesh()->SetVisibility(Value);
	GetMesh()->GetChildrenComponents(true, Meshes);

	for (USceneComponent* _Mesh : Meshes)
	{
		_Mesh->SetVisibility(Value);
	}
}

void AAoS_Nick::BeginPlay()
{
	Super::BeginPlay();

	const UAoS_GameInstance* GameInstance = Cast<UAoS_GameInstance>(GetWorld()->GetGameInstance());
	if (!IsValid(GameInstance)) {return;}

	LevelManager = GameInstance->GetSubsystem<UAoS_LevelManager>();
	if (!IsValid(LevelManager)){return;}

	if(LevelManager->GetLevelHasLoaded())
	{
		OnLevelLoaded(LevelManager->GetCurrentLoadedMapState().GetMapData());
	}
	else
	{
		LevelManager->OnLevelLoaded.AddDynamic(this, &ThisClass::OnLevelLoaded);	
	}
}


void AAoS_Nick::OnLevelLoaded(UAoS_MapData* LoadedLevel, bool bShouldFade)
{
	if (!IsValid(NickCharacterData)) {return;}

	FString MapName;
	
	if (IsValid(LoadedLevel))
	{
		MapName = LoadedLevel->GetName();
	}
	else
	{
		MapName = "DA_MainMenu";
	}
	
	if (MapName == "DA_NicksOffice")
	{
		GetMesh()->SetSkeletalMesh(NickCharacterData->GetClothingMeshFromName(FName(TEXT("NoJacketNick"))));
	}
	else
	{
		GetMesh()->SetSkeletalMesh(NickCharacterData->GetClothingMeshFromName(FName(TEXT("JacketNick"))));
	}
}

void AAoS_Nick::OnCameraCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherComp == GetMesh())
	{
		HideMeshes(false);
	}
}

void AAoS_Nick::OnCameraCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(OtherComp == GetMesh())
	{
		HideMeshes(true);
	}
}
