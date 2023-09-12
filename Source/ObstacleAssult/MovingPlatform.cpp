// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();

	FString Name = GetName();
	
	UE_LOG(LogTemp, Display, TEXT("Configured moved distance[%s] %f"), *Name, MoveDistance);
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovePlatform(DeltaTime);
	RotatePlatform(DeltaTime);
}

void AMovingPlatform::MovePlatform(float DeltaTime)
{
    if(ShouldPlatformReturn())
    {
    	FVector MoveDirection = PlatformVelocity.GetSafeNormal();
    	StartLocation = StartLocation + MoveDirection * MoveDistance; //CurrentLocaiton
    	// float OverShoot = FVector::Dist(StartLocation, CurrentLocation);
    	// UE_LOG(LogTemp, Display, TEXT("Over Shoot : %f"), OverShoot);
    	SetActorLocation(StartLocation);
    	PlatformVelocity = -PlatformVelocity;
    }
	else
	{
		FVector CurrentLocation = GetActorLocation();
		CurrentLocation += (PlatformVelocity * DeltaTime);
		SetActorLocation(CurrentLocation);
	}
}

void AMovingPlatform::RotatePlatform(float DeltaTime)
{
	// FRotator CurrentRotation = GetActorRotation();
	// CurrentRotation += (RotationVelocity * DeltaTime);
	// SetActorRotation(CurrentRotation);
	AddActorLocalRotation(RotationVelocity * DeltaTime);
}
	

bool AMovingPlatform::ShouldPlatformReturn() const
{
	return GetDistanceMoved() > MoveDistance;
}

float AMovingPlatform::GetDistanceMoved() const
{
	return FVector::Dist(StartLocation, GetActorLocation());
}



