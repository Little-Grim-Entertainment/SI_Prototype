// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/AoS_LevelTransition.h"
#include "Engine/Texture2D.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/BillboardComponent.h"
#include "Media/AoS_MediaManager.h"
#include "Data/Maps/AoS_MapData.h"
#include "Data/Media/AoS_CinematicDataAsset.h"
#include "Data/Media/AoS_VideoDataAsset.h"
#include "Kismet/KismetStringLibrary.h"
#include "Levels/AoS_LevelManager.h"


AAoS_LevelTransition::AAoS_LevelTransition()
{

MapSprite = CreateEditorOnlyDefaultSubobject<UBillboardComponent>(TEXT("Sprite"));

#if WITH_EDITORONLY_DATA

	if (!IsRunningCommandlet())
	{
		// Structure to hold one-time initialization
		struct FConstructorStatics
		{
			ConstructorHelpers::FObjectFinderOptional<UTexture2D> LevelTransitionTextureObject;
			FName ID_LevelTransition;
			FText NAME_LevelTransition;
			FName ID_Navigation;
			FText NAME_Navigation;
			FConstructorStatics()
				: LevelTransitionTextureObject(TEXT("Texture2D'/Game/AoS/UI/Interaction/Textures/StreetSign/S_TravelStreetSign.S_TravelStreetSign'"))
				, ID_LevelTransition(TEXT("PlayerStart"))
				, NAME_LevelTransition(NSLOCTEXT("SpriteCategory", "LevelTransition", "Level Transition"))
				, ID_Navigation(TEXT("Navigation"))
				, NAME_Navigation(NSLOCTEXT("SpriteCategory", "Navigation", "Navigation"))
			{
			}
		};
		static FConstructorStatics ConstructorStatics;

		if (MapSprite)
		{
			MapSprite->Sprite = ConstructorStatics.LevelTransitionTextureObject.Get();
			MapSprite->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
			MapSprite->bHiddenInGame = true;
			MapSprite->SpriteInfo.Category = ConstructorStatics.ID_LevelTransition;
			MapSprite->SpriteInfo.DisplayName = ConstructorStatics.NAME_LevelTransition;
			MapSprite->SetupAttachment(RootComponent);
			MapSprite->SetUsingAbsoluteScale(true);
			MapSprite->bIsScreenSizeScaled = true;
		}
	}

	bIsSpatiallyLoaded = false;
#endif // WITH_EDITORONLY_DATA
}

void AAoS_LevelTransition::OnBeginOverlap(AAoS_Nick* InNickActor)
{
	Super::OnBeginOverlap(InNickActor);
	
}

void AAoS_LevelTransition::OnEndOverlap(AAoS_Nick* InNickActor)
{
	Super::OnEndOverlap(InNickActor);
	
}

void AAoS_LevelTransition::OnInteract_Implementation(AActor* Caller)
{
	Super::OnInteract_Implementation(Caller);
	
	if (!MapToLoadTag.IsValid()){return;}

	UAoS_LevelManager* LevelManager = GetWorld()->GetGameInstance()->GetSubsystem<UAoS_LevelManager>();
	if (!IsValid(LevelManager)) {return;}

	FString NickPlayerStartTag = LevelManager->GetCurrentMap()->GetName();
	NickPlayerStartTag = UKismetStringLibrary::Replace(NickPlayerStartTag, "DA_", "Nick_");

	LevelManager->LoadLevelByTag(MapToLoadTag, NickPlayerStartTag);	
}
