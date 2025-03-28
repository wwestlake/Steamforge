#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayTagContainer.h"
#include "ItemActor.generated.h"

class UStaticMeshComponent;

UCLASS()
class STEAMFORGE_API AItemActor : public AActor
{
    GENERATED_BODY()

public:
    AItemActor();

protected:
    virtual void BeginPlay() override;

    // Gameplay tags for categorization
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    FGameplayTagContainer ItemTags;

    // Visual representation
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item")
    UStaticMeshComponent* MeshComponent;
};
