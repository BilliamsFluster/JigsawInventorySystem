// Fill out your copyright notice in the Description page of Project Settings.


#include "JI_JigsawInventoryComponent.h"
#include "JI_JigsawPiece.h"


// Sets default values for this component's properties
UJI_JigsawInventoryComponent::UJI_JigsawInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

UDataTable* UJI_JigsawInventoryComponent::GetInventoryDataTable() const
{
	return m_InventoryTable;
}

TArray<FJigsawPiece> UJI_JigsawInventoryComponent::GetJigsawInventory() const
{
	return m_JigsawInventory;
}


void UJI_JigsawInventoryComponent::AddItem(const FJigsawPiece& piece)
{
	if (m_JigsawInventory.Contains(piece))
	{
		UE_LOG(LogTemp, Warning, TEXT("AJI_JigsawInventory::AddItem() Item already in inventory: %s"), *piece.ItemName);
		return;
	}

	// Check if the item exists in the data table
	FJigsawPiece* pieceData = m_InventoryTable->FindRow<FJigsawPiece>(FName(*piece.ItemName), TEXT(""));
	if (!pieceData)
	{
		UE_LOG(LogTemp, Warning, TEXT("AJI_JigsawInventory::AddItem() Could not find piece data for ID: %s"), *piece.ItemName);
		return;
	}

	// If everything is ok, add the item to the inventory
	m_JigsawInventory.Add(*pieceData);
}

void UJI_JigsawInventoryComponent::RemoveItem(const FJigsawPiece& piece)
{
	// Check if the item is in the inventory
	if (m_JigsawInventory.Find(piece))
	{
		// If it is, remove it
		m_JigsawInventory.Remove(piece);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AJI_JigsawInventory::RemoveItem() Item not in inventory: %s"), *piece.ItemName);
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

