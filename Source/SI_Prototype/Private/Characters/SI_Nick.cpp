// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SI_Nick.h"
#include "ATPCCameraComponent.h"
#include "AI/SI_AIPerceptionStimuliSource.h"
#include "SI_GameInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/Actor/SI_AbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Data/Characters/SI_NickCharacterData.h"
#include "Perception/AISense_Hearing.h"
#include "Perception/AISense_Sight.h"
#include "Data/Maps/SI_MapData.h"
#include "Levels/SI_LevelManager.h"

// ******************* TODO: DELETE WHEN GADGET SYSTEM IS IMPLEMENTED
#include "Actors/Gadgets/SI_Flashlight.h"
#include "Engine/SkeletalMeshSocket.h"

ASI_Nick::ASI_Nick()
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
	PerceptionStimuliSourceComponent = CreateDefaultSubobject<USI_AIPerceptionStimuliSource>(TEXT("Perception Stimuli Source Component"));
	PerceptionStimuliSourceComponent->RegisterSense(UAISense_Sight::StaticClass());
	PerceptionStimuliSourceComponent->RegisterSense(UAISense_Hearing::StaticClass());

	AbilitySystemComponent = CreateDefaultSubobject<USI_AbilitySystemComponent>(TEXT("AbilitySystemComponent"));

}

void ASI_Nick::PostInitializeComponents()
{
	Super::PostInitializeComponents();

}

UAbilitySystemComponent* ASI_Nick::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ASI_Nick::HideMeshes(bool Value)
{
	TArray<USceneComponent*> Meshes;
	GetMesh()->SetVisibility(Value);
	GetMesh()->GetChildrenComponents(true, Meshes);

	for (USceneComponent* _Mesh : Meshes)
	{
		_Mesh->SetVisibility(Value);
	}
}

USI_AbilitySystemComponent* ASI_Nick::GetSIAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ASI_Nick::GiveAbilities()
{
	if (!IsValid(AbilitySystemComponent)) {return;}

	for (TSubclassOf<USI_GameplayAbility>& Ability : DefaultAbilities)
	{
		AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(Ability, 1, INDEX_NONE, this));
	}
}

void ASI_Nick::BeginPlay()
{
	Super::BeginPlay();

	const USI_GameInstance* GameInstance = Cast<USI_GameInstance>(GetWorld()->GetGameInstance());
	if (!IsValid(GameInstance)) {return;}

	LevelManager = GameInstance->GetSubsystem<USI_LevelManager>();
	if (!IsValid(LevelManager)){return;}

	if(LevelManager->GetLevelHasLoaded())
	{
		OnLevelLoaded(LevelManager->GetCurrentLoadedMapState().GetMapData());
	}
	else
	{
		LevelManager->OnLevelLoaded.AddDynamic(this, &ThisClass::OnLevelLoaded);	
	}

	GiveAbilities();


	// ****************** TODO: DELETE WHEN GADGET SYSTEM IS IMPLEMENTED		
	// Spawn Flashlight at world 0
	if (FlashlightClass)
	{		
		FTransform const FlashlightTransform = GetActorTransform();
		Flashlight = GetWorld()->SpawnActor<ASI_Flashlight>(FlashlightClass, FlashlightTransform);
		if (IsValid(Flashlight))
		{								
			Flashlight->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("gadget_socket"));
		}				
	}
}

void ASI_Nick::OnLevelLoaded(USI_MapData* LoadedLevel, bool bShouldFade)
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
	
	if (MapName == "DA_NicksApartment")
	{
		GetMesh()->SetSkeletalMesh(NickCharacterData->GetClothingMeshFromName(FName(TEXT("NoJacketNick"))));
	}
	else
	{
		GetMesh()->SetSkeletalMesh(NickCharacterData->GetClothingMeshFromName(FName(TEXT("JacketNick"))));
	}
}

void ASI_Nick::OnCameraCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherComp == GetMesh())
	{
		HideMeshes(false);
	}
}

void ASI_Nick::OnCameraCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(OtherComp == GetMesh())
	{
		HideMeshes(true);
	}
}
