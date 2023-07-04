// Fill out your copyright notice in the Description page of Project Settings.


#include "JI_JigsawPiece.h"
#include "JI_JigsawInventoryComponent.h"
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

