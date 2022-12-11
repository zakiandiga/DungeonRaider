#include "TriggerArea.h"
#include "GameFramework/Actor.h"
#include "Mover.h"

UTriggerArea::UTriggerArea()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UTriggerArea::BeginPlay()
{
	Super::BeginPlay();
		
}

void UTriggerArea::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);	
		
	if (TriggeredAction == nullptr) return;

	TriggerActionOnSetActor();	
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

void UTriggerArea::TriggerActionOnSetActor()
{
	AActor* UnlockingActor = AcceptableActor();

	if (UnlockingActor == nullptr)
	{
		TriggeredAction->ActionToTrigger_Implementation(false);
		return;
	}

	TriggeredAction->ActionToTrigger_Implementation(true);	

	if (!bSnapDroppedActor) return;

	UPrimitiveComponent* ActorPrimitive = Cast<UPrimitiveComponent>(UnlockingActor->GetRootComponent());

	if (ActorPrimitive == nullptr || UnlockingActor->Tags.Contains("AtHand")) return;

	SnapActor(ActorPrimitive);	
}

void UTriggerArea::SnapActor(UPrimitiveComponent* ActorPrimitive)
{
	ActorPrimitive->SetSimulatePhysics(false);
	ActorPrimitive->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
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