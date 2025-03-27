#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataTable.h"
#include "ItemSystemCore.generated.h"

/**
 * Primary classification of the item.
 */
UENUM(BlueprintType)
enum class EItemType : uint8
{
    Food,
    Drink,
    Tool,
    Weapon,
    MagicItem,
    Furniture,
    Material,
    MachinePart,
    Currency,
    Spell,
    SummonToken,
    Blueprint,
    Book,
    QuestItem,
    Key,
    Decorative,
    Drop,
    Container,
    Seed,
    Abstract
};

/**
 * How the item is consumed or used.
 */
UENUM(BlueprintType)
enum class EItemConsumableType : uint8
{
    None,
    Eat,
    Drink,
    UseOnce,
    Read,
    Inject,
    Absorb
};

/**
 * Craftability level of the item.
 */
UENUM(BlueprintType)
enum class ECraftability : uint8
{
    Unique,
    NonCraftableCommon,
    Handcrafted,
    BenchCrafted,
    MachineCrafted,
    Hybrid
};

/**
 * The environment or method needed to craft the item.
 */
UENUM(BlueprintType)
enum class ECraftingContext : uint8
{
    None,
    Inventory,
    BasicWorkbench,
    SteamForgeBench,
    AlchemyStove,
    ArcEngraver,
    FabricatorEngine,
    MysticLoom,
    RitualCircle
};

/**
 * Behavior matrix entry for EItemType categories.
 */
USTRUCT(BlueprintType)
struct FItemTypeMatrixRow : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EItemType ItemType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bTangible;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EItemConsumableType ConsumableType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bUsable;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bPlaceable;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bFunctional;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bStatic;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText Notes;
};

/**
 * Defines a crafting recipe entry.
 */
USTRUCT(BlueprintType)
struct FCraftingRecipe : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName RecipeID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ECraftability Craftability;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ECraftingContext CraftingContext;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FName> RequiredItemIDs;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<int32> RequiredQuantities;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName OutputItemID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 OutputQuantity;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FGameplayTagContainer CraftingTags;
};

/**
 * Metadata for defining item appearance and properties.
 */
USTRUCT(BlueprintType)
struct FItemMetadata : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName ItemID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText DisplayName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText Description;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EItemType ItemType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FGameplayTagContainer ItemTags;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ECraftability Craftability;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ECraftingContext CraftingContext;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSoftObjectPtr<UTexture2D> Icon;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSoftObjectPtr<UStaticMesh> Mesh;
};

USTRUCT(BlueprintType)
struct FIconMetadata : public FTableRowBase {
    GENERATED_BODY();

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName IconID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSoftObjectPtr<UTexture2D> Icon;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Notes;
};

USTRUCT(BlueprintType)
struct FMeshMetadata : public FTableRowBase {
    GENERATED_BODY();

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName MeshID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSoftObjectPtr<UStaticMesh> Mesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Notes;
};
