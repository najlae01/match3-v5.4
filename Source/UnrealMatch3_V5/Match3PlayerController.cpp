// Copyright Epic Games, Inc. All Rights Reserved.

#include "Match3PlayerController.h"
#include "UnrealMatch3_V5.h"
#include "Kismet/GameplayStatics.h"

AMatch3PlayerController::AMatch3PlayerController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// We want the mouse cursor to show immediately on startup, without having to click in the window.
	bShowMouseCursor = true;

	// We need click/touch events to interact with our tiles.
	bEnableTouchEvents = bEnableClickEvents = true;
	bEnableTouchOverEvents = bEnableMouseOverEvents = true;

	ScoreChangeRate = 375.0f;

}

void AMatch3PlayerController::AddScore(int32 Points, bool bForceImmediateUpdate)
{
	Score += Points;
	if (bForceImmediateUpdate)
	{
		DisplayedScore = (float)Score;
	}
	else
	{
		GetWorldTimerManager().SetTimer(TickScoreDisplayHandle, this, &AMatch3PlayerController::TickScoreDisplay, 0.001f, true);
	}
}

int32 AMatch3PlayerController::GetScore()
{
	return Score;
}

int32 AMatch3PlayerController::GetDisplayedScore()
{
	return (int32)DisplayedScore;
}

int32 AMatch3PlayerController::CalculateBombPower_Implementation()
{
	return 0;
}

void AMatch3PlayerController::TickScoreDisplay()
{
	// This assumes score only goes up, or instantly drops when it is decreased.
	DisplayedScore += UGameplayStatics::GetWorldDeltaSeconds(this) * ScoreChangeRate;
	if (DisplayedScore >= (float)Score)
	{
		DisplayedScore = Score;
		GetWorldTimerManager().ClearTimer(TickScoreDisplayHandle);
	}
}