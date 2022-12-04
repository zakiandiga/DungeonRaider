// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TriggeredAction.h"
#include "Mover.generated.h"

UENUM(BlueprintType)
enum class MoveState : uint8
{
	STOP UMETA(DisplayName="STOP"),
	OPENING UMETA(DisplayName="OPENING"),
	CLOSING UMETA(DisplayName="CLOSING")
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUNGEONRAIDER_API UMover : public UActorComponent, public ITriggeredAction
{
	GENERATED_BODY()	

public:	
	// Sets default values for this component's properties
	UMover();	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//Interface function
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ActionToTrigger(bool Value);

	virtual void ActionToTrigger_Implementation(bool Value) override;

private:

	UPROPERTY(VisibleAnywhere, Category="Mover")
	MoveState CurrentMoveState = MoveState::STOP;

	UPROPERTY(EditAnywhere, Category="Mover")
	FVector MoveDirection;

	UPROPERTY(EditAnywhere, Category="Mover")
	float MoveSpeed = 50;

	UPROPERTY(EditAnywhere, Category="Mover")
	float MoveDistance;

	UPROPERTY(EditAnywhere, Category="Mover")
	float MoveDuration; //will use lerp to move

	UPROPERTY(VisibleAnywhere, Category="Mover")
	FVector CurrentLocation;
	
	FVector ClosedLocation;
	FVector OpenedLocation;
	AActor* Owner;

	FVector GetOpenedLocation();

	float RemainingDistance(FVector& TargetLocation);

	FVector& GetTargetLocation(MoveState& SetMoveState);

	void SetCurrentMoveState(MoveState State);

	void MoveActor(const float& DeltaTime, FVector& TargetLocation);		
};


