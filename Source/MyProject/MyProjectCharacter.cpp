// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyProjectCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AMyProjectCharacter

AMyProjectCharacter::AMyProjectCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
	// Double jump defaults
	JumpCount = 0;
	MaxJumpCount = 2;
	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;
	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
	// Health system
	MaxHealth = 100.f;
	CurrentHealth = MaxHealth;
	FallStartZ = 0.f;
	bIsFalling = false;
}

//////////////////////////////////////////////////////////////////////////
// Input

void AMyProjectCharacter::NotifyControllerChanged()

{
	Super::NotifyControllerChanged();

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void AMyProjectCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping (use our override to support double jump)
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AMyProjectCharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyProjectCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMyProjectCharacter::Look);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AMyProjectCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AMyProjectCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AMyProjectCharacter::Jump()
{
       if (GetCharacterMovement()->IsFalling())
       {
	       if (JumpCount < MaxJumpCount)
	       {
		       const float JumpZ = GetCharacterMovement()->JumpZVelocity;
		       LaunchCharacter(FVector(0.f, 0.f, JumpZ), false, true);
		       JumpCount++;
	       }
       }
       else
       {
	       // On ground: perform normal jump and count it
	       Super::Jump();
	       JumpCount = 1;
       }
}

void AMyProjectCharacter::ApplyDamage(float DamageAmount)
{
       CurrentHealth = FMath::Clamp(CurrentHealth - DamageAmount, 0.f, MaxHealth);
       UE_LOG(LogTemplateCharacter, Warning, TEXT("Damage taken: %f, Current Health: %f"), DamageAmount, CurrentHealth);
       if (CurrentHealth <= 0.f)
       {
	       // Handle death (to be expanded)
	       UE_LOG(LogTemplateCharacter, Error, TEXT("Character is dead!"));
       }
}

void AMyProjectCharacter::Landed(const FHitResult& Hit)
{
       Super::Landed(Hit);
       // Reset jump count so player can jump again
       JumpCount = 0;

       // --- Fall Damage Calculation ---
       if (bIsFalling)
       {
	       float FallEndZ = GetActorLocation().Z;
	       float FallDistance = FallStartZ - FallEndZ;
	       float FallDistanceMeters = FallDistance / 100.f; // Unreal units to meters
	       if (FallDistanceMeters > 5.f)
	       {
		       float OverDistance = FallDistanceMeters - 5.f;
		       int32 OverMeters = FMath::FloorToInt(OverDistance);
		       float Damage = 10.f + OverMeters * 10.f;
		       ApplyDamage(Damage);
	       }
	       bIsFalling = false;
       }
}

// Track start of fall
void AMyProjectCharacter::Tick(float DeltaSeconds)
{
       Super::Tick(DeltaSeconds);
       if (GetCharacterMovement()->IsFalling())
       {
	       if (!bIsFalling)
	       {
		       FallStartZ = GetActorLocation().Z;
		       bIsFalling = true;
	       }
       }
}
