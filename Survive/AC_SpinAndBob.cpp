// Fill out your copyright notice in the Description page of Project Settings.


#include "AC_SpinAndBob.h"
#include "GameFramework/Actor.h"


// Sets default values
UAC_SpinAndBobComponent::UAC_SpinAndBobComponent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryComponentTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void UAC_SpinAndBobComponent::BeginPlay()
{
	Super::BeginPlay();

	startLocation = GetOwner()->GetActorLocation();
	
}

// Called every frame
void UAC_SpinAndBobComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	GetOwner()->AddActorWorldRotation(Spin * DeltaTime);

	float time = GetOwner()->GetWorld()->GetRealTimeSeconds();
	float sine = FMath::Sin(time * BobSpeedMultiplier);
	GetOwner()->SetActorLocation(startLocation + (Bob * sine));
}

