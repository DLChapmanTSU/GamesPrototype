// Fill out your copyright notice in the Description page of Project Settings.


#include "GameStatusManager.h"



void UGameStatusManager::SetPlayerOneStats(UStatsManager* manager)
{
	PlayerOne = manager;
}

void UGameStatusManager::SetPlayerTwoStats(UStatsManager* manager)
{
	PlayerTwo = manager;
}

bool UGameStatusManager::GetHasPlayerOneWon()
{
	if (PlayerOne != nullptr && IsValid(PlayerOne) && PlayerTwo != nullptr && IsValid(PlayerTwo))
	{
		return PlayerOne->GetHealth() > 0 && PlayerTwo->GetHealth() <= 0;
	}
	return false;
}

bool UGameStatusManager::GetHasPlayerTwoWon()
{
	if (PlayerOne != nullptr && IsValid(PlayerOne) && PlayerTwo != nullptr && IsValid(PlayerTwo))
	{
		return PlayerTwo->GetHealth() > 0 && PlayerOne->GetHealth() <= 0;
	}
	return false;
}

bool UGameStatusManager::GetIsADraw()
{
	if (PlayerOne != nullptr && IsValid(PlayerOne) && PlayerTwo != nullptr && IsValid(PlayerTwo))
	{
		return PlayerTwo->GetHealth() <= 0 && PlayerOne->GetHealth() <= 0;
	}
	return false;
}

bool UGameStatusManager::HasValidStats()
{
	return PlayerOne != nullptr && IsValid(PlayerOne) && PlayerTwo != nullptr && IsValid(PlayerTwo);
}
