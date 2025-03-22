// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackManager.h"

#include "ConductiveWall.h"
#include "StatsManager.h"
#include "Kismet/KismetSystemLibrary.h"

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
	//Trace stuff
	TArray<AActor*> FoundActors;
	TArray<AActor*> IgnoredActors;
	IgnoredActors.Add(GetOwner());
	FVector StartLocation = GetOwner()->GetActorLocation();
	FVector EndLocation = GetOwner()->GetActorLocation() + (GetOwner()->GetActorForwardVector() * 500.0f);
	float radius = levels.electricity * 50.0f;
	TArray<FHitResult> Hit;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypesArray;
	ObjectTypesArray.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Visibility));
	ObjectTypesArray.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));
	bool bHasHit = UKismetSystemLibrary::SphereTraceMultiForObjects(GetWorld(), StartLocation, EndLocation, radius, ObjectTypesArray, false, IgnoredActors, EDrawDebugTrace::ForDuration, Hit, true);

	FActorSpawnParameters spawnParams;
	GetWorld()->SpawnActor<AActor>(TazerAttackActor, GetOwner()->GetActorLocation() + (GetOwner()->GetActorForwardVector() * 200.0f), FRotator(0) , spawnParams);

	if (!bHasHit)
		return;

	
	
	UE_LOG(LogTemp, Warning, TEXT("I AM THE GLORIOUS TAZER ATTACK"));
	
	
	 UElectricTree* electricTree = NewObject<UElectricTree>();
	for (int i = 0; i < Hit.Num(); i++)
	{
		if (Hit.IsValidIndex(i) && Hit[i].GetActor() != nullptr && IsValid(Hit[i].GetActor()))
		{
			AActor* hitActor = Hit[i].GetActor();
			
			if (electricTree->IsActorVisited(hitActor))
				continue;
			
			AConductiveWall* wall = Cast<AConductiveWall>(hitActor);
			if (wall != nullptr && IsValid(wall))
			{
				UE_LOG(LogTemp, Warning, TEXT("I AM A WALL! OUCH!"));
				electricTree->AddActorAtLayer(hitActor, 0);
				//wall->ElectricDamage(levels, electricTree, 0);
			}
			else
			{
				APawn* playerPawn = Cast<APawn>(hitActor);
				if (playerPawn != nullptr && IsValid(playerPawn))
				{
					UE_LOG(LogTemp, Warning, TEXT("I AM A PLAYER! DEAL DAMAGE TO ME!"));

					/*UStatsManager* statsManager = Cast<UStatsManager>(playerPawn->GetComponentByClass(UStatsManager::StaticClass()));

					if (statsManager != nullptr && IsValid(statsManager))
					{
						statsManager->DealDamage(levels.electricity * 2);
						statsManager->AddRadiation(levels.radiation);
					}*/
					if (playerPawn->GetUniqueID() != GetOwner()->GetUniqueID())
						electricTree->AddActorAtLayer(hitActor, 0);
				}
			}
		} 
	}

	TArray<AActor*> layerActors = electricTree->GetVisitedActors(0);
	
	for (int i = 0; i < layerActors.Num(); i++)
	{
		if (layerActors.IsValidIndex(i) && layerActors[i] != nullptr && IsValid(layerActors[i]))
		{
			FRotator Rotation(i*0.1f, i*1.0f, i*0.1f);
			AConductiveWall* wall = Cast<AConductiveWall>(layerActors[i]);
			if (wall != nullptr && IsValid(wall))
			{
				
				wall->ElectricDamage(levels, electricTree, 1);
				GetWorld()->SpawnActor<AActor>(TazerAttackActor, wall ->GetActorLocation() + (wall ->GetActorForwardVector() * 100.0f), Rotation , spawnParams);
			}
			else
			{
				APawn* playerPawn = Cast<APawn>(layerActors[i]);
				if (playerPawn != nullptr && IsValid(playerPawn))
				{
					UStatsManager* statsManager = Cast<UStatsManager>(playerPawn->GetComponentByClass(UStatsManager::StaticClass()));

					if (statsManager != nullptr && IsValid(statsManager))
					{
						statsManager->DealDamage(levels.electricity * 2);
						statsManager->AddRadiation(levels.radiation);
						GetWorld()->SpawnActor<AActor>(TazerAttackActor, playerPawn ->GetActorLocation() + (playerPawn ->GetActorForwardVector() * 100.0f), Rotation , spawnParams);
					}
				}
			}
		}
	}

	//layerActors.Empty();
	electricTree->DamageAllObjectsInTree(levels);
}

void UAttackManager::RadioactiveAttack(FAttackLevels levels)
{
	AActor* owner = Cast<AActor>(GetOwner());
	if (owner && IsValid(RadioactiveActor))
	{
		FActorSpawnParameters spawnParams;
		ARadiationBounce* splash = GetWorld()->SpawnActor<ARadiationBounce>(RadioactiveActor, owner->GetActorLocation(), owner->GetActorRotation(), spawnParams);
		splash->InitialiseData(GetOwner(), levels.radiation, levels.electricity);
		splash->CalculateNextBounceTarget();
		
		/*const FName TraceTag("RadioTag");

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
			ARadiationBounce* splash = GetWorld()->SpawnActor<ARadiationBounce>(RadioactiveActor, hit.ImpactPoint, FRotator(0), spawnParams);
			splash->SetShockPower(levels.electricity);
			splash->SetNumberOfBounces(levels.radiation);
			splash->CalculateNextBounceTarget();
			//UE_LOG(LogTemp, Warning, TEXT("ACTOR SPAWNED"));
		}
		else
		{
			FActorSpawnParameters spawnParams;
			ARadiationBounce* splash = GetWorld()->SpawnActor<ARadiationBounce>(RadioactiveActor, owner->GetActorLocation() + dir, FRotator(0), spawnParams);
			splash->SetShockPower(levels.electricity);
			splash->SetNumberOfBounces(levels.radiation);
			splash->CalculateNextBounceTarget();
			//UE_LOG(LogTemp, Warning, TEXT("ACTOR SPAWNED"));
		}*/
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
	CurrentSpeialAttackTimer += DeltaTime;

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

	if (CurrentSpeialAttackTimer < SpecialAttackTimer)
		return;

	CurrentSpeialAttackTimer = 0.0f;

	FAttackLevels levels;
	levels.electricity = 0;
	levels.radiation = 0;
	levels.xray = 0;
	levels.owner = GetOwner()->GetUniqueID();
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

	if (HasRetainBuff == true)
		HasRetainBuff = false;
	else
		Resources.Empty();
}

void UAttackManager::BasicAttack()
{
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

TArray<int> UAttackManager::GetResources()
{
	return Resources;
}

void UAttackManager::SetRetainBuff()
{
	HasRetainBuff = true;
}

bool UAttackManager::GetRetainBuff()
{
	return HasRetainBuff;
}

void UAttackManager::ResetResources()
{
	CurrentNormalAttackTimer = 0.0f;
	CurrentSpeialAttackTimer = 0.0f;
	HasRetainBuff = false;
	Resources.Empty();
	ElectricTargets.Empty();
}
