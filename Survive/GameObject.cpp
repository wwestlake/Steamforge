// Fill out your copyright notice in the Description page of Project Settings.

#include "GameObject.h"

// Sets default values
AGameObject::AGameObject()
{
	PrimaryActorTick.bCanEverTick = true;

	InstanceContext = EObjectInstanceContext::Placed;
	Weight = 1.0f;
}

// Called when the game starts or when spawned
void AGameObject::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGameObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

