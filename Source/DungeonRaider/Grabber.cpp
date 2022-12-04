// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "Components/SceneComponent.h"
#include "Engine/World.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"


UGrabber::UGrabber()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
}

void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(PhysicsHandle && bIsGrabbingObject)
	{
		MoveGrabbedObject();		
	}
}

void UGrabber::Grab()
{
	FHitResult HitResult;
	bool HitSomething = GrabbableObjectInReach(HitResult);
	
	if(HitSomething && !bIsGrabbingObject)
	{
		GrabbedActor = HitResult.GetActor();
		GrabbedActor->Tags.Add("AtHand");

		UPrimitiveComponent* HitComponent = HitResult.GetComponent();
		if(PhysicsHandle)
		{
			HitComponent->SetSimulatePhysics(true);
			HitComponent->WakeAllRigidBodies();
			PhysicsHandle->GrabComponentAtLocationWithRotation(HitComponent, NAME_None, HitResult.ImpactPoint, GetComponentRotation());

			bIsGrabbingObject = true;
		}
	}
}

void UGrabber::Drop()
{
	if(PhysicsHandle &&bIsGrabbingObject)
	{
		PhysicsHandle->GetGrabbedComponent()->WakeAllRigidBodies();
		PhysicsHandle->ReleaseComponent();
		GrabbedActor->Tags.Remove("AtHand");
		GrabbedActor = nullptr;
		bIsGrabbingObject = false;
	}
}

void UGrabber::MoveGrabbedObject()
{
	FVector TargetLocation = GetOwner()->GetActorLocation() + GetForwardVector() * GrabbedObjectDistance;
	PhysicsHandle->SetTargetLocationAndRotation(TargetLocation, GetComponentRotation());
}

bool UGrabber::GrabbableObjectInReach(FHitResult& OutHitResult) const
{
	FVector Start = GetComponentLocation();
	FVector End = Start + GetForwardVector() * MaxGrabOffset;
	FCollisionShape CollisionShape = FCollisionShape::MakeSphere(Radius);

	return GetWorld()->SweepSingleByChannel(OutHitResult, Start, End, FQuat::Identity, ECC_GameTraceChannel2, CollisionShape);
}


