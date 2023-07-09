// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "JI_JigsawPiece.h"
#include "JI_JigsawDragDropOperation.generated.h"

/**
 * 
 */
UCLASS()
class JIGSAWINVENTORY_API UJI_JigsawDragDropOperation : public UDragDropOperation
{
	GENERATED_BODY()
public:

    UPROPERTY()
    AJI_JigsawPiece* DraggedPiece;

    UPROPERTY()
    FVector2D InitialRelativePos;

    UPROPERTY()
        UUserWidget* DefaultDragVisualWidget;

    void OnDragStart(const FPointerEvent& PointerEvent);
    
};
