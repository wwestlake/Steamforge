#include "TimeKeeper.h"
#include "Engine/World.h"
#include "Engine/DataTable.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"

ATimeKeeper::ATimeKeeper()
{
    PrimaryActorTick.bCanEverTick = true;
}

void ATimeKeeper::BeginPlay()
{
    Super::BeginPlay();
    LoadTimeMarkers();
    UE_LOG(LogTemp, Log, TEXT("TimeKeeper Initialized: %s"), *CurrentTime.ToString());
}

void ATimeKeeper::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    float ScaledDelta = DeltaTime * TimeScale;
    int32 PreviousHour = CurrentTime.Hour;
    int32 PreviousMinute = CurrentTime.Minute;

    CurrentTime.AdvanceTime(ScaledDelta);

    if (CurrentTime.Hour != PreviousHour || CurrentTime.Minute != PreviousMinute)
    {
        ProcessTimeEvents();
    }
}

void ATimeKeeper::LoadTimeMarkers()
{
    LoadedTimeMarkers.Empty();

    if (!TimeMarkerTable) return;

    static const FString ContextString(TEXT("Time Marker Context"));
    TArray<FTimeMarkerEvent*> Rows;
    TimeMarkerTable->GetAllRows(ContextString, Rows);

    for (FTimeMarkerEvent* Row : Rows)
    {
        if (Row)
        {
            LoadedTimeMarkers.Add(*Row);
        }
    }
}

void ATimeKeeper::ProcessTimeEvents()
{
    for (const FTimeMarkerEvent& Marker : LoadedTimeMarkers)
    {
        bool bShouldFire = false;

        if (Marker.Hour == CurrentTime.Hour && Marker.Minute == CurrentTime.Minute)
        {
            if (Marker.bIsDaily)
            {
                bShouldFire = true;
            }
            else if (Marker.bIsWeekly && Marker.DayOfWeek == CurrentTime.DayOfWeek)
            {
                bShouldFire = true;
            }
        }

        if (bShouldFire)
        {
            OnTimeMarker.Broadcast(Marker.EventID);
            UE_LOG(LogTemp, Log, TEXT("Time Event Triggered: %s at %02d:%02d"), *Marker.EventName, Marker.Hour, Marker.Minute);
        }
    }
}

// --- FGameDateTime Implementation ---

void FGameDateTime::AdvanceTime(float GameSeconds)
{
    AccumulatedTime += GameSeconds;
    int32 TotalMinutesToAdd = static_cast<int32>(AccumulatedTime / 60.0f);
    AccumulatedTime -= TotalMinutesToAdd * 60.0f;

    Minute += TotalMinutesToAdd;
    while (Minute >= MinutesPerHour)
    {
        Minute -= MinutesPerHour;
        Hour++;
    }

    while (Hour >= HoursPerDay)
    {
        Hour -= HoursPerDay;
        AdvanceOneDay();
    }
}

void FGameDateTime::AdvanceOneDay()
{
    DayOfMonth++;
    DayOfWeek = static_cast<EGameDay>((static_cast<uint8>(DayOfWeek) + 1) % DaysPerWeek);

    if (DayOfMonth > DaysPerMonth)
    {
        DayOfMonth = 1;
        Month = static_cast<EGameMonth>((static_cast<uint8>(Month) + 1) % MonthsPerYear);

        if (Month == EGameMonth::Kindlemoon)
        {
            Year++;
        }
    }
}

FString FGameDateTime::GetFormattedTime() const
{
    FString Suffix = (Hour >= 12) ? TEXT("PM") : TEXT("AM");
    int32 DisplayHour = (Hour == 0) ? 12 : (Hour > 12 ? Hour - 12 : Hour);
    return FString::Printf(TEXT("%02d:%02d %s"), DisplayHour, Minute, *Suffix);
}

FString FGameDateTime::ToString() const
{
    const UEnum* DayEnum = StaticEnum<EGameDay>();
    const UEnum* MonthEnum = StaticEnum<EGameMonth>();
    FString DayStr = DayEnum ? DayEnum->GetDisplayNameTextByValue((int64)DayOfWeek).ToString() : TEXT("UnknownDay");
    FString MonthStr = MonthEnum ? MonthEnum->GetDisplayNameTextByValue((int64)Month).ToString() : TEXT("UnknownMonth");

    return FString::Printf(TEXT("%s, %d of %s, Year %d - %s"), *DayStr, DayOfMonth, *MonthStr, Year, *GetFormattedTime());
}