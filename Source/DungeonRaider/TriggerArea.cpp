#include "TriggerArea.h"

UTriggerArea::UTriggerArea()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UTriggerArea::BeginPlay()
{
	Super::BeginPlay();
	//OnComponentBeginOverlap.AddDynamic(this, &UTriggerArea::OverlapBegin);
}

void UTriggerArea::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);	

	AActor* UnlockingActor = AcceptableActor();	
		
	if(UnlockingActor)		
	{
		if(TriggeredAction)
		{
			TriggeredAction->ActionToTrigger_Implementation(true);
		}			

		UPrimitiveComponent* ActorPrimitive = Cast<UPrimitiveComponent>(UnlockingActor->GetRootComponent());
		if(ActorPrimitive != nullptr && !UnlockingActor->Tags.Contains("AtHand") && bSnapDroppedActor)
		{
			SnapActor(ActorPrimitive);
		}			
	}
	else
	{
		if(TriggeredAction)
		{
			TriggeredAction->ActionToTrigger_Implementation(false);
		}
		
	}
	
}


void UTriggerArea::OverlapBegin(class UPrimitiveComponent* PrimitiveComp, class AActor* Other, class UPrimitiveComponent* OtherComp, int32 OtherIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(Other->ActorHasTag(UnlockingObjectTag))
	{
		
	}
	//UE_LOG(LogTemp, Warning, TEXT("OverlapBeginHandling() CALLED! Overlapped actor: %s"), *Other->GetActorNameOrLabel());
}


void UTriggerArea::SnapActor(UPrimitiveComponent* ActorPrimitive)
{
	ActorPrimitive->SetSimulatePhysics(false);
	ActorPrimitive->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
}

AActor* UTriggerArea::AcceptableActor() const
{
	TArray<AActor*> OverlappingActors;
	GetOverlappingActors(OverlappingActors);
		
	for (AActor* Actor : OverlappingActors)
	{
		if(Actor->ActorHasTag(UnlockingObjectTag))
		{				
			return Actor;
		}
	}

	return nullptr;
}

void UTriggerArea::SetTriggeredInterface(AActor* TriggeredActorToSet)
{	
	TSet<UActorComponent*> Components = TriggeredActorToSet->GetComponents();
	for (UActorComponent* Component: Components)
	{
		TriggeredAction = Cast<ITriggeredAction>(Component);
		if(TriggeredAction)
		{
			return;
		}
	}
}