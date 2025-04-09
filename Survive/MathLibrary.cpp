#include "MathLibrary.h"
#include "Math/UnrealMathUtility.h"

FVector UMathLibrary::FuzzyLogicGaussian3(float Value, float Mean, float StdDeviation, const FVector& Centers)
{
	auto Gaussian = [=](float x, float center) -> float
	{
		float exponent = -FMath::Square(x - center) / (2.0f * FMath::Square(StdDeviation));
		return FMath::Exp(exponent);
	};

	float A = Gaussian(Value, Centers.X);
	float B = Gaussian(Value, Centers.Y);
	float C = Gaussian(Value, Centers.Z);

	// Normalize the outputs so they sum to 1 if not all zero
	float Sum = A + B + C;
	if (Sum > 0)
	{
		A /= Sum;
		B /= Sum;
		C /= Sum;
	}

	return FVector(A, B, C);
}
