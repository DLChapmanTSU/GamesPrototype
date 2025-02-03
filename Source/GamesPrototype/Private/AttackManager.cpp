// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackManager.h"

#include "ConductiveWall.h"
#include "StatsManager.h"

// Sets default values for this component's properties
UAttackManager::UAttackManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAttackManager::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UAttackManager::ElectricAttack(FAttackLevels levels)
{
	for (int i = 0; i < ElectricTargets.Num(); i++)
	{
		if (ElectricTargets[i] != nullptr)
		{
			AConductiveWall* wall = Cast<AConductiveWall>(ElectricTargets[i]);
			if (wall != nullptr && IsValid(wall))
			{
				UE_LOG(LogTemp, Warning, TEXT("I AM A WALL! OUCH!"));
			}
			else
			{
				APawn* playerPawn = Cast<APawn>(ElectricTargets[i]);
				if (playerPawn != nullptr && IsValid(playerPawn))
				{
					UE_LOG(LogTemp, Warning, TEXT("I AM A PLAYER! DEAL DAMAGE TO ME!"));

					UStatsManager* statsManager = Cast<UStatsManager>(playerPawn->GetComponentByClass(UStatsManager::StaticClass()));

					if (statsManager != nullptr && IsValid(statsManager))
					{
						statsManager->DealDamage(levels.electricity * 2);
						statsManager->AddRadiation(levels.radiation);
					}
				}
			}
		}
	}
}

void UAttackManager::RadioactiveAttack(FAttackLevels levels)
{
	AActor* owner = Cast<AActor>(GetOwner());
	if (owner && IsValid(RadioactiveActor))
	{
		const FName TraceTag("RadioTag");

		GetWorld()->DebugDrawTraceTag = TraceTag;
		
		FVector dir = owner->GetActorForwardVector() * 500.0f;

		FHitResult hit;
		FVector start = owner->GetActorLocation();
		FVector end = owner->GetActorLocation() + dir;
		FCollisionQueryParams queryParams;
		queryParams.TraceTag = TraceTag;
		queryParams.AddIgnoredActor(owner);

		GetWorld()->LineTraceSingleByChannel(hit, start, end, ECollisionChannel::ECC_WorldStatic, queryParams);
		if (hit.IsValidBlockingHit() && IsValid(hit.GetActor()))
		{
			FActorSpawnParameters spawnParams;
			GetWorld()->SpawnActor<AActor>(RadioactiveActor, hit.ImpactPoint, FRotator(0), spawnParams);
			UE_LOG(LogTemp, Warning, TEXT("ACTOR SPAWNED"));
		}
		else
		{
			FActorSpawnParameters spawnParams;
			GetWorld()->SpawnActor<AActor>(RadioactiveActor, owner->GetActorLocation() + dir, FRotator(0), spawnParams);
			UE_LOG(LogTemp, Warning, TEXT("ACTOR SPAWNED"));
		}
	}
}

void UAttackManager::XRayAttack(FAttackLevels levels)
{
	AActor* owner = Cast<AActor>(GetOwner());
	if (owner && IsValid(RadioactiveActor))
	{
		FVector dir = owner->GetActorForwardVector();

		FHitResult hit;
		FVector start = owner->GetActorLocation();
		FVector end = owner->GetActorLocation() + dir * 1000.0f;
		FCollisionQueryParams queryParams;
		queryParams.AddIgnoredActor(owner);

		GetWorld()->LineTraceSingleByChannel(hit, start, end, ECollisionChannel::ECC_WorldDynamic, queryParams);
		if (hit.IsValidBlockingHit() && IsValid(hit.GetActor()))
		{
			UE_LOG(LogTemp, Warning, TEXT("PLAYER HIT"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("WHIFF"));
		}
	}
}

// Called every frame
void UAttackManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	CurrentNormalAttackTimer += DeltaTime;

	// ...
}

void UAttackManager::AddResource(int type)
{
	if (type < 0 || type >= 3)
		return;

	Resources.Add(type);
	
	if (Resources.Num() > 5)
		Resources.RemoveAt(0, 1);
}

void UAttackManager::StartAttack()
{
	if (Resources.Num() == 0)
		return;

	FAttackLevels levels;
	levels.electricity = 0;
	levels.radiation = 0;
	levels.xray = 0;
	for (int i = 0; i < Resources.Num(); i++)
	{
		if (i >= 5)
			break;
		
		switch (Resources[i])
		{
		case 0:
			levels.electricity++;
			break;
		case 1:
			levels.radiation++;
			break;
		case 2:
			levels.xray++;
			break;
		default:
			break;
		}
	}

	switch (Resources[0])
	{
	case 0:
		ElectricAttack(levels);
		break;
	case 1:
		RadioactiveAttack(levels);
		break;
	case 2:
		XRayAttack(levels);
		break;
	default:
		break;
	}

	Resources.Empty();
}

void UAttackManager::BasicAttack()
{
	UE_LOG(LogTemp, Warning, TEXT("I AM THE BASIC ATTACK"));

	if (CurrentNormalAttackTimer < NormalAttackTimer)
		return;

	CurrentNormalAttackTimer = 0.0f;
	
	FActorSpawnParameters spawnParams;
	GetWorld()->SpawnActor<AActor>(NormalAttackActor, GetOwner()->GetActorLocation() + (GetOwner()->GetActorForwardVector() * 100.0f), GetOwner()->GetActorRotation(), spawnParams);
}

void UAttackManager::SetElectricTargets(TArray<AActor*> targets)
{
	ElectricTargets = targets;
}
