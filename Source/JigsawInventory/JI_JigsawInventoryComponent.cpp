// Fill out your copyright notice in the Description page of Project Settings.


#include "JI_JigsawInventoryComponent.h"
#include "JI_JigsawPiece.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values for this component's properties
UJI_JigsawInventoryComponent::UJI_JigsawInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

bool UJI_JigsawInventoryComponent::TryAddItem(AJI_JigsawPiece* piece)
{
	if (piece)
	{
		for (int i = 0; i < m_JigsawInventory.Num(); i++)
		{
			if (IsRoomAvailable(piece, i))
			{
				AddItemAt(piece, i);
				piece->GetPieceIcon();
				return true;
			}
			
		}
	}
	return false;
}

bool UJI_JigsawInventoryComponent::IsRoomAvailable(AJI_JigsawPiece* piece, int topLeftIndex)
{
	
	FVector2D dimensions = piece->GetDimensions();
	FVector2D top_left_tile = IndexToTile(topLeftIndex);

	// iterate over each tile that the piece would cover
	for (int i = 0; i < dimensions.X; ++i) {
		for (int j = 0; j < dimensions.Y; ++j) {
			FVector2D current_tile = FVector2D(top_left_tile.X + i, top_left_tile.Y + j);
			// check if the tile is valid and if there is a piece on that tile
			if (!IsTileValid(current_tile) || GetItemAtIndex(TileToIndex(current_tile)).Piece != nullptr) {
				// if the tile is not valid or there's a piece already, the room is not available
				return false;
			}
		}
	}

	// if all tiles are valid and have no pieces, the room is available
	return true;
	
	 
}  
void UJI_JigsawInventoryComponent::AddItemAt(AJI_JigsawPiece* piece, int topLeftIndex)
{
	/*FVector2D tile = IterateTiles(piece, topLeftIndex);
	
	m_JigsawInventory[TileToIndex(tile)] = piece;

	m_InventoryChanged = true;*/

	FVector2D dimensions = piece->GetDimensions();
	FVector2D top_left_tile = IndexToTile(topLeftIndex);

	// iterate over each tile that the piece would cover
	for (int i = 0; i < dimensions.X; ++i) {
		for (int j = 0; j < dimensions.Y; ++j) {
			FVector2D current_tile = FVector2D(top_left_tile.X + i, top_left_tile.Y + j);
			// add the piece to each tile
			int index = TileToIndex(current_tile);
			if (index >= 0 && index < m_JigsawInventory.Num())
			{
				// Only try to access the array if the index is within bounds
				m_JigsawInventory[index] = piece;
			}
			else
			{
				// Handle the error case when the index is out of bounds
				// For example, you can log a warning message
				UE_LOG(LogTemp, Warning, TEXT("Index out of bounds: %d"), index);
			}
		}
	}

	m_InventoryChanged = true;

	// Debug log to check if piece was added successfully
	int debugIndex = TileToIndex(top_left_tile);
	if (debugIndex >= 0 && debugIndex < m_JigsawInventory.Num())
	{
		if (m_JigsawInventory[debugIndex] == piece)
		{
			UE_LOG(LogTemp, Warning, TEXT("Piece added successfully at index: %d"), debugIndex);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to add piece at index: %d"), debugIndex);
		}
	}

}
int UJI_JigsawInventoryComponent::TileToIndex(FVector2D tile)
{
	return tile.X + (tile.Y * m_Columns);

}
FVector2D UJI_JigsawInventoryComponent::IndexToTile(int index)

{
	int x, y;

	x = index % m_Columns;
	y = index / m_Columns; 
	return FVector2D(x, y );
}
FVector2D UJI_JigsawInventoryComponent::IterateTiles(AJI_JigsawPiece* piece, int topLeftIndex)
{
	FVector2D tiles = IndexToTile(topLeftIndex);

	for (int i = tiles.X; i < (piece->GetDimensions().X - 1 + (tiles.X)); i++)
	{
		for (int j = tiles.Y; j < (piece->GetDimensions().Y - 1 + (tiles.Y)); j++)
		{
			return FVector2D(i, j);
		}
	}
	return FVector2D(1, 1); // if something happened this is a message

	
}

bool UJI_JigsawInventoryComponent::IsTileValid(FVector2D tile)
{
	return (tile.X >= 0 && tile.Y >= 0 && tile.X < m_Columns && tile.Y < m_Rows);
}

UDataTable* UJI_JigsawInventoryComponent::GetInventoryDataTable() const
{
	return m_InventoryTable;
}

TArray<AJI_JigsawPiece*>& UJI_JigsawInventoryComponent::GetJigsawInventory() 
{
	return m_JigsawInventory;
}

void UJI_JigsawInventoryComponent::SetJigsawInventorySize(int col, int row)
{
	int32 ArraySize = col * row;
	m_JigsawInventory.SetNum(ArraySize);
}

FValidPiece UJI_JigsawInventoryComponent::GetItemAtIndex(int index)
{
	if (m_JigsawInventory.IsValidIndex(index))
	{
		return FValidPiece{ true, m_JigsawInventory[index] };
	}
	return FValidPiece{ false, {} };
}





void UJI_JigsawInventoryComponent::RemoveItem(AJI_JigsawPiece* piece)
{
	for (int i = 0; i < m_JigsawInventory.Num(); i++)
	{
		if (m_JigsawInventory[i] == piece)
		{
			m_JigsawInventory[i] = nullptr;
		}
	}
	// Check if the item is in the inventoryCoordItems
	if (m_JigsawInventoryCoordItems.Contains(piece))
	{
		// If it is, remove it
		m_JigsawInventoryCoordItems.Remove(piece);
	}
	m_InventoryChanged = true;
	
}

FItemCoord UJI_JigsawInventoryComponent::IterateOverJigsawInventoryCoordItems()
{
	TArray<AJI_JigsawPiece*> inventoryKeys;
	m_JigsawInventoryCoordItems.GetKeys(inventoryKeys);

	for (auto key : inventoryKeys)
	{
		FVector2D* coord = m_JigsawInventoryCoordItems.Find(key); // returns the value
		if (coord != nullptr)
		{
			return FItemCoord{ key, *coord };
		}
	}
	return FItemCoord{}; // couldnt find it 
}

TMap<AJI_JigsawPiece*, FVector2D>& UJI_JigsawInventoryComponent::GetAllJigsawPieces()
{
	for (int i = 0; i < m_JigsawInventory.Num() - 1; i++)
	{
		if (UKismetSystemLibrary::IsValid(m_JigsawInventory[i]))
		{
			if (!m_JigsawInventoryCoordItems.Contains(m_JigsawInventory[i]))
			{
				m_JigsawInventoryCoordItems.Add(m_JigsawInventory[i], IndexToTile(i));
				break;
			}
		}
	}
	return m_JigsawInventoryCoordItems;
}

// Called when the game starts
void UJI_JigsawInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UJI_JigsawInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

