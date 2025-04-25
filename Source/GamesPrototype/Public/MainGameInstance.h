// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ObjectPoolingSystem.h"
#include "MainGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class GAMESPROTOTYPE_API UMainGameInstance : public UGameInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ObjectPool")
		UObjectPoolingSystem* PoolingSystem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="WinCounts")
		int P1WinCount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="WinCounts")
		int P2WinCount = 0;
public:	
	UMainGameInstance();

	UFUNCTION(BlueprintCallable)
	void AddToPool(TSubclassOf<AActor> ObjectType);

	UFUNCTION(BlueprintCallable)
	AActor* FetchFromPool(TSubclassOf<AActor> ObjectType);

	UFUNCTION(BlueprintCallable)
	int GetP1Wins();

	UFUNCTION(BlueprintCallable)
	int GetP2Wins();

	UFUNCTION(BlueprintCallable)
	void ResetScores();
	
	UFUNCTION(BlueprintCallable)
	void AddP1Point();

	UFUNCTION(BlueprintCallable)
	void AddP2Point();
};
