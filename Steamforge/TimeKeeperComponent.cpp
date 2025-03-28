// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeKeeperComponent.h"

// Sets default values for this component's properties
UTimeKeeperComponent::UTimeKeeperComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTimeKeeperComponent::BeginPlay()
{
	Super::BeginPlay();

    // Initialize the game clock to canonical start time in Forge calendar
    CurrentTime.Year = 731;
    CurrentTime.Month = 1;
    CurrentTime.Day = 1;
    CurrentTime.Hour = 6;   // Start at 6:00 AM
    CurrentTime.Minute = 0;
    CurrentTime.Second = 0;
    CurrentTime.DayOfWeek = 1;

    // NOTE: Make configurable

    UE_LOG(LogTemp, Log, TEXT("TimeKeeper Initialized: %s"), *CurrentTime.GetFormattedTimeString(true, true));	
}


// Called every frame
void UTimeKeeperComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    AccumulatedRealSeconds += DeltaTime;
    UpdateCurrentTimeFromAccumulated();
}

void UTimeKeeperComponent::UpdateCurrentTimeFromAccumulated()
{
    const int32 TotalGameSeconds = FMath::FloorToInt(AccumulatedRealSeconds * TimeScale);

    int32 RemainingSeconds = TotalGameSeconds;

    CurrentTime.Second = RemainingSeconds % FGameDateTime::SecondsPerMinute;
    RemainingSeconds /= FGameDateTime::SecondsPerMinute;

    CurrentTime.Minute = RemainingSeconds % FGameDateTime::MinutesPerHour;
    RemainingSeconds /= FGameDateTime::MinutesPerHour;

    CurrentTime.Hour = RemainingSeconds % FGameDateTime::HoursPerDay;
    RemainingSeconds /= FGameDateTime::HoursPerDay;

    CurrentTime.Day = (RemainingSeconds % FGameDateTime::DaysPerMonth) + 1;
    RemainingSeconds /= FGameDateTime::DaysPerMonth;

    CurrentTime.Month = (RemainingSeconds % FGameDateTime::MonthsPerYear) + 1;
    RemainingSeconds /= FGameDateTime::MonthsPerYear;

    CurrentTime.Year = 731 + RemainingSeconds;

    int32 TotalDays = FMath::FloorToInt(TotalGameSeconds / (FGameDateTime::HoursPerDay * FGameDateTime::MinutesPerHour * FGameDateTime::SecondsPerMinute));
    CurrentTime.DayOfWeek = (TotalDays % FGameDateTime::DaysPerWeek) + 1;
}


////////////////////////////////
// FGameDataTime 
////////////////////////////////

FString FGameDateTime::GetFormattedTimeString(bool bUse24HourFormat, bool bUseNamedDate, const UDataTable* DayNames, const UDataTable* MonthNames) const
{
    // Format time portion
    FString TimeString;
    int32 DisplayHour = Hour;

    if (!bUse24HourFormat)
    {
        const FString Suffix = (Hour >= HoursPerDay / 2) ? TEXT("PM") : TEXT("AM");
        DisplayHour = Hour % (HoursPerDay / 2);
        if (DisplayHour == 0) DisplayHour = HoursPerDay / 2;

        TimeString = FString::Printf(TEXT("%02d:%02d %s"), DisplayHour, Minute, *Suffix);
    }
    else
    {
        TimeString = FString::Printf(TEXT("%02d:%02d"), Hour, Minute);
    }

    // Format date portion
    FString DateString;

    if (bUseNamedDate && DayNames && MonthNames)
    {
        FString DayName = FString::Printf(TEXT("Day %d"), DayOfWeek);
        FString MonthName = FString::Printf(TEXT("Month %d"), Month);

        if (DayOfWeek >= 1 && DayOfWeek <= DaysPerWeek)
        {
            const FName DayKey = FName(*FString::FromInt(DayOfWeek));
            const FCalendarLabelRow* DayRow = DayNames->FindRow<FCalendarLabelRow>(DayKey, TEXT(""));
            if (DayRow) DayName = DayRow->DisplayName.ToString();
        }

        if (Month >= 1 && Month <= MonthsPerYear)
        {
            const FName MonthKey = FName(*FString::FromInt(Month));
            const FCalendarLabelRow* MonthRow = MonthNames->FindRow<FCalendarLabelRow>(MonthKey, TEXT(""));
            if (MonthRow) MonthName = MonthRow->DisplayName.ToString();
        }

        DateString = FString::Printf(TEXT("%s, %s %d, Year %d"), *DayName, *MonthName, Day, Year);
    }
    else
    {
        DateString = FString::Printf(TEXT("%02d/%02d/%04d"), Month, Day, Year);
    }

    // Final combined result
    return FString::Printf(TEXT("%s - %s"), *DateString, *TimeString);
}
