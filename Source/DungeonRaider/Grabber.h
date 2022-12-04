// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUNGEONRAIDER_API UGrabber : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:

	virtual void BeginPlay() override;

public:	

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	UPROPERTY(EditAnywhere, Category="Grabber Raycast")
	float Radius = 30;

	UPROPERTY(EditAnywhere, Category="Grabber")
	float MaxGrabOffset = 200;

	UPROPERTY(EditAnywhere, Category="Grabber")
	float GrabbedObjectDistance = 80;

	UPROPERTY(VisibleAnywhere, Category="Grabber")
	bool bIsGrabbingObject = false;
	
	UPROPERTY(VisibleAnywhere, Category="Grabber")
	FRotator CurrentRotation;

	AActor* GrabbedActor;

	class UPhysicsHandleComponent* PhysicsHandle;

	UFUNCTION(BlueprintCallable)
	void Grab();

	UFUNCTION(BlueprintCallable)
	void Drop();

	void MoveGrabbedObject();

	bool GrabbableObjectInReach(FHitResult& OutHitResult) const;
};
