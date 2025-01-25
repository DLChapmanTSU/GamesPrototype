// Fill out your copyright notice in the Description page of Project Settings.


#include "ConductiveWall.h"


// Sets default values
AConductiveWall::AConductiveWall()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
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
}

void AConductiveWall::ElectricDamage(FAttackLevels levels)
{
	UE_LOG(LogTemp, Warning, TEXT("Wall Shocked"));
}

