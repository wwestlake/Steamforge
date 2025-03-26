#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
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

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EGameDay DayOfWeek = EGameDay::Sparkday;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 DayOfMonth = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EGameMonth Month = EGameMonth::Kindlemoon;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Year = 731;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Hour = 6;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Minute = 0;

    float AccumulatedTime = 0.0f;

    static constexpr int32 MinutesPerDay = 1440;
    static constexpr int32 HoursPerDay = 24;
    static constexpr int32 MinutesPerHour = 60;
    static constexpr int32 DaysPerMonth = 28;
    static constexpr int32 MonthsPerYear = 8;
    static constexpr int32 DaysPerWeek = 6;

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
    FString GetCurrentTimeString() const { return CurrentTime.ToString(); }

    UFUNCTION(BlueprintCallable, Category = "Time")
    const FGameDateTime& GetCurrentDateTime() const { return CurrentTime; }

    UFUNCTION(BlueprintCallable, Category = "Time")
    FString GetCurrentTimeString() const { return CurrentTime.ToString(); }


protected:
    virtual void BeginPlay() override;

private:
    TArray<FTimeMarkerEvent> LoadedTimeMarkers;
    int32 LastProcessedHour = -1;

    void LoadTimeMarkers();
    void ProcessTimeEvents();
};
