// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStatTracker.h"
# include "Net/UnrealNetwork.h"
# include "Engine/Engine.h"
#include "TimerManager.h"

// Sets default values for this component's properties
UPlayerStatTracker::UPlayerStatTracker()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	Health = 100;
	Energy = 100;  

	DrainPerSlowTick = 1;

	// ...
}


// Called when the game starts
void UPlayerStatTracker::BeginPlay()
{
	Super::BeginPlay();

	SetIsReplicated(true);  // tell UE to keep us in sync with the server

	GetWorld()->GetTimerManager().SetTimer(SlowTicker, this, &UPlayerStatTracker::SlowTick, 1.0f, true);  // set our timer to run once a second

	// we can pause this later with something like:
	// GetWorld()->GetTimerManager().PauseTimer(SlowTicker);



}


void UPlayerStatTracker::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Replicate to everyone
	DOREPLIFETIME(UPlayerStatTracker, Health);
}




// Called by server to drain energy
bool UPlayerStatTracker::SDrain_Validate(int Value)
{
	return false;
}


void UPlayerStatTracker::SDrain_Implementation(int Value)
{
	
	if (GetOwnerRole() == ROLE_Authority) {
		Drain(Value);
	}
}


// Called by server to lower health
bool UPlayerStatTracker::SHurt_Validate(int Value)
{
	return false;
}


void UPlayerStatTracker::SHurt_Implementation(int Value)
{

	if (GetOwnerRole() == ROLE_Authority) {
		Hurt(Value);
	}
}







// Called every frame
void UPlayerStatTracker::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPlayerStatTracker::Hurt(int Value)
{
	if (GetOwnerRole() < ROLE_Authority)  // something client side wants to cause damage, pass it to the server to validate
	{
		SHurt(Value);
	}
	else
	{
		// server side, we can just change the value
		Health -= Value;
	}

}

void UPlayerStatTracker::Drain(int Value)
{
	if (GetOwnerRole() < ROLE_Authority)
	{
		SDrain(Value);
	}
	else
	{
		// server side, we can just change the value
		Energy -= Value;
	}
}

void UPlayerStatTracker::SlowTick()
{
	Hurt(1);
}


int UPlayerStatTracker::getHealth()
{
	return Health;
}

int UPlayerStatTracker::getEnergy()
{
	return Energy;
}