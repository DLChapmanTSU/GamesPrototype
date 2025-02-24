// Fill out your copyright notice in the Description page of Project Settings.


#include "RadiationBounce.h"
#include "RadiationSplashBase.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
ARadiationBounce::ARadiationBounce()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = Mesh;
}

// Called when the game starts or when spawned
void ARadiationBounce::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARadiationBounce::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector diff = CurrentTargetLocation - GetActorLocation();
	if (diff.Length() <= 50.0f)
	{
		FActorSpawnParameters spawnParams;
		ARadiationSplashBase* splash = GetWorld()->SpawnActor<ARadiationSplashBase>(RadioactiveActor, CurrentTargetLocation, FRotator(0), spawnParams);
		splash->SetShockValue(ShockPower);
		CalculateNextBounceTarget();
	}

	SetActorLocation(GetActorLocation() + (GetActorForwardVector() * MovementSpeed * DeltaTime));
}

void ARadiationBounce::SetNumberOfBounces(int NewNumberOfBounces)
{
	NumberOfBounces = NewNumberOfBounces;
}

void ARadiationBounce::CalculateNextBounceTarget()
{
	if (CurrentBounces >= NumberOfBounces)
	{
		Destroy();
		return;
	}
	
	const FName TraceTag("RadioTag");

	GetWorld()->DebugDrawTraceTag = TraceTag;
		
	FVector dir = GetActorForwardVector() * 500.0f;

	FHitResult hit;
	FVector start = GetActorLocation();
	FVector end = GetActorLocation() + dir;
	FCollisionQueryParams queryParams;
	queryParams.TraceTag = TraceTag;

	GetWorld()->LineTraceSingleByChannel(hit, start, end, ECollisionChannel::ECC_WorldStatic, queryParams);
	if (hit.IsValidBlockingHit() && IsValid(hit.GetActor()))
	{
		CurrentTargetLocation = hit.ImpactPoint;
		CurrentTargetRotation = UKismetMathLibrary::FindLookAtRotation(hit.ImpactPoint, hit.ImpactPoint + FMath::GetReflectionVector(dir, hit.ImpactNormal));
	}
	else
	{
		CurrentTargetLocation = GetActorLocation() + dir;
		CurrentTargetRotation = GetActorRotation();
	}

	CurrentBounces++;
	SetActorRotation(UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), CurrentTargetLocation));
}

void ARadiationBounce::SetShockPower(int NewShockPower)
{
	ShockPower = NewShockPower;
}

