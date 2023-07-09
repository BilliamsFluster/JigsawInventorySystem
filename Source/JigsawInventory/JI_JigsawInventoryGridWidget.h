// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "JI_JigsawInventoryComponent.h"
#include "JI_JigsawPiece.h"
#include "JI_JigsawInventoryGridWidget.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FLine
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Start")
	FVector2D Start;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "End")
	FVector2D End;

	FLine() // Default constructor
	{
		Start = FVector2D::ZeroVector;
		End = FVector2D::ZeroVector;
	}

	FLine(FVector2D InStart, FVector2D InEnd) // Constructor with parameters
	{
		Start = InStart;
		End = InEnd;
	}
};

USTRUCT(BlueprintType)
struct FMouseState
{
	GENERATED_BODY()
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Right")
	bool Right;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Down")
	bool Down;
};
UCLASS()
class JIGSAWINVENTORY_API UJI_JigsawInventoryGridWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "InventoryGrid")
	void Init(UJI_JigsawInventoryComponent* inventoryComponent, float tileSize);

	UFUNCTION(BlueprintCallable, Category = "InventoryGrid")
	void CreateLineSegments();

	UFUNCTION(BlueprintCallable, Category = "InventoryGrid")
	void Refresh();

	UFUNCTION(BlueprintCallable, Category = "InventoryGrid")
	void OnPieceRemove(AJI_JigsawPiece* piece);

	UFUNCTION(BlueprintPure, Category = "InventoryGrid")
	AJI_JigsawPiece* GetPayload(class UDragDropOperation* operation);

	UFUNCTION(BlueprintCallable, Category = "InventoryGrid")
	bool IsRoomAvailableForPayload(AJI_JigsawPiece* piece);

	UFUNCTION(BlueprintPure, Category = "InventoryGrid")
	FMouseState MousePositionInTile(FVector2D pos);

	UFUNCTION(BlueprintPure, Category = "InventoryGrid")
	FVector2D CalculateTopLeftTile(FVector2D mousePosition, AJI_JigsawPiece* piece, FVector2D initialRelativePos);

	UFUNCTION(BlueprintPure, Category = "InventoryGrid")
	FVector2D GetMousePositionRelativeToInventoryGrid();

	UFUNCTION(BlueprintPure, Category = "InventoryGrid")
		UJI_JigsawInventoryComponent* GetInventoryComponent() { return JigsawInventoryComponent; }
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (DisplayName = "Inventory Component"))
	UJI_JigsawInventoryComponent* JigsawInventoryComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (DisplayName = "Lines"))
	TArray<FLine> Lines;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (DisplayName = "DraggedItemTopLeftTile"))
	FIntPoint DraggedItemTopLeftTile;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (DisplayName = "DrawDroppedLocation"))
	bool DrawDroppedLocation;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (DisplayName = "TileSize"))
	float TileSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (DisplayName = "CanvasPanel"))
	class UCanvasPanel* CanvasPanel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (DisplayName = "InventoryGridBorder"))
	class UBorder* InventoryGridBorder;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<class UJI_JigsawPieceWidget> JigsawPieceWidget;


	



	
};
