// Fill out your copyright notice in the Description page of Project Settings.


#include "JI_JigsawInventoryGridWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/Border.h"
#include "JI_JigsawPieceWidget.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/CanvasPanel.h"
#include "Blueprint/DragDropOperation.h"

void UJI_JigsawInventoryGridWidget::Init(UJI_JigsawInventoryComponent* inventoryComponent, float tileSize)
{
	JigsawInventoryComponent = inventoryComponent;
	TileSize = tileSize;
	auto* borderPanel = UWidgetLayoutLibrary::SlotAsCanvasSlot(InventoryGridBorder);
	float cols = JigsawInventoryComponent->GetColumns() * TileSize;
	float rows = JigsawInventoryComponent->GetRows() * TileSize;
	if(borderPanel)
		borderPanel->SetSize({ cols,rows });
	
	CreateLineSegments();
	Refresh();
	

}

void UJI_JigsawInventoryGridWidget::CreateLineSegments()
{
	int x, y;
	if (JigsawInventoryComponent)
	{
		
		for (int i = 0; i < JigsawInventoryComponent->GetColumns(); i++)
		{
			x = TileSize * i;

			FLine line = {FVector2D(x, 0), FVector2D(x, TileSize * JigsawInventoryComponent->GetRows())};
			Lines.Add(line);
		}
		for (int j = 0; j < JigsawInventoryComponent->GetRows(); j++)
		{
			y = TileSize * j;
			FLine line = {FVector2D(0, y), FVector2D(TileSize * JigsawInventoryComponent->GetColumns(), y)};
			Lines.Add(line);
		}
	}
	
}

void UJI_JigsawInventoryGridWidget::Refresh()
{
	TArray<AJI_JigsawPiece*> inventoryKeys;
	TMap<AJI_JigsawPiece*, FVector2D> jigsawPieces = JigsawInventoryComponent->GetAllJigsawPieces();
	CanvasPanel->ClearChildren();
	jigsawPieces.GetKeys(inventoryKeys);
	


	for (auto key : inventoryKeys)
	{
		UJI_JigsawPieceWidget* widget = CreateWidget<UJI_JigsawPieceWidget>(GetWorld(), JigsawPieceWidget);
		
		if (widget)
		{
			widget->SetupPieceAndSize(key, TileSize);
			// need to add widget->OnRemoved.AddDynamic(this, AJI_JigsawPiece::OnRemoved());
			auto* child = CanvasPanel->AddChild(widget);
			auto* castedChild = Cast<UCanvasPanelSlot>(child);
			castedChild->SetAutoSize(true);
			float x = jigsawPieces.Find(key)->X;
			float y = jigsawPieces.Find(key)->Y;
			castedChild->SetPosition({ x * TileSize, y * TileSize });
			UE_LOG(LogTemp, Warning, TEXT("Widget created and added to Canvas Panel"));



		}
	}
	
}

void UJI_JigsawInventoryGridWidget::OnPieceRemove(AJI_JigsawPiece* piece)
{
	JigsawInventoryComponent->RemoveItem(piece);
}

AJI_JigsawPiece* UJI_JigsawInventoryGridWidget::GetPayload(UDragDropOperation* operation)
{
	if (operation->Payload != nullptr)
	{
		return Cast<AJI_JigsawPiece>(operation->Payload);
	}
	return nullptr;
}

bool UJI_JigsawInventoryGridWidget::IsRoomAvailableForPayload(AJI_JigsawPiece* piece)
{
	if (piece)
	{
		int topLeftIndex = JigsawInventoryComponent->TileToIndex(FVector2D( DraggedItemTopLeftTile.X, DraggedItemTopLeftTile.Y ));
		return JigsawInventoryComponent->IsRoomAvailable(piece, topLeftIndex);
	}
	return false;
}

FMouseState UJI_JigsawInventoryGridWidget::MousePositionInTile(FVector2D pos)
{
	bool right = fmod(pos.X, TileSize) > TileSize / 2.0f;
	bool down = fmod(pos.Y, TileSize) > TileSize / 2.0f;
	return FMouseState{ right, down };
}

FVector2D UJI_JigsawInventoryGridWidget::CalculateTopLeftTile(FVector2D mousePosition, AJI_JigsawPiece* piece, FVector2D initialRelativePos)
{
	// Convert mouse position to tile coordinates
	FVector2D mouseTile = mousePosition / TileSize;

	mouseTile.X = FMath::RoundHalfToEven(mouseTile.X);
	mouseTile.Y = FMath::RoundHalfToEven(mouseTile.Y);
	// Calculate top left tile of the piece
	FVector2D topLeftTile = mouseTile - initialRelativePos;

	// Clamp to grid size to ensure the tile is within bounds
	topLeftTile.X = FMath::Clamp(topLeftTile.X, 0.0f, JigsawInventoryComponent->GetColumns() - piece->GetDimensions().X);
	topLeftTile.Y = FMath::Clamp(topLeftTile.Y, 0.0f, JigsawInventoryComponent->GetRows() - piece->GetDimensions().Y);

	return topLeftTile;
}

FVector2D UJI_JigsawInventoryGridWidget::GetMousePositionRelativeToInventoryGrid()
{
	// Get the mouse position in viewport coordinates
	FVector2D MousePosition = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());

	// Get the position of the top-left corner of the inventory grid in viewport coordinates
	FVector2D GridPosition = InventoryGridBorder->GetCachedGeometry().AbsoluteToLocal(FVector2D::ZeroVector);

	// Convert to relative coordinates
	FVector2D RelativeMousePosition = MousePosition - GridPosition;

	return RelativeMousePosition;
}

