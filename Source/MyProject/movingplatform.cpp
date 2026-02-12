// Fill out your copyright notice in the Description page of Project Settings.


#include "movingplatform.h"

// Sets default values
Amovingplatform::Amovingplatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

int MyTestFunction(float MyFloatParam, FString MyStringParam)
{
	UE_LOG(LogTemp, Display, TEXT("MyFloatParam is %f"), MyFloatParam);

	UE_LOG(LogTemp, Display, TEXT("MyStringParam is %s"), *MyStringParam);

	return 40;
}


// Called when the game starts or when spawned
void Amovingplatform::BeginPlay()
{
	Super::BeginPlay();


	FString MyName = GetName();
	int ReturnValue = MyTestFunction(3.5f, MyName);
	UE_LOG(LogTemp, Display, TEXT("Return value is %d"), ReturnValue);

	StartLocation = GetActorLocation();

	int MyNumber = 18 + 2;
	UE_LOG(LogTemp, Display, TEXT("MyNumber is %d"), MyNumber);

	if (MyNumber > 10)
	{
		UE_LOG(LogTemp, Display, TEXT("MyNumber is greater than 10"));
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("MyNumber is less than or equal to 10"));
	}
}



// Called every frame
void Amovingplatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	{
		Super::Tick(DeltaTime);
	
		MovePlatform(DeltaTime);
		RotatePlatform(DeltaTime);
	}
	

}

void Amovingplatform::MovePlatform(float DeltaTime)
{
	DistanceMoved = GetDistanceMoved();

	if (DistanceMoved >= MoveDistance)
	{
		float Overshoot = DistanceMoved - MoveDistance;
		FString PlatformName = GetName();
		UE_LOG(LogTemp, Display, TEXT("%s overshot by %f"), *PlatformName, Overshoot);

		FVector MoveDirection = PlatformVelocity.GetSafeNormal();
		FVector NewStartLocation = StartLocation + MoveDirection * MoveDistance;
		SetActorLocation(NewStartLocation);
		StartLocation = NewStartLocation;

		PlatformVelocity = -PlatformVelocity;
	}
	else
	{
		FVector CurrentLocation = GetActorLocation();

		CurrentLocation = CurrentLocation + (PlatformVelocity * DeltaTime);

		SetActorLocation(CurrentLocation);
	}
}


void Amovingplatform::RotatePlatform(float DeltaTime)
{
	// Rotate the platform
	FRotator RotationToAdd = RotationVelocity * DeltaTime;
	AddActorLocalRotation(RotationToAdd);
}

float Amovingplatform::GetDistanceMoved()
{
	return FVector::Dist(StartLocation, GetActorLocation());
}
