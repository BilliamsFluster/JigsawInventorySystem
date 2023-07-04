#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "JI_JigsawPiece.generated.h"


USTRUCT(BlueprintType)
struct FJigsawPiece : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jigsaw Piece")
	FString ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jigsaw Piece")
	FString ItemDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jigsaw Piece")
	UTexture2D* PieceIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jigsaw Piece")
	UStaticMesh* PieceMesh;

	bool operator==(const FJigsawPiece& other) const
	{
		return ItemName == other.ItemName;
	}

};


UCLASS()
class JIGSAWINVENTORY_API AJI_JigsawPiece : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AJI_JigsawPiece();

public:
	FDataTableRowHandle& GetPieceData() { return m_PieceData; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& changedEvent) override;


protected:
	UFUNCTION(BlueprintCallable, Category = "Jigsaw Piece")
	void UpdateMesh();


private:

	// The ID of the jigsaw piece this actor represents
	UPROPERTY(EditAnywhere, Category = "Jigsaw Piece", meta = (AllowPrivateAccess = true, DisplayName = "Piece Data"))
	FDataTableRowHandle  m_PieceData;
	// The mesh component that will display the jigsaw piece
	UPROPERTY(VisibleAnywhere, Category = "Jigsaw Piece", meta = (AllowPrivateAccess = true, DisplayName = "Mesh"))
	UStaticMeshComponent* m_MeshComponent;

	class UJI_JigsawInventoryComponent* m_JigsawInventory;


};
