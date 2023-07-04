// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "JI_JigsawInventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class JIGSAWINVENTORY_API UJI_JigsawInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UJI_JigsawInventoryComponent();


public:
	UFUNCTION(BlueprintPure, Category = "Inventory")
	UDataTable* GetInventoryDataTable() const;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	TArray<FJigsawPiece> GetJigsawInventory() const;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void AddItem(const struct FJigsawPiece& piece);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void RemoveItem(const FJigsawPiece& piece);
public:
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	int GetColumns() {return m_Columns;}
	
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	int GetRows() {return m_Rows;}

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SetColumns(int val) { m_Columns = val; }
	
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SetRows(int val) { m_Rows = val; }

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
	TArray<FJigsawPiece> m_JigsawInventory;
		
};
