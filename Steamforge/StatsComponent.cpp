// Fill out your copyright notice in the Description page of Project Settings.


#include "StatsComponent.h"

// Sets default values for this component's properties
UStatsComponent::UStatsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}



// Called when the game starts
void UStatsComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UStatsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	for (FCharacterStat& Stat : ConfiguredStats)
	{
		bool bModified = false;

		// Handle buff timer
		if (Stat.BuffTimeRemaining > 0.f)
		{
			Stat.BuffTimeRemaining -= DeltaTime;
			if (Stat.BuffTimeRemaining <= 0.f)
			{
				Stat.BuffTimeRemaining = 0.f;
				Stat.BuffAmount = 0.f;
				bModified = true;
			}
		}

		// Handle debuff timer
		if (Stat.DebuffTimeRemaining > 0.f)
		{
			Stat.DebuffTimeRemaining -= DeltaTime;
			if (Stat.DebuffTimeRemaining <= 0.f)
			{
				Stat.DebuffTimeRemaining = 0.f;
				Stat.DebuffAmount = 0.f;
				bModified = true;
			}
		}

		if (bModified)
		{
			Stat.bDirty = true;
		}
	}
}



void UStatsComponent::AddStatFromDefinition(const FStatDefinitionRow& Definition, float InitialValue, float MaxValue)
{
	FCharacterStat NewStat;
	NewStat.StatID = Definition.Name;
	NewStat.CurrentValue = InitialValue;
	NewStat.MaxValue = MaxValue;

	ConfiguredStats.Add(NewStat);
}

bool UStatsComponent::ApplyBuff(const FName& StatName, float BuffAmount, float DurationSeconds)
{
	for (FCharacterStat& Stat : ConfiguredStats)
	{
		if (Stat.StatID == StatName)
		{
			Stat.BuffAmount = BuffAmount;
			Stat.BuffTimeRemaining = DurationSeconds;
			Stat.bDirty = true;
			return true;
		}
	}

	return false; // Stat not found
}

bool UStatsComponent::ApplyDebuff(const FName& StatName, float DebuffAmount, float DurationSeconds)
{
	for (FCharacterStat& Stat : ConfiguredStats)
	{
		if (Stat.StatID == StatName)
		{
			Stat.DebuffAmount = DebuffAmount;
			Stat.DebuffTimeRemaining = DurationSeconds;
			Stat.bDirty = true;
			return true;
		}
	}

	return false; // Stat not found
}

bool UStatsComponent::SetStatMax(const FName& StatName, float NewMaxValue)
{
	for (FCharacterStat& Stat : ConfiguredStats)
	{
		if (Stat.StatID == StatName)
		{
			Stat.MaxValue = NewMaxValue;
			Stat.bDirty = true;
			return true;
		}
	}
	return false;
}

bool UStatsComponent::SetStatCurrent(const FName& StatName, float NewCurrentValue)
{
	for (FCharacterStat& Stat : ConfiguredStats)
	{
		if (Stat.StatID == StatName)
		{
			Stat.CurrentValue = NewCurrentValue;
			Stat.bDirty = true;
			return true;
		}
	}
	return false;
}

bool UStatsComponent::GetStatCurrent(const FName& StatName, float& OutCurrentValue) const
{
	for (const FCharacterStat& Stat : ConfiguredStats)
	{
		if (Stat.StatID == StatName)
		{
			OutCurrentValue = Stat.CurrentValue;
			return true;
		}
	}
	return false;
}

bool UStatsComponent::GetStatMax(const FName& StatName, float& OutMaxValue) const
{
	for (const FCharacterStat& Stat : ConfiguredStats)
	{
		if (Stat.StatID == StatName)
		{
			OutMaxValue = Stat.MaxValue;
			return true;
		}
	}
	return false;
}

bool UStatsComponent::GetStatBuff(const FName& StatName, float& OutBuffAmount) const
{
	for (const FCharacterStat& Stat : ConfiguredStats)
	{
		if (Stat.StatID == StatName)
		{
			OutBuffAmount = Stat.BuffAmount;
			return true;
		}
	}
	return false;
}

bool UStatsComponent::GetStatDebuff(const FName& StatName, float& OutDebuffAmount) const
{
	for (const FCharacterStat& Stat : ConfiguredStats)
	{
		if (Stat.StatID == StatName)
		{
			OutDebuffAmount = Stat.DebuffAmount;
			return true;
		}
	}
	return false;
}
