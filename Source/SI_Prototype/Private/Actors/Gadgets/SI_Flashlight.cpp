// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Gadgets/SI_Flashlight.h"
#include "Components/SpotLightComponent.h"


ASI_Flashlight::ASI_Flashlight()
{
	//*** CONSTRUCTOR
	Spotlight = CreateDefaultSubobject<USpotLightComponent>(TEXT("Flashlight Spotlight"));
	Spotlight->SetupAttachment(RootComponent);
	// bFlashlightOn = false;
}


//1. ***[DELETE] If input action is pressed(?) then turn light on and off
// INTERFACE - UsePrimary
// if (bFlashlightOn) {myFlashlight->SpotlightIntensity = 0.0f}
// else {myFlashlight->SpotlightIntensity = 0.0f}



//2. ***[DELETE] If input action is pressed(?) then place a flashlight segment
// INTERFACE - UseSecondary
// 2.1 Check if overlapping segment and pick up segment
// if (overlapping actor == (SegmentClass)
//		{ PickUpSegment }

// else if (SegmentsPlaced == MaxPlaceableSegments)
//		{"No more placeable segments"}
// else
//		{PlaceSegment();}

//void PickUpSegment()
//{
//		destroyOverlappingSegment;
//		PlayAnimation;
//		SegmentsPlaced--; 
//		ChangeGadgetIcon;
//}

//void PlaceSegment()
//{
//SegmentsPlaced--;