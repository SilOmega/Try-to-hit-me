// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UCLASS()
class FIRST_API ABaseCharacter : public ACharacter, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

	FGenericTeamId TeamID;

	virtual FGenericTeamId GetGenericTeamId() const override;

public:



	/* Health property */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Base Character")
		int maxHealth = 100;

	/* CurrentHealth property */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Base Character")
		int currentHealth = maxHealth;

	/* Character is alive */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Base Character")
		bool isDead = false;

	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	class UAIPerceptionSystem* PerceptionSystem;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/* Calculate health function */
	UFUNCTION(BlueprintCallable, Category = "Base Character")
	virtual	void CalculateHealth(int delta);

#if WITH_EDITOR

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

#endif

};
