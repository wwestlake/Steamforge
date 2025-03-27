#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SteamforgeUserSettings.generated.h"

/**
 * User-configurable persistent game settings
 */
UCLASS(Blueprintable, Config=GameUserSettings)
class STEAMFORGE_API USteamforgeUserSettings : public UObject
{
    GENERATED_BODY()

public:
    // Retrieve the singleton instance of the settings
    UFUNCTION(BlueprintCallable, Category = "User Settings")
    static USteamforgeUserSettings* Get();

    // Save settings to disk (GameUserSettings.ini)
    UFUNCTION(BlueprintCallable, Category = "User Settings")
    void SaveSettings();

    /** Whether to use 24-hour time format */
    UPROPERTY(EditAnywhere, Config, BlueprintReadWrite, Category = "UI")
    bool bUse24HourTime = false;
};
