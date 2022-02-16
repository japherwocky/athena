// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerStatTracker.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FIGHTME_API UPlayerStatTracker : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerStatTracker();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;



// SERVER FUNCTIONS to adjust health / energy
	UFUNCTION(Server, Reliable, WithValidation)
	void SDrain(int Value);
	bool SDrain_Validate(int Value);
	void SDrain_Implementation(int Value);

	UFUNCTION(Server, Reliable, WithValidation)
	void SHurt(int Value);
	bool SHurt_Validate(int Value);
	void SHurt_Implementation(int Value);




public:	
	// Called every frame, turned off with PrimaryComponentTick.bCanEverTick = false;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Hurt(int Value);
	void Drain(int Value);

	int getHealth();
	int getEnergy();




protected:

	UPROPERTY(Replicated)
	int Health;

	UPROPERTY(Replicated)
	int Energy;

	UPROPERTY(EditAnywhere, Category="S|PlayerStats")
	int DrainPerSlowTick;

	FTimerHandle SlowTicker;

	// regens and DoTs, don't run every tick
	void SlowTick();
		
};
