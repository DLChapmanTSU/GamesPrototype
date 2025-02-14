// Fill out your copyright notice in the Description page of Project Settings.


#include "ConductiveWall.h"

#include "StatsManager.h"


// Sets default values
AConductiveWall::AConductiveWall()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
	RootComponent = BoxComponent;
	
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AConductiveWall::ActorEnterRange);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &AConductiveWall::ActorExitRange);
}

// Called when the game starts or when spawned
void AConductiveWall::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called every frame
void AConductiveWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TArray<UPrimitiveComponent*> OverlappingComponents;
	BoxComponent->GetOverlappingComponents(OverlappingComponents);

	for (UPrimitiveComponent* OverlappingComponent : OverlappingComponents)
	{
		if (OverlappingComponent != nullptr || IsValid(OverlappingComponent))
		{
			if (!OverlappingComponent->ComponentTags.Contains(FName("CollisionIgnore")))
			{
				ElectricTargets.AddUnique(OverlappingComponent->GetOwner());
			}
		}
	}
}

void AConductiveWall::ElectricDamage(FAttackLevels levels, UElectricTree* tree, int layer)
{
	UE_LOG(LogTemp, Warning, TEXT("Wall Shocked"));

	for (int i = 0; i < ElectricTargets.Num(); i++)
	{
		if (ElectricTargets[i] != nullptr)
		{
			if (tree->IsActorVisited(ElectricTargets[i]))
				continue;
			
			if (ElectricTargets[i]->GetUniqueID() == levels.owner)
				continue;
			AConductiveWall* wall = Cast<AConductiveWall>(ElectricTargets[i]);
			if (wall != nullptr && IsValid(wall))
			{
				UE_LOG(LogTemp, Warning, TEXT("I AM A WALL! OUCH!"));
				tree->AddActorAtLayer(ElectricTargets[i], layer);
				//wall->ElectricDamage(levels, tree, layer);
			}
			else
			{
				APawn* playerPawn = Cast<APawn>(ElectricTargets[i]);
				if (playerPawn != nullptr && IsValid(playerPawn))
				{
					UE_LOG(LogTemp, Warning, TEXT("I AM A PLAYER! DEAL DAMAGE TO ME!"));

					/*UStatsManager* statsManager = Cast<UStatsManager>(playerPawn->GetComponentByClass(UStatsManager::StaticClass()));

					if (statsManager != nullptr && IsValid(statsManager))
					{
						statsManager->DealDamage(levels.electricity * 2);
						statsManager->AddRadiation(levels.radiation);
					}*/

					tree->AddActorAtLayer(ElectricTargets[i], layer);
				}
			}
		}
	}
	
	TArray<AActor*> layerActors = tree->GetVisitedActors(layer);
	
	for (int i = 0; i < layerActors.Num(); i++)
	{
		if (layerActors[i] != nullptr)
		{
			if (layerActors[i]->GetUniqueID() == levels.owner)
				continue;
			AConductiveWall* wall = Cast<AConductiveWall>(layerActors[i]);
			if (wall != nullptr && IsValid(wall))
			{
				wall->ElectricDamage(levels, tree, layer + 1);
			}
		}
	}
}

void AConductiveWall::ActorEnterRange(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != nullptr)
	{
		APawn* playerPawn = Cast<APawn>(OtherActor);
		if (playerPawn != nullptr && IsValid(playerPawn) && !OtherComp->ComponentHasTag("CollisionIgnore"))
		{
			ElectricTargets.AddUnique(OtherActor);
		}
		else
		{
			AConductiveWall* wall = Cast<AConductiveWall>(OtherActor);
			if (wall != nullptr && IsValid(wall) && !OtherComp->ComponentHasTag("CollisionIgnore"))
			{
				ElectricTargets.AddUnique(OtherActor);
			}
		}
	}
}

void AConductiveWall::ActorExitRange(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor != nullptr)
	{
		APawn* playerPawn = Cast<APawn>(OtherActor);
		if (playerPawn != nullptr && IsValid(playerPawn) && !OtherComp->ComponentHasTag("CollisionIgnore"))
		{
			ElectricTargets.Remove(OtherActor);
		}
		else
		{
			AConductiveWall* wall = Cast<AConductiveWall>(OtherActor);
			if (wall != nullptr && IsValid(wall) && !OtherComp->ComponentHasTag("CollisionIgnore"))
			{
				ElectricTargets.Remove(OtherActor);
			}
		}
	}
}

