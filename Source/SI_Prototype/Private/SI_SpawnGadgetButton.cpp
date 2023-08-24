// Fill out your copyright notice in the Description page of Project Settings.


#include "SI_SpawnGadgetButton.h"

#include "Characters/SI_Nick.h"
#include "Components/TextRenderComponent.h"


// Sets default values
ASI_SpawnGadgetButton::ASI_SpawnGadgetButton()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Button = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Button"));
	Button->SetupAttachment(RootComponent);
	Text = CreateDefaultSubobject<UTextRenderComponent>(TEXT("ButtonText"));
	Text->SetupAttachment(Button);
}

// Called when the game starts or when spawned
void ASI_SpawnGadgetButton::BeginPlay()
{
	Super::BeginPlay();

	bIsObservable = true;
}

void ASI_SpawnGadgetButton::OnInteract_Implementation(AActor* Caller)
{
	Super::OnInteract_Implementation(Caller);

	ASI_Nick* Nick = Cast<ASI_Nick>(GetWorld()->GetFirstPlayerController()->GetPawn());
	
	if(!IsValid(Nick))
	{
		return;
	}

	FTransform const GadgetTransform = Nick->GetActorTransform();
	Nick->Gadget = GetWorld()->SpawnActor<ASI_BaseGadget>(GadgetClass, GadgetTransform);
	if (IsValid(Nick->Gadget))
	{								
		Nick->Gadget->AttachToComponent(Nick->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("gadget_socket"));
	}
}

// Called every frame
void ASI_SpawnGadgetButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

