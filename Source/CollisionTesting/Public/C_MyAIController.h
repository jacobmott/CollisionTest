// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "C_MyAIController.generated.h"

/**
 * 
 */
UCLASS()
class COLLISIONTESTING_API AC_MyAIController : public AAIController
{
	GENERATED_BODY()

protected:
  //APawn* ControlledPawn;

public:
  // Sets default values for this AI Controller's properties.
  AC_MyAIController();

  // Called when the game starts or when spawned.
  virtual void BeginPlay() override;

  // Called when the AIController is taken over.
  //virtual void OnPossess(APawn* Pawn) override;

  // Called every frame.
  virtual void Tick(float DeltaSeconds) override;

	
};
