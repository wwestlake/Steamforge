// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameObject.generated.h"

UENUM(BlueprintType)
enum class EObjectInstanceContext : uint8
{
	Placed      UMETA(DisplayName = "Placed"),
	Inventory   UMETA(DisplayName = "Inventory"),
	Dropped     UMETA(DisplayName = "Dropped")
};

UCLASS(Blueprintable)
class SURVIVE_API AGameObject : public AActor
{
	GENERATED_BODY()

public:	
	AGameObject();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	// --- Blueprint-exposed properties ---

	// Context of this object instance
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Object")
	EObjectInstanceContext InstanceContext;

	// Display name
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Object")
	FText DisplayName;

	// Short description
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Object")
	FText Description;

	// Tags for categorization or filtering
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Object")
	TArray<FName> ObjectTags;

	// Inventory icon (optional)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Object")
	UTexture2D* Icon;

	// Weight for inventory systems
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Object")
	float Weight;

	// --- Blueprint-callable methods ---

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Object")
	 void OnPickedUp();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Object")
	 void OnDropped();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Object")
	 void OnUsed();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Object")
	 void LoadFromSave();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Object")
	 void SaveState();
};
