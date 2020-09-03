// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "Perception/AIPerceptionSystem.h"
#include "Perception/AISense_Sight.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TeamID = FGenericTeamId(0);
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

/* Calculate health applying incoming delta and update isAlive status*/
void ABaseCharacter::CalculateHealth(int Delta)
{
	currentHealth = FMath::Clamp<float>(currentHealth + Delta, 0, maxHealth);

	if (currentHealth == 0)
		isDead = true;
}

void ABaseCharacter::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	currentHealth = maxHealth;

	Super::PostEditChangeProperty(PropertyChangedEvent);
}

FGenericTeamId ABaseCharacter::GetGenericTeamId() const
{
	return TeamID;
}
