// TimeKeeper.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "GameFramework/SaveGame.h"
#include "UObject/NoExportTypes.h"
#include "TimeKeeper.generated.h"

UENUM(BlueprintType)
enum class ESeason : uint8
{
    Forgewake,
    Glimmerreach,
    Coalrest,
    Shrouddeep
};

UENUM(BlueprintType)
enum class EGameMonth : uint8
{
    Kindlemoon,
    Copperseed,
    Ashrise,
    Sparksend,
    Gearturn,
    Waneveil,
    Fogbane,
    Stillheart
};

UENUM(BlueprintType)
enum class EGameDay : uint8
{
    Sparkday,
    Coilday,
    Flareday,
    Veilday,
    Stonehold,
    Restfell
};

USTRUCT(BlueprintType)
struct FGameDateTime
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame)
    EGameDay DayOfWeek = EGameDay::Sparkday;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame)
    int32 DayOfMonth = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame)
    EGameMonth Month = EGameMonth::Kindlemoon;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame)
    int32 Year = 731;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame)
    int32 Hour = 6;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame)
    int32 Minute = 0;

    UPROPERTY(SaveGame)
    float AccumulatedTime = 0.0f;

    static const int32 MinutesPerDay;
    static const int32 HoursPerDay;
    static const int32 MinutesPerHour;
    static const int32 DaysPerMonth;
    static const int32 MonthsPerYear;
    static const int32 DaysPerWeek;

    void AdvanceTime(float GameSeconds);
    void AdvanceOneDay();
    FString GetFormattedTime() const;
    FString ToString() const;
};

USTRUCT(BlueprintType)
struct FTimeMarkerEvent : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName EventID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString EventName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Hour;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Minute;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsDaily = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsWeekly = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EGameDay DayOfWeek;
};

USTRUCT(BlueprintType)
struct FTimeEventMetadata : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName EventID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Description;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString LoreText;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSoftObjectPtr<UTexture2D> Icon;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString TriggerType; // e.g., Dialogue, Environment, Music
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTimeMarkerEvent, FName, EventID);

UCLASS()
class STEAMFORGE_API ATimeKeeper : public AActor
{
    GENERATED_BODY()

public:
    ATimeKeeper();

    virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time")
    float TimeScale = 72.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time")
    FGameDateTime CurrentTime;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time Events")
    UDataTable* TimeMarkerTable;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time Events")
    UDataTable* TimeEventMetadataTable;

    UPROPERTY(BlueprintAssignable, Category = "Time Events")
    FOnTimeMarkerEvent OnTimeMarker;

    UFUNCTION(BlueprintCallable, Category = "Time")
    FString GetCurrentTimeString() const;

    UFUNCTION(BlueprintCallable, Category = "Time")
    const FGameDateTime& GetCurrentDateTime() const { return CurrentTime; }

    UFUNCTION(BlueprintCallable, Category = "Time")
    void SaveGameTime();

    UFUNCTION(BlueprintCallable, Category = "Time")
    void LoadGameTime();

protected:
    virtual void BeginPlay() override;

private:
    TArray<FTimeMarkerEvent> LoadedTimeMarkers;
    int32 LastProcessedHour = -1;

    void LoadTimeMarkers();
    void ProcessTimeEvents();
};
