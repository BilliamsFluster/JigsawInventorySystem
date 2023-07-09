// Fill out your copyright notice in the Description page of Project Settings.


#include "JI_JigsawPiece.h"
#include "JI_JigsawInventoryComponent.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AJI_JigsawPiece::AJI_JigsawPiece()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    m_MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    m_MeshComponent->SetupAttachment(GetRootComponent());
}



// Called when the game starts or when spawned
void AJI_JigsawPiece::BeginPlay()
{
	Super::BeginPlay();
    UpdateMesh();

}

// Called every frame
void AJI_JigsawPiece::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AJI_JigsawPiece::PostEditChangeProperty(FPropertyChangedEvent& changedEvent)
{
	Super::PostEditChangeProperty(changedEvent);

	UpdateMesh();
}

void AJI_JigsawPiece::UpdateMesh()
{
    FJigsawPiece* PieceData = m_PieceData.GetRow<FJigsawPiece>("JigsawPiece");

    if (PieceData)
    {
        // Update the mesh component
        m_MeshComponent->SetStaticMesh(PieceData->PieceMesh);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("AJigsawPiece::UpdateMesh() Could not find piece data."));
    }
}


FVector2D& AJI_JigsawPiece::GetDimensions()
{
    return m_PieceData.GetRow<FJigsawPiece>("PieceDimensions")->Dimensions;
}

void AJI_JigsawPiece::OnRemoved()
{
}

UTexture2D* AJI_JigsawPiece::GetPieceIcon()
{
    if (!m_PieceData.DataTable) {
        UE_LOG(LogTemp, Warning, TEXT("DataTable is null"));
        return nullptr;
    }

    // Get the row data from the handle
    const FJigsawPiece* PieceRow = m_PieceData.GetRow<FJigsawPiece>("GetPieceIcon");

    if (PieceRow != nullptr && PieceRow->PieceMaterial != nullptr)
    {
        // Try to cast to UMaterialInstance
        if (UMaterialInstance* MaterialInstance = Cast<UMaterialInstance>(PieceRow->PieceMaterial))
        {
            UE_LOG(LogTemp, Warning, TEXT("Material Instance: %s"), *MaterialInstance->GetPathName());

            // Try to get the texture parameter value
            UTexture* BaseTexture = nullptr;
            if (MaterialInstance->GetTextureParameterValue(FName("IconTexture"), BaseTexture))
            {
                UE_LOG(LogTemp, Warning, TEXT("Texture parameter retrieved successfully"));
                // Try to cast to UTexture2D
                if (UTexture2D* Texture2D = Cast<UTexture2D>(BaseTexture))
                {
                    return Texture2D;
                }
            }
            else {
                UE_LOG(LogTemp, Warning, TEXT("Failed to retrieve texture parameter"));
            }
        }
        else 
        {
            UE_LOG(LogTemp, Warning, TEXT("Failed to cast to UMaterialInstance"));
        }

        
    }
    else {
        UE_LOG(LogTemp, Warning, TEXT("PieceRow or PieceMaterial is null"));
    }

    return nullptr;
}



