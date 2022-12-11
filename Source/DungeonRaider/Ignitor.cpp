// Fill out your copyright notice in the Description page of Project Settings.


#include "Ignitor.h"
#include "Components/ActorComponent.h"
#include "Components/SceneComponent.h"



// Sets default values for this component's properties
UIgnitor::UIgnitor()
{
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UIgnitor::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UIgnitor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UIgnitor::TurnVisible(bool ToVisible)
{
	for (USceneComponent* Component : ComponentsToIgnite)
	{
		Component->SetVisibility(true);		
	}
}

void UIgnitor::AddToIgniteList(USceneComponent* ComponentsToAdd)
{
	ComponentsToIgnite.Add(ComponentsToAdd);
	
}

void UIgnitor::ActionToTrigger_Implementation(bool TriggerValue)
{
	if (!TriggerValue) return;
	if (bIsTurnedOn) return;	

	bIsTurnedOn = true;
	TurnVisible(bIsTurnedOn);
}
