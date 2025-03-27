// ItemActor.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "ItemSystemCore.h" // includes EItemType, FItemMetadata, etc.
#include "ItemActor.generated.h"

UCLASS(Abstract)
class STEAMFORGE_API AItemActor : public AActor
{
    GENERATED_BODY()

public:
    AItemActor();

protected:
    virtual void BeginPlay() override;

    // Load metadata when placed or spawned
    void LoadMetadata();

public:
    /** Unique identifier for item, used to look up metadata */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
    FName ItemID;

    /** Reference to the item metadata data table */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
    UDataTable* ItemMetadataTable;

    /** Cached metadata loaded from table at runtime */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item")
    FItemMetadata ItemMetadata;

    /** Returns true if metadata was successfully loaded */
    UFUNCTION(BlueprintCallable, Category = "Item")
    bool HasValidMetadata() const { return bMetadataLoaded; }

    /** Accessor for name */
    UFUNCTION(BlueprintCallable, Category = "Item")
    FText GetItemName() const { return ItemMetadata.DisplayName; }

    /** Accessor for description */
    UFUNCTION(BlueprintCallable, Category = "Item")
    FText GetItemDescription() const { return ItemMetadata.Description; }

    /** Accessor for icon */
    UFUNCTION(BlueprintCallable, Category = "Item")
    TSoftObjectPtr<UTexture2D> GetItemIcon() const { return ItemMetadata.Icon; }

    /** Accessor for type */
    UFUNCTION(BlueprintCallable, Category = "Item")
    EItemType GetItemType() const { return ItemMetadata.ItemType; }

private:
    bool bMetadataLoaded = false;
};
