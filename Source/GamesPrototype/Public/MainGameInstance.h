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

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ObjectPool")
		UObjectPoolingSystem* PoolingSystem;
	
	UMainGameInstance();
};
