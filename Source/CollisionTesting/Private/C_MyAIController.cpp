// Fill out your copyright notice in the Description page of Project Settings.


#include "C_MyAIController.h"
// include draw debug helpers header file
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "../CollisionTestingPawn.h"

AC_MyAIController::AC_MyAIController()
{

  PrimaryActorTick.bCanEverTick = true;

}

void AC_MyAIController::BeginPlay()
{

  Super::BeginPlay();

  if (GEngine) {
    GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("AC_MyAIController BeginPlay called"));
  }
}

void AC_MyAIController::Tick(float DeltaSeconds)
{

  if (GEngine) {
    GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("AC_MyAIController Tick called"));
  }
  Super::Tick(DeltaSeconds);


  if (!GetPawn()) {
    return;
  }

  FHitResult OutHit;
  FVector Start = GetPawn()->GetActorLocation();  //FVector(1.0f, 1.0f, 1.0f); //GetActorLocation();
  if (GetPawn()) {
    if (GEngine)
      GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::Printf(TEXT("Ai Position x: %f, y: %f"), GetPawn()->GetActorLocation().X, GetPawn()->GetActorLocation().Y));
  }
  // alternatively you can get the camera location
  // FVector Start = FirstPersonCameraComponent->GetComponentLocation();
  //APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
  APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
  if (PlayerPawn) {
    if (GEngine)
      GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::Printf(TEXT("Player Position x: %f, y: %f"), PlayerPawn->GetActorLocation().X, PlayerPawn->GetActorLocation().Y));
  }
  FVector ForwardVector = PlayerPawn->GetActorLocation(); //FVector(1.0f, 1.0f, 1.0f); //FirstPersonCameraComponent->GetForwardVector();
  FVector End = (ForwardVector - Start);
  End.Y *= 1000;
  End.X *= 1000; //((ForwardVector) - Start);
  FCollisionQueryParams CollisionParams;

  DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1, 0, 1);


  //Shootable type
  //ETraceTypeQuery MyTraceType = UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_GameTraceChannel2);
  ACollisionTestingPawn* CollisionTestingPawn = Cast<ACollisionTestingPawn>(GetPawn());
  CollisionParams.AddIgnoredActor(CollisionTestingPawn);
  CollisionParams.AddIgnoredComponent(CollisionTestingPawn->ShipMeshComponent);
  if (GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECollisionChannel::ECC_GameTraceChannel2, CollisionParams))
  {
    if (OutHit.bBlockingHit && ( OutHit.GetActor() == Cast<AActor>(PlayerPawn) ) )
    {
      //This is equavalent to GetunitDirectionVector in blueprints
      FVector End2 = End.GetSafeNormal();
      CollisionTestingPawn->FireShot(End2);
      if (GEngine) {
        GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("You are hitting: %s"), *OutHit.GetActor()->GetName()));
        //GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("Impact Point: %s"), *OutHit.ImpactPoint.ToString()));
       // GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("Normal Point: %s"), *OutHit.ImpactNormal.ToString()));

      }
    }
  }

}
