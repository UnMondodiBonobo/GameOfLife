// Fill out your copyright notice in the Description page of Project Settings.


#include "Cell.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values
ACell::ACell()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	Collider->SetupAttachment(Mesh);

	

}

// Called when the game starts or when spawned
void ACell::BeginPlay()
{
	Super::BeginPlay();
	SetActorTickEnabled(false);
	
	/* At the first iteration check if the cell is set to dead or alive and change the material*/
	bIsDead == true ? Mesh->SetMaterial(0, DeadMaterial) : Mesh->SetMaterial(0, AliveMaterial);
	bIsDeadtemp = bIsDead;

	/*Sets the timer that loops through the iteration*/
	GetWorldTimerManager().SetTimer(TimerHandleIteration, this,  &ACell::Interaction,0.1f, true);
	
}

/* This function checks all the cell's neighbours, counts the living ones and the dead ones and sets bIsDeadtemp following the rules*/
void ACell::Interaction() 
{
	
	Dead = 0;
	Alive = 0;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	/* Calculate all vectors around (up, down, right , left and diagonals) and always use a correct vector length based on trigonometric standards*/
	Start = GetActorLocation();
	EndRight = Start+FVector(0.f, Radius, 0.f);
	EndLeft = Start+FVector(0.f, -Radius, 0.f);
	EndUp = Start+FVector(0.f, 0.f, Radius);
	EndDown = Start+FVector(0.f, 0.f, -Radius);
	EndRightUp = Start+FVector(0.f, Radius*DiagonalAngle, Radius*DiagonalAngle);
	EndLeftUp = Start+FVector(0.f, -Radius*DiagonalAngle, Radius*DiagonalAngle);
	EndRightDown = Start+FVector(0.f, Radius*DiagonalAngle, -Radius*DiagonalAngle);
	EndLeftDown = Start+FVector(0.f, -Radius*DiagonalAngle, -Radius*DiagonalAngle);


	/*Render a red line for each vector, check his neighbours*/

	IsHitRight = GetWorld()->LineTraceSingleByChannel(HitRight, Start, EndRight, ECollisionChannel::ECC_Visibility, QueryParams);
	//DrawDebugLine(GetWorld(), Start, EndRight, FColor::Red, false, 0.4f);

	IsHitLeft = GetWorld()->LineTraceSingleByChannel(HitLeft, Start, EndLeft, ECollisionChannel::ECC_Visibility, QueryParams);
	//DrawDebugLine(GetWorld(), Start, EndLeft, FColor::Red, false, 0.4f);

	IsHitUp = GetWorld()->LineTraceSingleByChannel(HitUp, Start, EndUp, ECollisionChannel::ECC_Visibility, QueryParams);
	//DrawDebugLine(GetWorld(), Start, EndUp, FColor::Red, false, 0.4f);

	IsHitDown = GetWorld()->LineTraceSingleByChannel(HitDown, Start, EndDown, ECollisionChannel::ECC_Visibility, QueryParams);
	//DrawDebugLine(GetWorld(), Start, EndDown, FColor::Red, false, 0.4f);

	IsHitRightUp = GetWorld()->LineTraceSingleByChannel(HitRightUp, Start, EndRightUp, ECollisionChannel::ECC_Visibility, QueryParams);
	//DrawDebugLine(GetWorld(), Start, EndRightUp, FColor::Red, false, 0.4f);

	IsHitLeftUp = GetWorld()->LineTraceSingleByChannel(HitLeftUp, Start, EndLeftUp, ECollisionChannel::ECC_Visibility, QueryParams);
	//DrawDebugLine(GetWorld(), Start, EndLeftUp, FColor::Red, false, 0.4f);

	IsHitRightDown = GetWorld()->LineTraceSingleByChannel(HitRightDown, Start, EndRightDown, ECollisionChannel::ECC_Visibility, QueryParams);
	//DrawDebugLine(GetWorld(), Start, EndRightDown, FColor::Red, false, 0.4f);

	IsHitLeftDown = GetWorld()->LineTraceSingleByChannel(HitLeftDown, Start, EndLeftDown, ECollisionChannel::ECC_Visibility, QueryParams);
	//DrawDebugLine(GetWorld(), Start, EndLeftDown, FColor::Red, false, 0.4f);

	if(IsHitDown && HitDown.GetActor() != this) 
	{
		CellDown = Cast<ACell>(HitDown.GetActor());
		if(CellDown->bIsDead == true){Dead++;}  
		else{Alive++;}

		
	}
	if(IsHitUp && HitUp.GetActor() != this) 
	{
		CellUp = Cast<ACell>(HitUp.GetActor());
		if(CellUp->bIsDead == true){Dead++;}  
		else{Alive++;}
		
		
	}	
	if(IsHitRight && HitRight.GetActor() != this) 
	{
		
		CellRight = Cast<ACell>(HitRight.GetActor());
		if(CellRight->bIsDead == true){Dead++;}  
		else{Alive++;}
		
		
	}
	
	if(IsHitLeft && HitLeft.GetActor() != this) 
	{
		CellLeft = Cast<ACell>(HitLeft.GetActor());
		if(CellLeft->bIsDead == true){Dead++;}  
		else{Alive++;}
				
	
	}

	if(IsHitRightUp && HitRightUp.GetActor() != this) 
	{
		CellRightUp = Cast<ACell>(HitRightUp.GetActor());
		if(CellRightUp->bIsDead == true){Dead++;}  
		else{Alive++;}
		
		
	}

	if(IsHitRightDown && HitRightDown.GetActor() != this) 
	{
		CellRightDown = Cast<ACell>(HitRightDown.GetActor());
		if(CellRightDown->bIsDead == true){Dead++;}  
		else{Alive++;}
	
	}
	
	if(IsHitLeftUp && HitLeftUp.GetActor() != this) 
	{

		CellLeftUp = Cast<ACell>(HitLeftUp.GetActor());
		if(CellLeftUp->bIsDead == true){Dead++;}  
		else{Alive++;}

	
	}

	if(IsHitLeftDown && HitLeftDown.GetActor() != this) 
	{
		CellLeftDown = Cast<ACell>(HitLeftDown.GetActor());
		if(CellLeftDown->bIsDead == true){Dead++;}  
		else{Alive++;}

		
	}

	if(bIsDead)/*If this cell is already dead*/
	{
		/*Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.*/

		if(Alive == 3) {bIsDeadtemp = false;} /* use bIsDeadtemp as a placeholder */
	}

	else /* if this cell is still alive*/
	{	
		/*Any live cell with fewer than two live neighbours dies, as if by underpopulation.
		Any live cell with more than three live neighbours dies, as if by overpopulation.*/
		
		if(Alive < 2 || Alive > 3) {bIsDeadtemp = true; }/* use bIsDeadtemp as a placeholder */
	}

	/* Call ChangeState function 0.05 seconds after Interaction function has been called*/
	GetWorldTimerManager().SetTimer(TimerHandleToChangeState, this, &ACell::ChangeState, 0.05f, false);


}

/*This function change the state of bIsDead, based on the result of bIsDeadtemp*/
void ACell::ChangeState() 
{
	bIsDead = bIsDeadtemp;
	bIsDead == true ? Mesh->SetMaterial(0, DeadMaterial) : Mesh->SetMaterial(0, AliveMaterial);
	GetWorldTimerManager().ClearTimer(TimerHandleToChangeState);
}

// Called every frame
void ACell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	

	

}

