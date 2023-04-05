// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AoS_Types.h"
#include "GameplayTagContainer.h"
#include "AoS_MapData.generated.h"

class UAoS_MusicManager;
class UAoS_CinematicDataAsset;
class UAoS_VideoDataAsset;

UCLASS()
class AOS_PROTOTYPE_API UAoS_MapData : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MapDetails")
	FString MapName;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MapDetails", meta=(Categories = "Map"))
	FGameplayTag MapTag;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MapDetails", meta=(Categories = "Map.Type"))
	FGameplayTag MapType;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MapDetails")
	TSoftObjectPtr<UWorld> Map;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Music")
<<<<<<< Updated upstream
	FMusicSettings BackgroundMusicSettings;

	
	UFUNCTION()
	void SetStreamingLevelRef(ULevelStreaming* StreamingLevelToSet);
	UFUNCTION()
	ULevelStreaming* GetStreamingLevelRef() const {return StreamingLevelRef;}

	// Music Functionns
	UFUNCTION(BlueprintCallable, Category = "Music")
	void PlayLevelBackgroundMusic(UAoS_MusicManager* InMusicManager);
	
	// Video Functions
	
	UFUNCTION(BlueprintCallable, Category = "Videos")
	void SetIntroVideo(UAoS_VideoDataAsset* InIntroVideo);
	UFUNCTION(BlueprintCallable, Category = "Videos")
	void ClearIntroVideo();
	
	UFUNCTION(BlueprintPure, Category = "Videos")
	UAoS_VideoDataAsset* GetIntroVideo() const;
	UFUNCTION(BlueprintPure, Category = "Videos")
	bool HasIntroVideo() const;
	UFUNCTION(BlueprintPure, Category = "Videos")
	bool IntroVideoHasPlayed() const;

	UFUNCTION(BlueprintCallable, Category = "Videos")
	void SetOutroVideo(UAoS_VideoDataAsset* InOutroVideo);
	UFUNCTION(BlueprintCallable, Category = "Videos")
	void ClearOutroVideo();
	
	UFUNCTION(BlueprintPure, Category = "Videos")
	UAoS_VideoDataAsset* GetOutroVideo() const;
	UFUNCTION(BlueprintPure, Category = "Videos")
	bool HasOutroVideo() const;
	UFUNCTION(BlueprintPure, Category = "Videos")
	bool OutroVideoHasPlayed() const;

	// Cinematic Functions
	
	UFUNCTION(BlueprintCallable, Category = "Cinematics")
	void SetIntroCinematic(UAoS_CinematicDataAsset* InIntroCinematic);
	UFUNCTION(BlueprintCallable, Category = "Cinematics")
	void ClearIntroCinematic();
	
	UFUNCTION(BlueprintPure, Category = "Cinematics")
	UAoS_CinematicDataAsset* GetIntroCinematic() const;
	UFUNCTION(BlueprintPure, Category = "Cinematics")
	bool HasIntroCinematic() const;
	UFUNCTION(BlueprintPure, Category = "Cinematics")
	bool IntroCinematicHasPlayed() const;


	UFUNCTION(BlueprintCallable, Category = "Cinematics")
	void SetOutroCinematic(UAoS_CinematicDataAsset* InOutroCinematic);
	UFUNCTION(BlueprintCallable, Category = "Cinematics")
	void ClearOutroCinematic();
	
	UFUNCTION(BlueprintPure, Category = "Cinematics")
	UAoS_CinematicDataAsset* GetOutroCinematic() const;
	UFUNCTION(BlueprintPure, Category = "Cinematics")
	bool HasOutroCinematic() const;
	UFUNCTION(BlueprintPure, Category = "Cinematics")
	bool OutroCinematicHasPlayed() const;

private:

	UPROPERTY()
	ULevelStreaming* StreamingLevelRef;
=======
	FAoS_MusicSettings BackgroundMusicSettings;
>>>>>>> Stashed changes
};
