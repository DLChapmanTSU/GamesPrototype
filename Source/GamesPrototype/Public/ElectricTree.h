// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttackManager.h"
#include "UObject/Object.h"
#include "ElectricTree.generated.h"

/**
 * 
 */
UCLASS()
class GAMESPROTOTYPE_API UElectricTree : public UObject
{
	GENERATED_BODY()

protected:
	TArray<TArray<AActor*>> VisitedActors;
public:
	bool IsActorVisited(AActor* Actor);
	void AddActorAtLayer(AActor* Actor, int Layer);
	TArray<AActor*> GetVisitedActors(int Layer);
	void DamageAllObjectsInTree(FAttackLevels levels);
};
