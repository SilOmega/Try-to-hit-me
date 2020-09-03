// Fill out your copyright notice in the Description page of Project Settings.


#include "AIC_Enemy2.h"
#include "BaseCharacter.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "TimerManager.h"
#include <Runtime\Engine\Classes\Engine\Engine.h>
#include "ConstructorHelpers.h"


AAIC_Enemy2::AAIC_Enemy2()
{
	SetGenericTeamId(FGenericTeamId(1));

	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception Component")));

	// Create and configure sight sense
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	SightConfig->SightRadius = 500.0f;
	SightConfig->LoseSightRadius = 700.0f;
	SightConfig->PeripheralVisionAngleDegrees = 90.0f;
	SightConfig->DetectionByAffiliation.DetectAllFlags();
	SightConfig->SetMaxAge(0.0f);

	// Setup perception component
	GetPerceptionComponent()->ConfigureSense(*SightConfig);
	GetPerceptionComponent()->SetSenseEnabled(SightConfig->GetSenseImplementation(), true);

	// Create Behaviour Tree, Blackborad and Behaviour Tree Component
	BehaviourComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("Behaviour Tree"));
	Blackboard = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard Comp"));
	
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BehaviourTObj(TEXT("/Game/AI/BT_Enemy.BT_Enemy"));
	BehaviourT = BehaviourTObj.Object;

	if (Blackboard == nullptr)
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, "Null");
	

}

void AAIC_Enemy2::BeginPlay()
{
	Super::BeginPlay();

	if (GetPerceptionComponent()) {
		GetAIPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &AAIC_Enemy2::OnTargetPerceptionUpdated);
	}

	if (BehaviourT != nullptr) {
		RunBehaviorTree(BehaviourT);
	}
	else
		return;

	Blackboard->InitializeBlackboard(*BehaviourT->BlackboardAsset);

	Blackboard->SetValueAsInt("Health%", 100);

}

void AAIC_Enemy2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/* Update Blackborad target location */
	if (Stimulus.GetAge() == 0 && Stimulus.WasSuccessfullySensed()) {

		AActor* target = StaticCast<AActor*>(Blackboard->GetValueAsObject(TEXT("TargetActor")));

		if(target != nullptr)		
			Blackboard->SetValueAsVector(TEXT("TargetLocation"), target->GetActorLocation());
	}
	else
	{
		Blackboard->SetValueAsBool(TEXT("bHasLineOfSight"), false);
	}

}

void AAIC_Enemy2::OnTargetPerceptionUpdated(AActor* SensedActor, FAIStimulus Stim)
{

	Stimulus = Stim;
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, "Perceived");
	// Check if sensed actor is the player
	if (SensedActor->ActorHasTag(TEXT("Player"))) {
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, "Player");
		
		if (Stimulus.WasSuccessfullySensed()) {
			// Refresh Sight key timer
			LooseSightTimerHandler.Invalidate();
			// Enemy has sight of the player and updates related parameters
			Blackboard->SetValueAsBool(TEXT("bHasLineOfSight"), true);
			Blackboard->SetValueAsObject(TEXT("TargetActor"), SensedActor);
			Blackboard->SetValueAsVector(TEXT("TargetLocation"), SensedActor->GetActorLocation());
		}
		else
		{
			// Set a timer to loose sight after some seconds
			GetWorldTimerManager().SetTimer(LooseSightTimerHandler, this, &AAIC_Enemy2::LooseSight, LooseLineOfSightTimer, false);
		}
	}
	else
	{
		printf("Not a Player");
	}


}

void AAIC_Enemy2::LooseSight() {

	Blackboard->SetValueAsObject(TEXT("TargetActor"), nullptr);
}



