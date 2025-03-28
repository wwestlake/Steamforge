// Fill out your copyright notice in the Description page of Project Settings.


#include "CoreUtilityLibrary.h"

FString UCoreUtilityLibrary::FormatTime_HHMMSS(int32 Hour, int32 Minute, int32 Second)
{
    return FString::Printf(TEXT("%02d:%02d:%02d"), Hour, Minute, Second);
}

FString UCoreUtilityLibrary::FormatTime_HHMM_AMPM(int32 Hour, int32 Minute)
{
    const FString Suffix = (Hour >= 12) ? TEXT("PM") : TEXT("AM");
    int32 DisplayHour = Hour % 12;
    if (DisplayHour == 0) DisplayHour = 12;
    return FString::Printf(TEXT("%02d:%02d %s"), DisplayHour, Minute, *Suffix);
}

FString UCoreUtilityLibrary::FormatDate_MMDDYYYY(int32 Month, int32 Day, int32 Year)
{
    return FString::Printf(TEXT("%02d/%02d/%04d"), Month, Day, Year);
}

FString UCoreUtilityLibrary::FormatDateWithNames(const FString& DayName, const FString& MonthName, int32 Day, int32 Year)
{
    return FString::Printf(TEXT("%s, %s %d, Year %d"), *DayName, *MonthName, Day, Year);
}

FString UCoreUtilityLibrary::PadLeft(const FString& Input, int32 TotalWidth, const FString& PadChar)
{
    const int32 PadCount = FMath::Max(0, TotalWidth - Input.Len());
    const TCHAR Pad = (!PadChar.IsEmpty()) ? PadChar[0] : TEXT('0');
    return FString::ChrN(PadCount, Pad) + Input;
}
