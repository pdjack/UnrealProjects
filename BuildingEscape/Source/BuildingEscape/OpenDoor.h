// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"

class ATriggerVolume;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

	UPROPERTY(BlueprintAssignable)
	FDoorEvent OnOpen;

	UPROPERTY(BlueprintAssignable)
	FDoorEvent OnClose;


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
private:
	

	UPROPERTY(EditAnywhere)
	ATriggerVolume * PressurePlate = nullptr;

	//UPROPERTY(EditAnywhere)
	//AActor* ActorThatOpens = nullptr; // Remember pawn inhrerits from actor

	AActor* Owner = nullptr;

	/*float LastDoorOpenTime = 0.0f;
	
	UPROPERTY(EditAnywhere)
	float DoorOpenDurationTime = 3.0f;
*/
	float TriggerMass = 50.f;


	float GetTotalMassOfActorOnPlate();
};
