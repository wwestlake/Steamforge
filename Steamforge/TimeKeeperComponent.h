// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "TimeKeeperComponent.generated.h"


/**
 * Represents a named calendar label used in the Steamforge time system.
 * 
 * This struct is shared by day-of-week names, month names, and season names,
 * and is intended to be stored in a DataTable for runtime lookup.
 * 
 * Fields:
 * - Tag: Specifies the type of label, such as "Day", "Month", or "Season".
 * - Index: The zero-based position of this label in its respective category.
 *   For example:
 *     - Days: 0 = Sparkday, 1 = Emberday, etc.
 *     - Months: 0 = Kindlemoon, 1 = Ashfall, etc.
 *     - Seasons: 0 = Spring, 1 = Summer, etc.
 * 
 * This design enables flexible UI and logic support for calendar formatting,
 * localization, and lore-based customization without hardcoding.
 */
USTRUCT(BlueprintType)
struct FCalendarLabelRow : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Calendar")
    int32 Index;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Calendar")
    FText DisplayName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Calendar")
    FText Description;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Calendar")
    FString Tag;  // Expected values: "Day", "Month", or "Season"

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Calendar")
    FSlateBrush Icon;
};


USTRUCT(BlueprintType)
struct FGameDateTime
{
    GENERATED_BODY()

    // Current date and time fields
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time")
    int32 Year = 731; // Starting year as per Forge Time

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time")
    int32 Month = 1; // Range: 1-12

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time")
    int32 Day = 1; // Range: 1-30

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time")
    int32 Hour = 0; // Range: 0-23

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time")
    int32 Minute = 0; // Range: 0-59

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time")
    int32 Second = 0; // Range: 0-59

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time")
    int32 DayOfWeek = 1; // Range: 1-7, corresponding to custom day names

    // Calendar constants
    static const int32 HoursPerDay = 24;
    static const int32 MinutesPerHour = 60;
    static const int32 SecondsPerMinute = 60;
    static const int32 DaysPerWeek = 7;
    static const int32 DaysPerMonth = 30;
    static const int32 MonthsPerYear = 12;

    // Functions to manipulate and display time
    void AdvanceTime(float GameSeconds);
    void AdvanceOneDay();

    FString GetFormattedTime() const;
    FString ToString() const;

	FString GetFormattedTimeString(bool bUse24HourFormat = true, bool bUseNamedDate = true, const UDataTable* DayNames = nullptr, const UDataTable* MonthNames = nullptr) const;

};



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STEAMFORGE_API UTimeKeeperComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTimeKeeperComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/** Current in-game time tracked by this component */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time")
	FGameDateTime CurrentTime;
	
	/** 
	 * Time scale factor: how many in-game seconds pass per real-world second.
	 * Example: 72.0 means 1 real second = 72 in-game seconds (~1.2 minutes)
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time")
	float TimeScale = 72.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time")
	float AccumulatedRealSeconds = 0.0f;

private:
	void UpdateCurrentTimeFromAccumulated();

};
