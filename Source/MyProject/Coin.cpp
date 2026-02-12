// Fill out your copyright notice in the Description page of Project Settings.



#include "Coin.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/PlayerState.h"
#include "GameFramework/Pawn.h"

// Sets default values
ACoin::ACoin()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create collision component
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComp"));
	CollisionComp->InitSphereRadius(40.f);
	CollisionComp->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	RootComponent = CollisionComp;

	// Create visual mesh
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(RootComponent);
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// Default points
	Points = 10;

	// Bind overlap
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &ACoin::OnOverlapBegin);

}

// Called when the game starts or when spawned
void ACoin::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Log, TEXT("Salut ca va?"));
	
}

// Called every frame
void ACoin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACoin::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor || OtherActor == this)
	{
		return;
	}

	// Try to find a player controller / player state to add score
	APawn* Pawn = Cast<APawn>(OtherActor);
	if (Pawn)
	{
		AController* Controller = Pawn->GetController();
		if (Controller && Controller->PlayerState)
		{
			APlayerState* PS = Controller->PlayerState;
			const float NewScore = PS->GetScore() + (float)Points;
			PS->SetScore(NewScore);
			UE_LOG(LogTemp, Log, TEXT("Coin collected by %s — +%d points (score=%f)"), *PS->GetPlayerName(), Points, PS->GetScore());
			// Destroy the coin actor
			Destroy();
			return;
		}
	}

	// Fallback: log and destroy
	UE_LOG(LogTemp, Log, TEXT("Coin overlapped by %s but no player state found."), *GetNameSafe(OtherActor));
	Destroy();
}

