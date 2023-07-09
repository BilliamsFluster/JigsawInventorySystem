// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "JI_JigsawPiece.h"
#include "JI_JigsawPieceWidget.generated.h"

/**
 * 
 */
DECLARE_DELEGATE(FOnRemovedWidget)


UCLASS()
class JIGSAWINVENTORY_API UJI_JigsawPieceWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SetupPieceAndSize(AJI_JigsawPiece* piece, float size);

	
	FOnRemovedWidget OnRemoved;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (DisplayName = "Piece"))
	AJI_JigsawPiece* Piece;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (DisplayName = "Size"))
	FVector2D Size;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (DisplayName = "TileSize"))
	float TileSize;
	
};
