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
			if (i >= m_JigsawInventory.Num())
			{
				return false;
			}
		}
	}
	return false;
}

bool UJI_JigsawInventoryComponent::IsRoomAvailable(AJI_JigsawPiece* piece, int topLeftIndex)
{
	FVector2D tile = IterateTiles(piece, topLeftIndex);
	if (IsTileValid(tile))
	{
		ValidPiece p = GetItemAtIndex(TileToIndex(tile));
		if (p.Valid)
		{
			if (UKismetSystemLibrary::IsValid(piece))
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	return true;
	
	 
}  
void UJI_JigsawInventoryComponent::AddItemAt(AJI_JigsawPiece* piece, int topLeftIndex)
{
	FVector2D tile = IterateTiles(piece, topLeftIndex);
	
	m_JigsawInventory[TileToIndex(tile)] = piece;

	m_InventoryChanged = true;

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
	if (tile.X >= 0 && tile.Y >= 0 && tile.X < 0 && tile.Y < 0)
	{
		return true;
	}
	return false;
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

ValidPiece UJI_JigsawInventoryComponent::GetItemAtIndex(int index)
{
	if (m_JigsawInventory.IsValidIndex(index))
	{
		return ValidPiece{ true, m_JigsawInventory[index] };
	}
	return ValidPiece{ false, {} };
}



void UJI_JigsawInventoryComponent::AddItem(AJI_JigsawPiece* piece)
{
	if (m_JigsawInventory.Contains(piece))
	{
		return;
	}

	// Check if the item exists in the data table
	

	// If everything is ok, add the item to the inventory
	m_JigsawInventory.Add(piece);
}

void UJI_JigsawInventoryComponent::RemoveItem(AJI_JigsawPiece* piece)
{
	// Check if the item is in the inventory
	if (m_JigsawInventory.Find(piece))
	{
		// If it is, remove it
		m_JigsawInventory.Remove(piece);
	}
	
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

