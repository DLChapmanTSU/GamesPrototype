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
public:	
	UMainGameInstance();

	UFUNCTION(BlueprintCallable)
	void AddToPool(TSubclassOf<AActor> ObjectType);

	UFUNCTION(BlueprintCallable)
	AActor* FetchFromPool(TSubclassOf<AActor> ObjectType);
};
