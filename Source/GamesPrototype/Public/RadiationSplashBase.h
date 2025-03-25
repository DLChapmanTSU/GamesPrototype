// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "RadiationSplashBase.generated.h"

UCLASS(Blueprintable)
class GAMESPROTOTYPE_API ARadiationSplashBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARadiationSplashBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true), Category="RadiationSplash")
		UStaticMeshComponent* Mesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true), Category="RadiationSplash")
		USphereComponent* Sphere;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true), Category="RadiationSplash")
		float Duration;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true), Category="RadiationSplash")
		int RadiationPerTick;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true), Category="RadiationSplash")
		float TimePerTick;

	UFUNCTION()
	void OnEnterRange(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
					   int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnExitRange(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
						  int32 OtherBodyIndex);

	void ApplyShock();

	TArray<APawn*> Pawns;
	float CurrentDeathTime = 0.0f;
	float CurrentTickTime = 0.0f;
	bool HasPerformedShock = false;
	int ShockValue = 0;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void InitialiseData(int shock, float radius);
};
