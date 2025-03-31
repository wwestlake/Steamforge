// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "StatsComponent.generated.h"


USTRUCT(BlueprintType)
struct FStatDefinitionRow : public FTableRowBase
{
	GENERATED_BODY()

	/** Unique stat identifier (used as DataTable row name) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name;

	/** Designer-facing name for UI, etc. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText DisplayName;

	/** Description of what the stat represents */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Description;

	/** Optional default max value (used at init if not overridden) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DefaultMaxValue = 100.f;
};


USTRUCT(BlueprintType)
struct FCharacterStat
{
	GENERATED_BODY()

	/** Matches Name in DataTable */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName StatID;

	/** Current raw value */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurrentValue = 0.f;

	/** Max base value (before buffs) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxValue = 100.f;

	/** Buff amount added to MaxValue */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BuffAmount = 0.f;

	/** Remaining duration (in seconds) of active buff */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BuffTimeRemaining = 0.f;

	/** Debuff amount subtracted from CurrentValue */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DebuffAmount = 0.f;

	/** Remaining duration (in seconds) of active debuff */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DebuffTimeRemaining = 0.f;

	/** Whether this stat is currently dirty (optional for UI refresh) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bDirty = false;
};



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STEAMFORGE_API UStatsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStatsComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	TArray<FCharacterStat> ConfiguredStats;

	/** Adds a new stat using a data table row and initial values */
	UFUNCTION(BlueprintCallable, Category = "Stats")
	void AddStatFromDefinition(const FStatDefinitionRow& Definition, float InitialValue, float MaxValue);
	
	/** Applies a buff to a stat by name. Returns true if successful, false if stat not found. */
	UFUNCTION(BlueprintCallable, Category = "Stats")
	bool ApplyBuff(const FName& StatName, float BuffAmount, float DurationSeconds);

	/** Applies a debuff to a stat by name. Returns true if successful, false if stat not found. */
	UFUNCTION(BlueprintCallable, Category = "Stats")
	bool ApplyDebuff(const FName& StatName, float DebuffAmount, float DurationSeconds);

	/** Sets the max value for a stat by name. Returns true if found. */
	UFUNCTION(BlueprintCallable, Category = "Stats")
	bool SetStatMax(const FName& StatName, float NewMaxValue);

	/** Sets the current value for a stat by name. Returns true if found. */
	UFUNCTION(BlueprintCallable, Category = "Stats")
	bool SetStatCurrent(const FName& StatName, float NewCurrentValue);

	/** Gets the current value of a stat by name. Returns true if successful. */
	UFUNCTION(BlueprintCallable, Category = "Stats")
	bool GetStatCurrent(const FName& StatName, float& OutCurrentValue) const;

	/** Gets the max value of a stat by name. Returns true if successful. */
	UFUNCTION(BlueprintCallable, Category = "Stats")
	bool GetStatMax(const FName& StatName, float& OutMaxValue) const;

	/** Gets the buff amount for a stat by name. Returns true if successful. */
	UFUNCTION(BlueprintCallable, Category = "Stats")
	bool GetStatBuff(const FName& StatName, float& OutBuffAmount) const;

	/** Gets the debuff amount for a stat by name. Returns true if successful. */
	UFUNCTION(BlueprintCallable, Category = "Stats")
	bool GetStatDebuff(const FName& StatName, float& OutDebuffAmount) const;

};
