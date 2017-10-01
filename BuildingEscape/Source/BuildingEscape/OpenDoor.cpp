// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"

#include "BuildingEscape.h"
#include "GameFramework/Actor.h"
#include "Engine/TriggerVolume.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Components/PrimitiveComponent.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	
	// Find the owning actor
	Owner = GetOwner();
	
	
	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("Missing ATriggerVolume"))
	}
	//ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
}







// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Poll the Trigger Volume
	// If the ActorThatOpens is in the volume
	//if (PressurePlate->IsOverlappingActor(ActorThatOpens))
	if (GetTotalMassOfActorOnPlate() > TriggerMass)
	{
		OnOpen.Broadcast();
	}
	else
	{
		OnClose.Broadcast();
	}
}

float UOpenDoor::GetTotalMassOfActorOnPlate()
{
	float TotalMass = 0.f;

	// Find all the overlapping actors
	TArray<AActor*> OverlappingActors;
	if (PressurePlate == nullptr) {	return TotalMass; }
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);

	// Iterate through adding their messes
	for (auto &Actor : OverlappingActors)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		
		UE_LOG(LogTemp, Warning, TEXT("Actor : %s"), *Actor->GetName())
	}

	if (TotalMass > 0.f)
	{
		UE_LOG(LogTemp, Warning, TEXT("Total : %f"), TotalMass)
	}

	return TotalMass;
}


