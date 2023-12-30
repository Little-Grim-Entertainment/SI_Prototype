// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SI_CharacterSpawner.h"
#include "Async/TaskGraphInterfaces.h"
#include "Characters/SI_Character.h"
#include "Characters/Data/SI_CharacterData.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/ArrowComponent.h"
#include "Engine/Texture2D.h"
#include "Components/CapsuleComponent.h"
#include "Components/BillboardComponent.h"
#include "Subsystems/EditorActorSubsystem.h"


ASI_CharacterSpawner::ASI_CharacterSpawner(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	GetCapsuleComponent()->InitCapsuleSize(40.0f, 92.0f);
	GetCapsuleComponent()->SetShouldUpdatePhysicsVolume(false);
	
#if WITH_EDITORONLY_DATA
	ArrowComponent = CreateEditorOnlyDefaultSubobject<UArrowComponent>(TEXT("Arrow"));

	if (!IsRunningCommandlet())
	{
		// Structure to hold one-time initialization
		struct FConstructorStatics
		{
			ConstructorHelpers::FObjectFinderOptional<UTexture2D> CharacterSpawnerTextureObject;
			FName ID_CharacterSpawner;
			FText NAME_CharacterSpawner;
			FName ID_Navigation;
			FText NAME_Navigation;
			FConstructorStatics()
				: CharacterSpawnerTextureObject(TEXT("/Engine/EditorResources/S_Player"))
				, ID_CharacterSpawner(TEXT("CharacterSpawner"))
				, NAME_CharacterSpawner(NSLOCTEXT("SpriteCategory", "CharacterSpawner", "Character Spawner"))
				, ID_Navigation(TEXT("Navigation"))
				, NAME_Navigation(NSLOCTEXT("SpriteCategory", "Navigation", "Navigation"))
			{
			}
		};
		static FConstructorStatics ConstructorStatics;

		if (GetGoodSprite())
		{
			GetGoodSprite()->Sprite = ConstructorStatics.CharacterSpawnerTextureObject.Get();
			GetGoodSprite()->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));
			GetGoodSprite()->SpriteInfo.Category = ConstructorStatics.ID_CharacterSpawner;
			GetGoodSprite()->SpriteInfo.DisplayName = ConstructorStatics.NAME_CharacterSpawner;
		}
		if (GetBadSprite())
		{
			GetBadSprite()->SetVisibility(false);
		}

		if (ArrowComponent)
		{
			ArrowComponent->ArrowColor = FColor(150, 200, 255);

			ArrowComponent->ArrowSize = 1.0f;
			ArrowComponent->bTreatAsASprite = true;
			ArrowComponent->SpriteInfo.Category = ConstructorStatics.ID_Navigation;
			ArrowComponent->SpriteInfo.DisplayName = ConstructorStatics.NAME_Navigation;
			ArrowComponent->SetupAttachment(GetCapsuleComponent());
			ArrowComponent->bIsScreenSizeScaled = true;
		}
	}

	bIsSpatiallyLoaded = false;
#endif // WITH_EDITORONLY_DATA
}

// Called when the game starts or when spawned
void ASI_CharacterSpawner::BeginPlay()
{
	Super::BeginPlay();

#if WITH_EDITORONLY_DATA
	if(!PreviewSkeletalMeshComponents.IsEmpty())
	{
		ResetCharacterSpawner();
	}
#endif

	SpawnCharacter();
}

void ASI_CharacterSpawner::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

#if WITH_EDITOR
	if(!IsValid(CharacterData)) {return;}
	if(EndPlayReason != EEndPlayReason::EndPlayInEditor || !IsValid(CharacterData)){return;}

	SpawnPreviewCharacter(CharacterData->CharacterClass);
#endif
}

#if WITH_EDITOR
void ASI_CharacterSpawner::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	
	const FName MemberPropertyName = (PropertyChangedEvent.MemberProperty != nullptr) ? PropertyChangedEvent.MemberProperty->GetFName() : NAME_None;

	if (MemberPropertyName == GET_MEMBER_NAME_CHECKED(ASI_CharacterSpawner, CharacterData))
	{
		ResetCharacterSpawner();
		if(!IsValid(CharacterData)) {return;}
		
		SpawnPreviewCharacter(CharacterData->CharacterClass);
	}
}

void ASI_CharacterSpawner::SpawnPreviewCharacter(const TSubclassOf<ASI_Character>& InCharacterClass)
{
	if(!IsValid(InCharacterClass)) {return;}
	
	ResetCharacterSpawner();
	
	UEditorActorSubsystem* EditorActorSubsystem = GEditor->GetEditorSubsystem<UEditorActorSubsystem>();
	ASI_Character* PreviewCharacter = Cast<ASI_Character>(EditorActorSubsystem->SpawnActorFromClass(InCharacterClass, GetActorLocation(), GetActorRotation()));
	if(!IsValid(PreviewCharacter) || !IsValid(PreviewCharacter->GetMesh())) {return;}

	TArray<USkeletalMeshComponent*> SkeletalMeshComponents;
	PreviewCharacter->GetComponents<USkeletalMeshComponent>(SkeletalMeshComponents);
	DuplicateSkeletalMeshComponents(SkeletalMeshComponents);

	TArray<UStaticMeshComponent*> StaticMeshComponents;
	PreviewCharacter->GetComponents<UStaticMeshComponent>(StaticMeshComponents);
	DuplicateStaticMeshComponents(StaticMeshComponents);

	const UCapsuleComponent* PreviewCapsuleComponent = PreviewCharacter->GetCapsuleComponent();
	if(!IsValid(PreviewCapsuleComponent)) {return;}

	GetCapsuleComponent()->SetCapsuleSize(PreviewCapsuleComponent->GetScaledCapsuleRadius(), PreviewCapsuleComponent->GetScaledCapsuleHalfHeight());
	
	PreviewCharacter->Destroy();
}

