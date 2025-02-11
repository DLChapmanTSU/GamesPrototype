// Fill out your copyright notice in the Description page of Project Settings.


#include "Tazerpoint.h"

// Sets default values
ATazerpoint::ATazerpoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATazerpoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATazerpoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

