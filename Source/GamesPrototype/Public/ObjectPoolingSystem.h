// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ObjectPoolingSystem.generated.h"

/**
 * 
 */
UCLASS()
class GAMESPROTOTYPE_API UObjectPoolingSystem : public UObject
{
	GENERATED_BODY()

protected:
	TMap<TSubclassOf<AActor>, TArray<AActor*>> ObjectPool;

public:
	UFUNCTION(BlueprintCallable)
		void AddToPool(TSubclassOf<AActor> ObjectType, UWorld* World);
	
	UFUNCTION(BlueprintCallable)
		AActor* FetchFromPool(TSubclassOf<AActor> ObjectType);
};
