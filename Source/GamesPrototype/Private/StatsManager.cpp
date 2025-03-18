// Fill out your copyright notice in the Description page of Project Settings.


#include "StatsManager.h"

#include "AttackManager.h"
#include "Components/ArrowComponent.h"
#include "Components/SceneComponent.h"


// Sets default values for this component's properties
UStatsManager::UStatsManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UStatsManager::BeginPlay()
{
	Super::BeginPlay();

	// ...
	CurrentHealth = MaxHealth;
}


// Called every frame
void UStatsManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (CurrentRadiation <= 0)
	{
		CurrentRadiationTickTime = 0.0f;
		return;
	}

	CurrentRadiationTickTime += DeltaTime;

	if (CurrentRadiationTickTime >= RadiationTickTime)
	{
		if (CurrentRadiation > 0)
		{
			CurrentHealth--;
			CurrentRadiation--;

			//if (CurrentHealth <= 0)
			//	GetOwner()->SetHidden(true);
		}

		CurrentRadiationTickTime = 0.0f;
	}

	

	// ...
}

int UStatsManager::GetHealth()
{
	return CurrentHealth;
}

int UStatsManager::GetMaxHealth()
{
	return MaxHealth;
}

int UStatsManager::GetRadiation()
{
	return CurrentRadiation;
}

int UStatsManager::GetMaxRadiation()
{
	return MaxRadiation;
}

void UStatsManager::DealDamage(int damage)
{
	int finalDamage = damage;
	if (ArmourValue > 0)
	{
		finalDamage = (damage / 3) * 2;
		if (finalDamage == 0)
			ArmourValue -= 1;
		else
			ArmourValue -= finalDamage;
	}
	
	CurrentHealth -= finalDamage;
	if (CurrentRadiation > 0)
	{
		CurrentHealth -= CurrentRadiation * 2;
		CurrentRadiation = 0;
	}
	//UE_LOG(LogTemp, Warning, TEXT("OUCH!"));
	if (CurrentHealth <= 0)
	{
		TArray<UStaticMeshComponent*> comps;
		GetOwner()->GetComponents<UStaticMeshComponent>(comps);

		for (int i = 0; i < comps.Num(); i++)
		{
			comps[i]->SetVisibility(false);
			comps[i]->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}

		TArray<UArrowComponent*> arrows;
		GetOwner()->GetComponents<UArrowComponent>(arrows);

		for (int i = 0; i < comps.Num(); i++)
		{
			arrows[i]->SetVisibility(false);
		}
	}
}

void UStatsManager::AddRadiation(int radiation)
{
	CurrentRadiation += radiation;
	//UE_LOG(LogTemp, Warning, TEXT("THAT BURNS!"));
	if (CurrentRadiation > MaxRadiation)
		CurrentRadiation = MaxRadiation;
}

void UStatsManager::HealHealth(int health)
{
	CurrentHealth += health;
	if (CurrentHealth > MaxHealth)
		CurrentHealth = MaxHealth;
}

void UStatsManager::HealRadiation(int radiation)
{
	CurrentRadiation -= radiation;
	if (CurrentRadiation < 0)
		CurrentRadiation = 0;
}

void UStatsManager::SetArmourBuff()
{
	ArmourValue = 10;
}

int UStatsManager::GetArmourValue()
{
	return ArmourValue;
}

void UStatsManager::ResetPlayer()
{
	CurrentHealth = MaxHealth;
	CurrentRadiation = 0;
	CurrentRadiationTickTime = 0.0f;
	if (GetOwner() != nullptr && IsValid(GetOwner()))
	{
		UActorComponent* attackComp = GetOwner()->GetComponentByClass(UAttackManager::StaticClass());

		if (attackComp != nullptr && IsValid(attackComp))
		{
			UAttackManager* attackManager = Cast<UAttackManager>(attackComp);
			if (attackManager != nullptr && IsValid(attackManager))
			{
				attackManager->ResetResources();
			}
		}

		TArray<UStaticMeshComponent*> comps;
		GetOwner()->GetComponents<UStaticMeshComponent>(comps);

		for (int i = 0; i < comps.Num(); i++)
		{
			comps[i]->SetVisibility(true);
			comps[i]->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		}

		TArray<UArrowComponent*> arrows;
		GetOwner()->GetComponents<UArrowComponent>(arrows);

		for (int i = 0; i < comps.Num(); i++)
		{
			arrows[i]->SetVisibility(true);
		}
	}
}

