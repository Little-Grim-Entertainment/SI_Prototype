// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AoS_SkySphere.generated.h"

class UAoS_GameInstance;
class AAoS_SunLight;
class UAoS_WorldManager;
class ADirectionalLight;

UCLASS()
class AOS_PROTOTYPE_API AAoS_SkySphere : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAoS_SkySphere();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = BP_Skydome)
	USceneComponent* Base;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = BP_Skydome)
	UStaticMeshComponent* SkySphereMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OverrideSettings")
	float SunHeight = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OverrideSettings")
	float HorizonFalloff = 3.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OverrideSettings")
	FLinearColor ZenithColor = FLinearColor(0.034046, 0.109247, 0.295, 1);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OverrideSettings")
	FLinearColor HorizonColor = FLinearColor(1.979559, 2.586644, 3.0, 1);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OverrideSettings")
	FLinearColor CloudColor = FLinearColor(0.855778, 0.91902, 1, 1);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OverrideSettings")
	FLinearColor OverallColor = FLinearColor(1, 1, 1, 1);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterial* SkyMaterial;
	UPROPERTY(BlueprintReadWrite)
	UMaterialInstanceDynamic* DynamicSkyMaterial;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bRefreshMaterial;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bColorsDeterminedBySunPosition = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SunBrightness = 50.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CloudSpeed = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CloudOpacity = 0.7f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float StarsBrightness = 0.1f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCurveLinearColor* HorizonColorCurve;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCurveLinearColor* ZenithColorCurve;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCurveLinearColor* CloudColorColorCurve;
		
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	AAoS_SunLight* SunLightActor;

	UFUNCTION(BlueprintCallable)
	void UpdateSunDirection();
	UFUNCTION(BlueprintCallable)
	void RefreshMaterial();
	UFUNCTION(BlueprintCallable)
	void RotateSun(FRotator InRotation);

	UFUNCTION()
	void SetSunLightActor(AAoS_SunLight* SunLightToSet);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY()
	UAoS_WorldManager* WorldManager;
	UPROPERTY()
	UAoS_GameInstance* GameInstance;
};
