// Fill out your copyright notice in the Description page of Project Settings.


#include "RadiationSplashBase.h"

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

// Called every frame
void ARadiationSplashBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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

