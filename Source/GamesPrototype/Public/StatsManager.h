// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatsManager.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GAMESPROTOTYPE_API UStatsManager : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UStatsManager();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stats")
		int MaxHealth = 100;
	
	int CurrentHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stats")
		int MaxRadiation = 25;
	
	int CurrentRadiation = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stats")
		float RadiationTickTime = 2.0f;

	float CurrentRadiationTickTime = 0.0f;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
		int GetHealth();

	UFUNCTION(BlueprintCallable)
		int GetMaxHealth();

	UFUNCTION(BlueprintCallable)
		int GetRadiation();

	UFUNCTION(BlueprintCallable)
		int GetMaxRadiation();

	UFUNCTION(BlueprintCallable)
		void DealDamage(int damage);
	
	UFUNCTION(BlueprintCallable)
		void AddRadiation(int radiation);
	
	UFUNCTION(BlueprintCallable)
		void HealHealth(int health);

	UFUNCTION(BlueprintCallable)
		void HealRadiation(int radiation);
};
