// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "JI_JigsawInventoryComponent.generated.h"



struct FValidPiece
{
	bool Valid;
	class AJI_JigsawPiece* Piece;
};
USTRUCT(BlueprintType)
struct FItemCoord
{
	GENERATED_BODY()

	AJI_JigsawPiece* Piece;
	FVector2D TopLeftTile;

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
	
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void AddItemAt(AJI_JigsawPiece* piece, int topLeftIndex);
	
	UFUNCTION(BlueprintPure, Category = "Inventory")
	int TileToIndex(FVector2D tile);

	UFUNCTION(BlueprintPure, Category = "Inventory")
	FVector2D IndexToTile(int index);
	


	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void RemoveItem(AJI_JigsawPiece* piece);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	FItemCoord IterateOverJigsawInventoryCoordItems();
public:
	
	UFUNCTION(BlueprintPure, Category = "Inventory")
	UDataTable* GetInventoryDataTable() const;

	UFUNCTION(BlueprintPure, Category = "Inventory")
	TArray<AJI_JigsawPiece*>& GetJigsawInventory();
	
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SetJigsawInventorySize(int col, int row);

	FValidPiece GetItemAtIndex(int index);
	
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
	TMap<AJI_JigsawPiece*, FVector2D>& GetAllJigsawPieces();

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

	UPROPERTY(VisibleAnywhere, Category = "Inventory", meta = (AllowPrivateAccess = true, DisplayName = "Jigsaw Inventory"))
	TMap<AJI_JigsawPiece*, FVector2D> m_JigsawInventoryCoordItems;

	bool m_InventoryChanged = false;
		
};
