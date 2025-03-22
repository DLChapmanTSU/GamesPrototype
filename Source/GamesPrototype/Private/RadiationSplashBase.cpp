// Fill out your copyright notice in the Description page of Project Settings.


#include "RadiationSplashBase.h"

#include "AttackManager.h"
#include "ConductiveWall.h"
#include "ElectricTree.h"
#include "StatsManager.h"


// Sets default values
ARadiationSplashBase::ARadiationSplashBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	RootComponent = Sphere;
	Sphere->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	Sphere->SetLineThickness(1);
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ARadiationSplashBase::OnEnterRange);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &ARadiationSplashBase::OnExitRange);
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	
}

// Called when the game starts or when spawned
void ARadiationSplashBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARadiationSplashBase::OnEnterRange(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherComp->ComponentTags.Contains(FName("CollisionIgnore")))
		return;
	APawn* pawn = Cast<APawn>(OtherActor);
	if (pawn != nullptr && IsValid(pawn))
	{
		Pawns.AddUnique(pawn);
	}
}

void ARadiationSplashBase::OnExitRange(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherComp->ComponentTags.Contains(FName("CollisionIgnore")))
		return;
	APawn* pawn = Cast<APawn>(OtherActor);
	if (pawn != nullptr && IsValid(pawn))
	{
		Pawns.Remove(pawn);
	}
}

void ARadiationSplashBase::ApplyShock()
{
	HasPerformedShock = true;

	TArray<UPrimitiveComponent*> OverlappedComponents;
	Sphere->GetOverlappingComponents(OverlappedComponents);
	TArray<AActor*> OverlappedActors;
	for (UPrimitiveComponent* OverlappedComp : OverlappedComponents)
	{
		if (OverlappedComp != nullptr || IsValid(OverlappedComp))
		{
			if (!OverlappedComp->ComponentTags.Contains(FName("CollisionIgnore")))
			{
				OverlappedActors.AddUnique(OverlappedComp->GetOwner());
			}
		}
	}
	FAttackLevels levels;
	levels.electricity = ShockValue;
	levels.radiation = 0;
	levels.xray = 0;
	levels.owner = -1;

	UElectricTree* electricTree = NewObject<UElectricTree>();
	for (int i = 0; i < OverlappedActors.Num(); i++)
	{
		if (OverlappedActors[i] != nullptr)
		{
			if (electricTree->IsActorVisited(OverlappedActors[i]))
				continue;
			
			AConductiveWall* wall = Cast<AConductiveWall>(OverlappedActors[i]);
			if (wall != nullptr && IsValid(wall))
			{
				UE_LOG(LogTemp, Warning, TEXT("I AM A WALL! OUCH!"));
				electricTree->AddActorAtLayer(OverlappedActors[i], 0);
				//wall->ElectricDamage(levels, electricTree, 0);
			}
			else
			{
				APawn* playerPawn = Cast<APawn>(OverlappedActors[i]);
				if (playerPawn != nullptr && IsValid(playerPawn))
				{
					UE_LOG(LogTemp, Warning, TEXT("I AM A PLAYER! DEAL DAMAGE TO ME!"));

					/*UStatsManager* statsManager = Cast<UStatsManager>(playerPawn->GetComponentByClass(UStatsManager::StaticClass()));

					if (statsManager != nullptr && IsValid(statsManager))
					{
						statsManager->DealDamage(levels.electricity * 2);
						statsManager->AddRadiation(levels.radiation);
					}*/

					electricTree->AddActorAtLayer(OverlappedActors[i], 0);
				}
			}
		} 
	}

	TArray<AActor*> layerActors = electricTree->GetVisitedActors(0);
	
	for (int i = 0; i < layerActors.Num(); i++)
	{
		if (layerActors[i] != nullptr)
		{
			AConductiveWall* wall = Cast<AConductiveWall>(layerActors[i]);
			if (wall != nullptr && IsValid(wall))
			{
				wall->ElectricDamage(levels, electricTree, 1);
			}
			else
			{
				APawn* playerPawn = Cast<APawn>(layerActors[i]);
				if (playerPawn != nullptr && IsValid(playerPawn))
				{
					UStatsManager* statsManager = Cast<UStatsManager>(playerPawn->GetComponentByClass(UStatsManager::StaticClass()));

					if (statsManager != nullptr && IsValid(statsManager))
					{
						//statsManager->DealDamage(levels.electricity * 2);
						//statsManager->AddRadiation(levels.radiation);
					}
				}
			}
		}
	}

	//layerActors.Empty();
	electricTree->DamageAllObjectsInTree(levels);
	
	/*if (Pawns.Num() > 0)
	{
		for (int i = 0; i< Pawns.Num(); i++)
		{
			if (Pawns[i] != nullptr && IsValid(Pawns[i]))
			{
				UStatsManager* manager = Cast<UStatsManager>(Pawns[i]->GetComponentByClass(UStatsManager::StaticClass()));
				if (manager != nullptr && IsValid(manager))
				{
					manager->DealDamage(ShockValue);
				}
			}
		}
	}*/
}

// Called every frame
void ARadiationSplashBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!HasPerformedShock)
	{
		ApplyShock();
	}

	if (CurrentTickTime >= TimePerTick)
	{
		for (int i = 0; i < Pawns.Num(); i++)
		{
			if (Pawns[i] != nullptr && IsValid(Pawns[i]))
			{
				UStatsManager* stats = Cast<UStatsManager>(Pawns[i]->GetComponentByClass(UStatsManager::StaticClass()));

				if (stats != nullptr && IsValid(stats))
				{
					stats->AddRadiation(RadiationPerTick);
				}
			}
		}

		CurrentTickTime = 0.0f;
	}

	CurrentDeathTime += DeltaTime;
	CurrentTickTime += DeltaTime;

	if (CurrentDeathTime >= Duration)
		Destroy();
}

void ARadiationSplashBase::InitialiseData(int shock, float radius)
{
	ShockValue = shock;
	Sphere->SetSphereRadius(radius);
	Mesh->SetWorldScale3D(FVector((radius / 100.0f) * 2.0f, (radius / 100.0f) * 2.0f, 0.05f));
}

