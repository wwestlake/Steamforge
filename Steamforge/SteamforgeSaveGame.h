#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "TimeSystemCore.h" // For FGameDateTime
#include "SteamforgeSaveGame.generated.h"

UCLASS()
class STEAMFORGE_API USteamforgeSaveGame : public USaveGame
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite, SaveGame)
    FGameDateTime SavedTime;
};
