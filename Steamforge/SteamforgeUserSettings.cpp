#include "SteamforgeUserSettings.h"
#include "UObject/ConstructorHelpers.h"

USteamforgeUserSettings* USteamforgeUserSettings::Get()
{
    static USteamforgeUserSettings* Singleton = nullptr;

    if (!Singleton)
    {
        Singleton = NewObject<USteamforgeUserSettings>(GetTransientPackage(), USteamforgeUserSettings::StaticClass());
        Singleton->AddToRoot(); // Prevent garbage collection
        Singleton->LoadConfig(); // Load from GameUserSettings.ini
    }

    return Singleton;
}

void USteamforgeUserSettings::SaveSettings()
{
    SaveConfig();
}