void ASI_CharacterSpawner::DuplicateSkeletalMeshComponents(const TArray<USkeletalMeshComponent*>& InSkeletalMeshArray)
{
	for (int32 CurrentIndex = 0; CurrentIndex < InSkeletalMeshArray.Num(); CurrentIndex++)
	{
		const USkeletalMeshComponent* CurrentSkeletalMeshComponent = InSkeletalMeshArray[CurrentIndex];
		if(!IsValid(CurrentSkeletalMeshComponent)){continue;}

		const FName CurrentMeshName = FName(CurrentSkeletalMeshComponent->GetName());
		USkeletalMeshComponent* NewSkeletalMesh = DuplicateObject<USkeletalMeshComponent>(CurrentSkeletalMeshComponent, GetRootComponent(), CurrentMeshName);
		if(!IsValid(NewSkeletalMesh)) {continue;}

		NewSkeletalMesh->RegisterComponent();
		if(CurrentIndex > 0)
		{
			NewSkeletalMesh->AttachToComponent(PreviewSkeletalMeshComponents[0], FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		}
		else
		{
			NewSkeletalMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		}

		NewSkeletalMesh->CreationMethod = EComponentCreationMethod::Instance;
		NewSkeletalMesh->SetRelativeLocation(CurrentSkeletalMeshComponent->GetRelativeLocation());
		NewSkeletalMesh->SetRelativeRotation(CurrentSkeletalMeshComponent->GetRelativeRotation());
		
		PreviewSkeletalMeshComponents.AddUnique(NewSkeletalMesh);
	}
}

void ASI_CharacterSpawner::DuplicateStaticMeshComponents(const TArray<UStaticMeshComponent*>& InStaticMeshArray)
{
	for (int32 CurrentIndex = 0; CurrentIndex < InStaticMeshArray.Num(); CurrentIndex++)
	{
		const UStaticMeshComponent* CurrentStaticMeshComponent = InStaticMeshArray[CurrentIndex];
		if(!IsValid(CurrentStaticMeshComponent)){continue;}
		if(IsValid(CurrentStaticMeshComponent->GetStaticMesh()) && CurrentStaticMeshComponent->GetStaticMesh().GetName().Contains("Cam")) {continue;}

		const FName CurrentMeshName = FName(CurrentStaticMeshComponent->GetName());
		UStaticMeshComponent* NewStaticMesh = DuplicateObject<UStaticMeshComponent>(CurrentStaticMeshComponent, GetRootComponent(), CurrentMeshName);
		if(!IsValid(NewStaticMesh)) {continue;}

		NewStaticMesh->RegisterComponent();
		if(CurrentIndex > 0)
		{
			NewStaticMesh->AttachToComponent(PreviewStaticMeshComponents[0], FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		}
		else
		{
			NewStaticMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		}

		NewStaticMesh->CreationMethod = EComponentCreationMethod::Instance;
		NewStaticMesh->SetRelativeLocation(CurrentStaticMeshComponent->GetRelativeLocation());
		NewStaticMesh->SetRelativeRotation(CurrentStaticMeshComponent->GetRelativeRotation());
		
		PreviewStaticMeshComponents.AddUnique(NewStaticMesh);
	}
}
#endif

#if WITH_EDITORONLY_DATA
/** Returns ArrowComponent subobject **/
UArrowComponent* ASI_CharacterSpawner::GetArrowComponent() const
{
	return ArrowComponent;
}

void ASI_CharacterSpawner::ResetCharacterSpawner()
{
	if(!PreviewSkeletalMeshComponents.IsEmpty())
	{
		for (USkeletalMeshComponent* CurrentSkeletalMeshComponent : PreviewSkeletalMeshComponents)
		{
			if(!IsValid(CurrentSkeletalMeshComponent)) {continue;}
			CurrentSkeletalMeshComponent->DestroyComponent();
		}
		PreviewSkeletalMeshComponents.Empty();
	}
	if(!PreviewStaticMeshComponents.IsEmpty())
	{
		for (UStaticMeshComponent* CurrentStaticMeshComponent : PreviewStaticMeshComponents)
		{
			if(!IsValid(CurrentStaticMeshComponent)) {continue;}
			CurrentStaticMeshComponent->DestroyComponent();
		}
		PreviewStaticMeshComponents.Empty();
	}
}
#endif

void ASI_CharacterSpawner::SpawnCharacter()
{
	UWorld* World = GetWorld();
	if(!IsValid(World) || !IsValid(CharacterData)) {return;}


	FActorSpawnParameters ActorSpawnParameters;
	ActorSpawnParameters.Owner = this;
	
	const FVector SpawnLocation = GetActorLocation();
	const FRotator SpawnRotation = GetActorRotation();
	AActor* SpawnedActor = World->SpawnActor(CharacterData->CharacterClass, &SpawnLocation, &SpawnRotation, ActorSpawnParameters);
	SpawnedCharacter = Cast<ASI_Character>(SpawnedActor);
}
