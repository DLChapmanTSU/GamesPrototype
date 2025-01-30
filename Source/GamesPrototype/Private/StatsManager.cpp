// Fill out your copyright notice in the Description page of Project Settings.


#include "StatsManager.h"


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

			if (CurrentHealth <= 0)
				GetOwner()->Destroy();
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
	CurrentHealth -= damage;
	UE_LOG(LogTemp, Warning, TEXT("OUCH!"));
	if (CurrentHealth <= 0)
		GetOwner()->Destroy();
}

void UStatsManager::AddRadiation(int radiation)
{
	CurrentRadiation += radiation;
	UE_LOG(LogTemp, Warning, TEXT("THAT BURNS!"));
	if (CurrentRadiation > MaxRadiation)
		CurrentRadiation = MaxRadiation;
}

