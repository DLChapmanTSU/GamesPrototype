// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/BoxComponent.h"
#include "AttackManager.generated.h"

USTRUCT()
struct FAttackLevels
{
	GENERATED_BODY()
	UPROPERTY()
	int electricity;
	UPROPERTY()
	int radiation;
	UPROPERTY()
	int xray;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMESPROTOTYPE_API UAttackManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAttackManager();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void ElectricAttack(FAttackLevels levels);
	void RadioactiveAttack(FAttackLevels levels);
	void XRayAttack(FAttackLevels levels);

	TArray<int> Resources;
	TArray<AActor*> ElectricTargets;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AttackSpawnables")
		TSubclassOf<AActor>	RadioactiveActor;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintCallable)
		void AddResource(int type);

	UFUNCTION(BlueprintCallable)
		void StartAttack();

	UFUNCTION(BlueprintCallable)
		void SetElectricTargets(TArray<AActor*>& targets);
};
