// Fill out your copyright notice in the Description page of Project Settings.


#include "Mover.h"
#include "Components/ActorComponent.h"
#include "Math/UnrealMathUtility.h"



// Sets default values for this component's properties
UMover::UMover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}

void UMover::BeginPlay()
{
	Super::BeginPlay();
	
	ClosedLocation = GetOwner()->GetActorLocation();
	OpenedLocation = GetOpenedLocation();
}

void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(CurrentMoveState != MoveState::STOP)
	{
		MoveActor(DeltaTime, GetTargetLocation(CurrentMoveState));
	}
}

void UMover::MoveActor(const float& DeltaTime, FVector& TargetLocation)
{	
	CurrentLocation = GetOwner()->GetActorLocation();
	FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, MoveSpeed);
	GetOwner()->SetActorLocation(NewLocation);

	if(RemainingDistance(TargetLocation) <= 0)
	{
		SetCurrentMoveState(MoveState::STOP);
	}
}

FVector& UMover::GetTargetLocation(MoveState& SetMoveState)
{
	if(SetMoveState == MoveState::OPENING)
	{
		return OpenedLocation;
	}
	else if(SetMoveState == MoveState::CLOSING)
	{
		return ClosedLocation;
	}

	return CurrentLocation;
}

void UMover::SetCurrentMoveState(MoveState State)
{
	CurrentMoveState = State;
}

float UMover::RemainingDistance(FVector& TargetLocation)
{
	return FVector::Dist(CurrentLocation, TargetLocation);
}

FVector UMover::GetOpenedLocation()
{
	return ClosedLocation + (MoveDirection * MoveDistance);
}

//Interface implementation
void UMover::ActionToTrigger_Implementation(bool Value)
{
	CurrentMoveState = Value ? MoveState::OPENING : MoveState::CLOSING;
}
