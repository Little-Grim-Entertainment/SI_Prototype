// Fill out your copyright notice in the Description page of Project Settings.


#include "Decorator/HorizonDialogueMsgSpaceDecorator.h"
#include "HorizonUIPrivate.h"


bool UHorizonDialogueMsgSpaceDecorator::BuildSegment_Implementation(UHorizonDialogueMsgTextBlock* InMsgTextBlock,
	int32 InCurrentSegInfoIndex, FHorizonDialogueSegmentInfo& InCurrentSegInfo,
	const TArray<FHorizonDialogueSegmentInfo>& InSegInfos)
{

	bool bWithSpaceL = true;
	bool bWithSpaceR = false;

	if (InCurrentSegInfo.Tags.Contains("NoSpace"))
	{
		bWithSpaceL = false;
		bWithSpaceR = false;
	}
	else if(InCurrentSegInfo.Tags.Contains("WithSpace"))
	{
		bWithSpaceL = true;
		bWithSpaceR = true;
	}
	else
	{
		// Handle Append Space to Segment Left 
		{
			if (InCurrentSegInfo.Tags.Contains("NoSpaceL"))
			{
				bWithSpaceL = false;
			}
			else if (InCurrentSegInfo.Tags.Contains("WithSpaceL"))
			{
				bWithSpaceL = true;
			}
			else
			{
				if(InCurrentSegInfoIndex == 0)
				{
					bWithSpaceL = false;
				}
			}
		}

		// Handle Append Space to Segment Right
		{
			if (InCurrentSegInfo.Tags.Contains("NoSpaceR"))
			{
				bWithSpaceR = false;
			}
			else if (InCurrentSegInfo.Tags.Contains("WithSpaceR"))
			{
				bWithSpaceR = true;
			}
		}


	}


	if (bWithSpaceR)
	{
		InCurrentSegInfo.Text.Append(Space.ToString());
	}
	if (bWithSpaceL)
	{
		if(InCurrentSegInfoIndex == 0)
		{
			InCurrentSegInfo.Text.InsertAt(0, FirstLineSpaceL.ToString());
		}
		else
		{
			InCurrentSegInfo.Text.InsertAt(0, Space.ToString());
		}
	
	}


	return bWithSpaceR || bWithSpaceL;

}
