#include "ItemActor.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "GameplayTagContainer.h"

AItemActor::AItemActor()
{
    PrimaryActorTick.bCanEverTick = false;

    // Optional: Basic mesh root setup (if not already done in header)
    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    RootComponent = MeshComponent;

    // Optional: Default tags setup
    ItemTags = FGameplayTagContainer();

    // Logging for debug
    UE_LOG(LogTemp, Log, TEXT("ItemActor constructed."));
}

void AItemActor::BeginPlay()
{
    Super::BeginPlay();

    // Example debug
    UE_LOG(LogTemp, Log, TEXT("ItemActor BeginPlay: Tags [%s]"),
        *ItemTags.ToStringSimple());
}
