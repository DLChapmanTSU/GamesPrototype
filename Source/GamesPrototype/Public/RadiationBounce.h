// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RadiationSplashBase.h"
#include "RadiationBounce.generated.h"

UCLASS(Blueprintable)
class GAMESPROTOTYPE_API ARadiationBounce : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARadiationBounce();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="RadiationBounce")
		UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="RadiationBounce")
		TSubclassOf<ARadiationSplashBase> RadioactiveActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="RadiationBounce")
		float MovementSpeed = 100.0f;
	
	int NumberOfBounces = 0;
	int CurrentBounces = 0;
	FVector CurrentTargetLocation;
	FRotator CurrentTargetRotation;
	int ShockPower = 0;
	AActor* PlayerOwner;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SetNumberOfBounces(int NewNumberOfBounces);
	void CalculateNextBounceTarget();
	void SetShockPower(int NewShockPower);
	void SetPlayerOwner(AActor* owner);
};
