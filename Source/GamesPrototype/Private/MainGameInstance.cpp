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
