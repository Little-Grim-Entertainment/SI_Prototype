// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "AoS_AIPerceptionStimuliSource.generated.h"

class UAISense;

/**
 * UAIPerceptionStimuliSourceComponent's implementation only registers UAISenses during the game's runtime.
 * This could be circumvented if access to bAutoRegisterAsSource was allowed within the base class.
 * However, that option is not provided outside of the Unreal editor.
 * Therefore, this class exists to enable us to store UAISenses for our Actors, without doing any initial setup
 * in the editor, and before the game's runtime. During the game's runtime, the senses will then be registered.
 *
 * For reference: https://forums.unrealengine.com/t/cant-register-uaisense-sight-with-uaiperceptionstimulisourcecomponent/149852/3
 */
UCLASS()
class AOS_PROTOTYPE_API UAoS_AIPerceptionStimuliSource : public UAIPerceptionStimuliSourceComponent
{
	GENERATED_BODY()

public:
	UAoS_AIPerceptionStimuliSource(const FObjectInitializer& ObjectInitializer);

	void RegisterSense(TSubclassOf<UAISense> SenseClass);
};
