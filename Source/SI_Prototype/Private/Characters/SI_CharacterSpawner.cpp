// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SI_CharacterSpawner.h"
#include "Async/TaskGraphInterfaces.h"
#include "Characters/SI_Character.h"
#include "Characters/Data/SI_CharacterData.h"
#include "Characters/Data/SI_CharacterList.h"
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
}

void ASI_CharacterSpawner::Destroyed()
{
	Super::Destroyed();

#if WITH_EDITORONLY_DATA
	ResetCharacterSpawner();
#endif
}

#if WITH_EDITOR
void ASI_CharacterSpawner::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	
	const FName MemberPropertyName = (PropertyChangedEvent.MemberProperty != nullptr) ? PropertyChangedEvent.MemberProperty->GetFName() : NAME_None;

	if (MemberPropertyName == GET_MEMBER_NAME_CHECKED(ASI_CharacterSpawner, CharacterTag))
	{
		ResetCharacterSpawner();

		USI_CharacterList* CharacterList = LoadObject<USI_CharacterList>(NULL, TEXT("/Game/SI/Data/Characters/DA_CharacterList.DA_CharacterList"));
		if(!IsValid(CharacterList)){return;}

		const USI_CharacterData* CharacterData = CharacterList->GetCharacterDataByTag(CharacterTag);
		if(!IsValid(CharacterData)) {return;}
		
		SpawnPreviewCharacter(CharacterData->CharacterClass);
	}
}

void ASI_CharacterSpawner::SpawnPreviewCharacter(const TSubclassOf<ASI_Character>& InCharacterClass)
{
	if(!IsValid(InCharacterClass)) {return;}

	CharacterClass = InCharacterClass;
	
	ResetCharacterSpawner();
	
	UEditorActorSubsystem* EditorActorSubsystem = GEditor->GetEditorSubsystem<UEditorActorSubsystem>();
	PreviewCharacter = Cast<ASI_Character>(EditorActorSubsystem->SpawnActorFromClass(InCharacterClass, GetActorLocation(), GetActorRotation()));
	if(!IsValid(PreviewCharacter) || !IsValid(PreviewCharacter->GetMesh())) {return;}

	PreviewCharacter->SetupPreviewCharacter();
	PreviewCharacter->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
	const FVector NewLocation = FVector(GetActorLocation().X, GetActorLocation().Y, PreviewCharacter->GetMesh()->GetRelativeLocation().Z);
	PreviewCharacter->SetActorLocation(NewLocation);

	const FRotator NewRotation = FRotator(GetActorRotation().Pitch, GetActorRotation().Yaw - 90, GetActorRotation().Roll);
	PreviewCharacter->SetActorRotation(NewRotation);
	PreviewCharacter->SetActorEnableCollision(false);
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
	if(IsValid(PreviewCharacter))
	{
		PreviewCharacter->Destroy();
		CharacterClass = nullptr;
	}
}
#endif
