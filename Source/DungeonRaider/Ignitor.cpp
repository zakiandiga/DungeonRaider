// Fill out your copyright notice in the Description page of Project Settings.


#include "Ignitor.h"

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
		UE_LOG(LogTemp, Warning, TEXT("%s becomes visible"), *Component->GetReadableName());
		
	}
}


void UIgnitor::ActionToTrigger_Implementation(bool Value)
{
	if(Value && !bIsTurnedOn)
	{
		bIsTurnedOn = true;
		TurnVisible(bIsTurnedOn);
	}
}

void UIgnitor::AddToIgniteList(USceneComponent* ComponentsToAdd)
{
	ComponentsToIgnite.Add(ComponentsToAdd);
	
}

