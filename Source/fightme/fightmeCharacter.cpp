

#include "fightmeCharacter.h"

#include "MyCharacterMovementComponent.h"

//////////////////////////////////////////////////////////////////////////
// Base Character to set our custom movement component

AfightmeCharacter::AfightmeCharacter(const class FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer.SetDefaultSubobjectClass<UMyCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{

	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AfightmeCharacter::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AfightmeCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AfightmeCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UMyCharacterMovementComponent* AfightmeCharacter::GetMyMovementComponent() const
{
	return static_cast<UMyCharacterMovementComponent*>(GetCharacterMovement());
}
