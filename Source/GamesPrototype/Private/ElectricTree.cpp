// Fill out your copyright notice in the Description page of Project Settings.


#include "ElectricTree.h"

#include "StatsManager.h"

bool UElectricTree::IsActorVisited(AActor* Actor)
{
	/*for (int i = 0; i < VisitedActors.Num(); i++)
	{
		if (VisitedActors.Contains(Actor))
		{
			return true;
		}
	}*/

	return VisitedActors.Contains(Actor);
}

void UElectricTree::AddActorAtLayer(AActor* Actor, int Layer)
{
	if (IsActorVisited(Actor))
		return;

	VisitedActors.AddUnique(Actor);
	
	/*if (VisitedActors.IsValidIndex(Layer))
	{
		VisitedActors[Layer].AddUnique(Actor);
	}
	else if (Layer == VisitedActors.Num())
	{
		TArray<AActor*> newActors;
		newActors.Add(Actor);
		VisitedActors.Add(newActors);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ElectricTree::AddActorAtLayer: Layer %d does not exist"), Layer);
	}*/
}

TArray<AActor*> UElectricTree::GetVisitedActors()
{
	return VisitedActors;
}

void UElectricTree::DamageAllObjectsInTree(FAttackLevels levels)
{
	for (int i = 0; i < VisitedActors.Num(); i++)
	{
		APawn* pawn = Cast<APawn>(VisitedActors[i]);
		if (pawn != nullptr && IsValid(pawn))
		{
			UStatsManager* manager = Cast<UStatsManager>(pawn->GetComponentByClass(UStatsManager::StaticClass()));

			if (manager != nullptr && IsValid(manager))
			{
				manager->DealDamage(levels.electricity * 2);
				manager->AddRadiation(levels.radiation);
			}
		}
	}
}
