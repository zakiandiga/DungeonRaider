// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "TriggeredAction.h"
#include "TriggerArea.generated.h"


class UBoxComponent;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DUNGEONRAIDER_API UTriggerArea : public UBoxComponent
{
	GENERATED_BODY()
	
public:

	UTriggerArea();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;	

	UFUNCTION(BlueprintCallable)
	void SetTriggeredInterface(AActor* TriggeredActorToSet);

private:
	UPROPERTY(EditAnywhere, Category="Door Status")
	FName UnlockingObjectTag = "Default";

	ITriggeredAction* TriggeredAction;

	UPROPERTY(EditAnywhere, Category="Door Status")
	bool bSnapDroppedActor = true;
	
	void SnapActor(UPrimitiveComponent* ActorPrimitive);

	AActor* AcceptableActor() const;

	UFUNCTION()
	void TriggerActionOnSetActor();
};
