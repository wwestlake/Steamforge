#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SteamforgeSaveGame.generated.h"

UCLASS()
class STEAMFORGE_API USteamforgeSaveGame : public USaveGame
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite, SaveGame)
    float stubValue = 0.0;
};
