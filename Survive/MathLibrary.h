// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MathLibrary.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVE_API UMathLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category = "Math|FuzzyLogic")
	static FVector FuzzyLogicGaussian3(float Value, float Mean, float StdDeviation, const FVector& Centers);


};
