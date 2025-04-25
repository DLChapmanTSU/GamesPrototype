// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameInstance.h"

UMainGameInstance::UMainGameInstance()
{
	PoolingSystem = NewObject<UObjectPoolingSystem>();
}

void UMainGameInstance::AddToPool(TSubclassOf<AActor> ObjectType)
{
	PoolingSystem->AddToPool(ObjectType, GetWorld());
}

AActor* UMainGameInstance::FetchFromPool(TSubclassOf<AActor> ObjectType)
{
	return PoolingSystem->FetchFromPool(ObjectType);
}

int UMainGameInstance::GetP1Wins()
{
	return P1WinCount;
}

int UMainGameInstance::GetP2Wins()
{
	return P2WinCount;
}

void UMainGameInstance::ResetScores()
{
	P1WinCount = 0;
	P2WinCount = 0;
}

void UMainGameInstance::AddP1Point()
{
	P1WinCount++;
}

void UMainGameInstance::AddP2Point()
{
	P2WinCount++;
}
