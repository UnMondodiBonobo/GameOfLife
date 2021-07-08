// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Cell.generated.h"

class UStaticMeshComponent;
class UBoxComponent;

UCLASS()
class GAMEOFLIFE_API ACell : public AActor
{
	GENERATED_BODY()
	
	public:	
		// Sets default values for this actor's properties
		ACell();

		//Create Mesh component and collider component
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta=(AllowPrivateAccess = true))
		UStaticMeshComponent* Mesh;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta=(AllowPrivateAccess = true))
		UBoxComponent* Collider;

		/* Create boolean variable to check if it's Dead or Alive */
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DeadOrAlive", meta=(AllowPrivateAccess = true))
		bool bIsDead;

		UPROPERTY(EditAnywhere)
		float Radius = 200.f;

		/* 45° degrees variation angle*/
		UPROPERTY(VisibleAnywhere)
		double DiagonalAngle = PI/4;

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UMaterialInterface* DeadMaterial;

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UMaterialInterface* AliveMaterial;


		// Called every frame
		virtual void Tick(float DeltaTime) override;

	protected:
		// Called when the game starts or when spawned
		virtual void BeginPlay() override;

	private:
		FTimerHandle TimerHandleIteration;
		FTimerHandle TimerHandleToChangeState;

		/* These values are declared here in the .h file so we don't have to recreate them each iteration and UPROPERTY MACRO can handle potential memory leaks  */
		UPROPERTY()
		FHitResult HitRight;
		UPROPERTY()
		FHitResult HitLeft;
		UPROPERTY()
		FHitResult HitUp;
		UPROPERTY()
		FHitResult HitDown;
		UPROPERTY()
		FHitResult HitRightUp;
		UPROPERTY()
		FHitResult HitRightDown;
		UPROPERTY()
		FHitResult HitLeftUp;
		UPROPERTY()
		FHitResult HitLeftDown;

		UPROPERTY()
		FVector Start;
		UPROPERTY()
		FVector EndRight;
		UPROPERTY()
		FVector EndLeft; 
		UPROPERTY()
		FVector EndUp ;
		UPROPERTY()
		FVector EndDown ;
		UPROPERTY()
		FVector EndRightUp; 
		UPROPERTY()
		FVector EndLeftUp;
		UPROPERTY()
		FVector EndRightDown; 
		UPROPERTY()
		FVector EndLeftDown;

		UPROPERTY()
		bool IsHitRight;
		UPROPERTY()
		bool IsHitLeft;
		UPROPERTY()
		bool IsHitUp;
		UPROPERTY()
		bool IsHitDown;
		UPROPERTY()
		bool IsHitRightUp;
		UPROPERTY()
		bool IsHitLeftUp;
		UPROPERTY()
		bool IsHitRightDown;
		UPROPERTY()
		bool IsHitLeftDown;


		UFUNCTION()
		void Interaction();

		UFUNCTION()
		void ChangeState();

		int32 Dead = 0;
		int32 Alive = 0;

		UPROPERTY()
		ACell* CellDown;
		UPROPERTY()
		ACell* CellUp;
		UPROPERTY()
		ACell* CellRight;
		UPROPERTY()
		ACell* CellLeft;
		UPROPERTY()
		ACell* CellRightUp;
		UPROPERTY()
		ACell* CellRightDown;
		UPROPERTY()
		ACell* CellLeftUp;
		UPROPERTY()
		ACell* CellLeftDown;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DeadOrAlive", meta=(AllowPrivateAccess = true))
		bool bIsDeadtemp;


	
};
