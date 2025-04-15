// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectPoolingSystem.h"

void UObjectPoolingSystem::AddToPool(TSubclassOf<AActor> ObjectType)
{
	if (!ObjectPool.Contains(ObjectType))
	{
		ObjectPool.Add(ObjectType);
		for (int i = 0; i < 50; i++)
		{
			AActor* object = GetWorld()->SpawnActor(ObjectType);
			object->SetActorTickEnabled(false);
			ObjectPool[ObjectType].Add(object);
		}
	}
}

AActor* UObjectPoolingSystem::FetchFromPool(TSubclassOf<AActor> ObjectType)
{
	if (ObjectPool.Contains(ObjectType))
	{
		for (int i = 0; i < ObjectPool[ObjectType].Num(); i++)
		{
			if (ObjectPool[ObjectType][i] != nullptr && IsValid(ObjectPool[ObjectType][i]))
			{
				if (!ObjectPool[ObjectType][i]->IsActorTickEnabled())
				{
					ObjectPool[ObjectType][i]->SetActorTickEnabled(true);
					return ObjectPool[ObjectType][i];
				}
			}
		}
	}
	return nullptr;
}
