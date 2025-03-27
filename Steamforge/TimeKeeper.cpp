// TimeKeeper.cpp

#include "TimeKeeper.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "SteamforgeSaveGame.h" // Ensure this is your save game class header

ATimeKeeper::ATimeKeeper()
{
    PrimaryActorTick.bCanEverTick = true;
}

void ATimeKeeper::BeginPlay()
{
    Super::BeginPlay();

    LoadGameTime();
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

    UE_LOG(LogTemp, Log, TEXT("Loaded %d Time Marker Events"), LoadedTimeMarkers.Num());
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
            UE_LOG(LogTemp, Log, TEXT("Time Event Triggered: %s (%s) at %02d:%02d"),
                *Marker.EventID.ToString(), *Marker.EventName, Marker.Hour, Marker.Minute);
        }
    }
}

void ATimeKeeper::SaveGameTime()
{
    USteamforgeSaveGame* SaveGameInstance = Cast<USteamforgeSaveGame>(UGameplayStatics::CreateSaveGameObject(USteamforgeSaveGame::StaticClass()));
    if (!SaveGameInstance) return;

    SaveGameInstance->SavedTime = CurrentTime;
    UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("TimeSaveSlot"), 0);

    UE_LOG(LogTemp, Log, TEXT("Game Time Saved: %s"), *CurrentTime.ToString());
}

void ATimeKeeper::LoadGameTime()
{
    if (UGameplayStatics::DoesSaveGameExist(TEXT("TimeSaveSlot"), 0))
    {
        USteamforgeSaveGame* LoadedGame = Cast<USteamforgeSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("TimeSaveSlot"), 0));
        if (LoadedGame)
        {
            CurrentTime = LoadedGame->SavedTime;
            UE_LOG(LogTemp, Log, TEXT("Game Time Loaded: %s"), *CurrentTime.ToString());
        }
    }
}
