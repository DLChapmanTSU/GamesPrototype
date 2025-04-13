// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "StatsManager.h"
#include "GameStatusManager.generated.h"

/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), BlueprintType )
class GAMESPROTOTYPE_API UGameStatusManager : public UObject
{
	GENERATED_BODY()
	
protected:
	UStatsManager* PlayerOne;
	UStatsManager* PlayerTwo;
public:
	UFUNCTION(BlueprintCallable)
		void SetPlayerOneStats(UStatsManager* manager);
	UFUNCTION(BlueprintCallable)
		void SetPlayerTwoStats(UStatsManager* manager);
	UFUNCTION(BlueprintCallable)
		bool GetHasPlayerOneWon();
	UFUNCTION(BlueprintCallable)
		bool GetHasPlayerTwoWon();
	UFUNCTION(BlueprintCallable)
		bool HasValidStats();
};
