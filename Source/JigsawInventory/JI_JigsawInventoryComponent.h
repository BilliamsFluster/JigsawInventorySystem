// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "JI_JigsawInventoryComponent.generated.h"


//USTRUCT(BlueprintType) // can use instead of FVector2D
//struct FTileLayout : public FTableRowBase
//{
//	GENERATED_BODY()
//public:
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Coords")
//	int X;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Coords")
//	int Y;
//
//	FTileLayout(int x, int y)
//		: X(x), Y(y) {}
//
//
//};
struct ValidPiece
{
	bool Valid;
	class AJI_JigsawPiece* Item;
};
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class JIGSAWINVENTORY_API UJI_JigsawInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UJI_JigsawInventoryComponent();

public:

	UFUNCTION(BlueprintCallable)
	bool TryAddItem(AJI_JigsawPiece* piece);

	FVector2D IterateTiles(AJI_JigsawPiece* piece, int topLeftIndex);
	bool IsTileValid(FVector2D tile);

	
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool IsRoomAvailable(AJI_JigsawPiece* piece, int topLeftIndex);
	
	void AddItemAt(AJI_JigsawPiece* piece, int topLeftIndex);
	int TileToIndex(FVector2D tile);
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	FVector2D IndexToTile(int index);
	
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void AddItem(AJI_JigsawPiece* piece);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void RemoveItem(AJI_JigsawPiece* piece);
public:
	
	UFUNCTION(BlueprintPure, Category = "Inventory")
	UDataTable* GetInventoryDataTable() const;

	UFUNCTION(BlueprintPure, Category = "Inventory")
	TArray<AJI_JigsawPiece*>& GetJigsawInventory();
	
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SetJigsawInventorySize(int col, int row);

	ValidPiece GetItemAtIndex(int index);
	
	UFUNCTION(BlueprintPure, Category = "Inventory")
	int& GetColumns() {return m_Columns;}
	
	UFUNCTION(BlueprintPure, Category = "Inventory")
	int& GetRows() {return m_Rows;}

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SetColumns(int val) { m_Columns = val; }
	
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SetRows(int val) { m_Rows = val; }

	UFUNCTION(BlueprintPure, Category = "Inventory")
	bool GetInventoryChanged() { return m_InventoryChanged; }

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SetInventoryChanged(bool val) { m_InventoryChanged = val; }


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere, Category = "Inventory", meta = (AllowPrivateAccess = true, DisplayName = "Columns"))
	int m_Columns;
	
	UPROPERTY(EditAnywhere, Category = "Inventory", meta = (AllowPrivateAccess = true, DisplayName = "Rows"))
	int m_Rows;

	UPROPERTY(EditAnywhere, Category = "Inventory", meta = (AllowPrivateAccess = true, DisplayName = "InventoryTable"))
	UDataTable* m_InventoryTable;

	UPROPERTY(VisibleAnywhere, Category = "Inventory", meta = (AllowPrivateAccess = true, DisplayName = "Jigsaw Inventory"))
	TArray<AJI_JigsawPiece*> m_JigsawInventory;

	bool m_InventoryChanged = false;
		
};
