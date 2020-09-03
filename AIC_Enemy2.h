// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "AIC_Enemy2.generated.h"


/**
 * 
 */
UCLASS()
class FIRST_API AAIC_Enemy2 : public AAIController
{
	GENERATED_BODY()

	/* Behaviour Tree component */
	class UBehaviorTreeComponent* BehaviourComp;

	/* Behaviour Tree */
	class UBehaviorTree* BehaviourT;

	/* Sight sense configuration */
	class UAISenseConfig_Sight* SightConfig;

	/* Time before loosing the line of sight with target */
	float LooseLineOfSightTimer = 7.0f;

	/* Loose sight time handler */
	FTimerHandle LooseSightTimerHandler;

	/* Stimulus */
	FAIStimulus Stimulus;

	/* Loose sight */
	void LooseSight();

public:

	AAIC_Enemy2();

	void BeginPlay() override;

	void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnTargetPerceptionUpdated(AActor* SensedActor, FAIStimulus Stim);

};
