// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "StatsManager.h"
#include "GameStatusManager.generated.h"

/**
 * 
 */
UCLASS()
class GAMESPROTOTYPE_API UGameStatusManager : public UObject
{
	GENERATED_BODY()
protected:
	UStatsManager* PlayerOne;
	UStatsManager* PlayerTwo;
public:
	void SetPlayerOneStats(UStatsManager* manager);
	void SetPlayerTwoStats(UStatsManager* manager);
	bool GetHasPlayerOneWon();
	bool GetHasPlayerTwoWon();
};
