// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Engine/DataTable.h"                 // FTableRowBase
#include "GameplayTagContainer.h"
#include "ObjectManagerSubsystem.generated.h"


USTRUCT(BlueprintType)
struct FObjectDefinitionMetaData
{
    GENERATED_BODY();

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Tooltip;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Lore;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FGameplayTag> Tags;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 BuildCost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName CraftingStation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float PlacementRadius;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bCanBeUsedAsFuel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bRequiresFoundation;
};

USTRUCT(BlueprintType)
struct FObjectDefinition : public FTableRowBase
{
    GENERATED_BODY();

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName Name;  // Required by DataTable

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText DisplayName;

    // Class name to be loaded dynamically at runtime
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName ObjectClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName Category;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsPlaceable;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bHasPersistentState;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float BaseMass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 MaxStackSize;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FObjectDefinitionMetaData Meta;
};




/**
 * 
 */
UCLASS()
class STEAMFORGE_API UObjectManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
};
