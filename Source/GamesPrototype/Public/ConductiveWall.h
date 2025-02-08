// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttackManager.h"
#include "ElectricTree.h"
#include "GameFramework/Actor.h"
#include "ConductiveWall.generated.h"

UCLASS()
class GAMESPROTOTYPE_API AConductiveWall : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AConductiveWall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UBoxComponent* BoxComponent;

	TArray<AActor*> ElectricTargets;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ElectricDamage(FAttackLevels levels, UElectricTree* tree, int layer);
	UFUNCTION()
	void ActorEnterRange(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
									UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void ActorExitRange(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
									UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
