// Fill out your copyright notice in the Description page of Project Settings.


#include "ElectricTree.h"

#include "StatsManager.h"

bool UElectricTree::IsActorVisited(AActor* Actor)
{
	for (int i = 0; i < VisitedActors.Num(); i++)
	{
		if (VisitedActors[i].Contains(Actor))
		{
			return true;
		}
	}

	return false;
}

void UElectricTree::AddActorAtLayer(AActor* Actor, int Layer)
{
	if (IsActorVisited(Actor))
		return;

	//VisitedActors[Layer].AddUnique(Actor);
	
	if (VisitedActors.IsValidIndex(Layer))
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
	}
}

TArray<AActor*> UElectricTree::GetVisitedActors(int Layer)
{
	if (!VisitedActors.IsValidIndex(Layer))
		return TArray<AActor*>();
	return VisitedActors[Layer];
}

void UElectricTree::DamageAllObjectsInTree(FAttackLevels levels)
{
	for (int i = 0; i < VisitedActors.Num(); i++)
	{
		for (int j = 0; j < VisitedActors[i].Num(); j++)
		{
			APawn* pawn = Cast<APawn>(VisitedActors[i][j]);
			if (pawn != nullptr && IsValid(pawn))
			{
				if (pawn->GetUniqueID() != levels.owner)
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
	}
}
