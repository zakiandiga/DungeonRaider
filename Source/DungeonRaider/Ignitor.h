// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TriggeredAction.h"
#include "Ignitor.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUNGEONRAIDER_API UIgnitor : public UActorComponent, public ITriggeredAction
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UIgnitor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//Interface function
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ActionToTrigger(bool Value);

	UFUNCTION(BlueprintCallable)
	void AddToIgniteList(USceneComponent* ComponentsToAdd);

	virtual void ActionToTrigger_Implementation(bool Value) override;

private:

	UPROPERTY(EditAnywhere, Category="Ignitor")
	TSet<USceneComponent*> ComponentsToIgnite;

	bool bIsTurnedOn = false;

	void TurnVisible(bool ToVisible);

};
