// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CoreUtilityLibrary.generated.h"

/**
 * 
 */
UCLASS()
class STEAMFORGE_API UCoreUtilityLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

	/** Returns time formatted as HH:MM:SS with zero padding */
	UFUNCTION(BlueprintPure, Category = "Time Formatting")
	static FString FormatTime_HHMMSS(int32 Hour, int32 Minute, int32 Second);

	/** Returns time formatted as HH:MM AM/PM (12-hour clock) with zero padding */
	UFUNCTION(BlueprintPure, Category = "Time Formatting")
	static FString FormatTime_HHMM_AMPM(int32 Hour, int32 Minute);

	/** Returns date formatted as MM/DD/YYYY with zero padding */
	UFUNCTION(BlueprintPure, Category = "Date Formatting")
	static FString FormatDate_MMDDYYYY(int32 Month, int32 Day, int32 Year);

	/** Returns date formatted as: DayName, MonthName Day, Year */
	UFUNCTION(BlueprintPure, Category = "Date Formatting")
	static FString FormatDateWithNames(const FString& DayName, const FString& MonthName, int32 Day, int32 Year);

	/** Pads a string on the left with a specified character up to a total width */
	UFUNCTION(BlueprintPure, Category = "String Utilities")
	static FString PadLeft(const FString& Input, int32 TotalWidth, const FString& PadChar = TEXT("0"));

	
};
