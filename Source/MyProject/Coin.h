// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Coin.generated.h"

UCLASS()
class MYPROJECT_API ACoin : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACoin();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Collision component */
	UPROPERTY(VisibleAnywhere, Category = "Coin")
	USphereComponent* CollisionComp;

	/** Visual mesh */
	UPROPERTY(VisibleAnywhere, Category = "Coin")
	UStaticMeshComponent* MeshComp;

	/** Points awarded when collected */
	UPROPERTY(EditAnywhere, Category = "Coin")
	int32 Points;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
