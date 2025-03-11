// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RadiationSplashBase.h"
#include "Components/ActorComponent.h"
#include "Components/BoxComponent.h"
#include "Tazerpoint.h"
#include "RadiationBounce.h"
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
	UPROPERTY()
	int owner;
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
		TSubclassOf<AActor> NormalAttackActor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AttackSpawnables")
		TSubclassOf<AActor> TazerAttackActor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AttackSpawnables")
		TSubclassOf<ARadiationBounce>	RadioactiveActor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AttackSpawnables")
		float NormalAttackTimer = 0.5f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AttackSpawnables")
		float SpecialAttackTimer = 0.5f;

	float CurrentNormalAttackTimer = 0.0f;
	float CurrentSpeialAttackTimer = 0.0f;

	bool HasRetainBuff = false;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintCallable)
		void AddResource(int type);

	UFUNCTION(BlueprintCallable)
		void StartAttack();

	UFUNCTION(BlueprintCallable)
		void BasicAttack();

	UFUNCTION(BlueprintCallable)
		void SetElectricTargets(TArray<AActor*> targets);

	UFUNCTION(BlueprintCallable)
		TArray<int> GetResources();

	UFUNCTION(BlueprintCallable)
		void SetRetainBuff();

	UFUNCTION(BlueprintCallable)
		bool GetRetainBuff();

	void ResetResources();
};
