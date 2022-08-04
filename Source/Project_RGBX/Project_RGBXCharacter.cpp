// Copyright Epic Games, Inc. All Rights Reserved.

#include "Project_RGBXCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AProject_RGBXCharacter::AProject_RGBXCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Create a camera boom attached to the root (capsule)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Rotation of the character should not affect rotation of boom
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->TargetArmLength = 500.f;
	CameraBoom->SocketOffset = FVector(0.f,0.f,75.f);
	CameraBoom->SetRelativeRotation(FRotator(0.f,180.f,0.f));

	// Create a camera and attach to boom
	SideViewCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
	SideViewCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	SideViewCameraComponent->bUsePawnControlRotation = false; // We don't want the controller rotating the camera

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Face in the direction we are moving..
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->GravityScale = 2.f;
	GetCharacterMovement()->AirControl = 0.80f;
	GetCharacterMovement()->JumpZVelocity = 1000.f;
	GetCharacterMovement()->GroundFriction = 3.f;
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	GetCharacterMovement()->MaxFlySpeed = 600.f;

	playerHealth = 1.00f;
	wasLpUsed = false;
	wasMpUsed = false;
	wasHpUsed = false;
	wasLkUsed = false;
	wasMkUsed = false;
	wasHkUsed = false;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void AProject_RGBXCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAxis("MoveRight", this, &AProject_RGBXCharacter::MoveRight);

	PlayerInputComponent->BindAction("LP", IE_Pressed, this, &AProject_RGBXCharacter::StartLP);
	PlayerInputComponent->BindAction("MP", IE_Pressed, this, &AProject_RGBXCharacter::StartMP);
	PlayerInputComponent->BindAction("HP", IE_Pressed, this, &AProject_RGBXCharacter::StartHP);
	PlayerInputComponent->BindAction("LK", IE_Pressed, this, &AProject_RGBXCharacter::StartLK);
	PlayerInputComponent->BindAction("MK", IE_Pressed, this, &AProject_RGBXCharacter::StartMK);
	PlayerInputComponent->BindAction("HK", IE_Pressed, this, &AProject_RGBXCharacter::StartHK);

	PlayerInputComponent->BindTouch(IE_Pressed, this, &AProject_RGBXCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AProject_RGBXCharacter::TouchStopped);
}

void AProject_RGBXCharacter::MoveRight(float Value)
{
	// add movement in that direction
	AddMovementInput(FVector(0.f,-1.f,0.f), Value);
}

void AProject_RGBXCharacter::TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	// jump on any touch
	Jump();
}

void AProject_RGBXCharacter::TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	StopJumping();
}

void AProject_RGBXCharacter::StartLP()
{
	UE_LOG(LogTemp, Warning, TEXT("Using LP"));
	wasLpUsed = true;
}

void AProject_RGBXCharacter::StartMP()
{
	UE_LOG(LogTemp, Warning, TEXT("Using MP"));
	wasMpUsed = true;
}

void AProject_RGBXCharacter::StartHP()
{
	UE_LOG(LogTemp, Warning, TEXT("Using HP"));
	wasHpUsed = true;

}

void AProject_RGBXCharacter::StartLK()
{
	UE_LOG(LogTemp, Warning, TEXT("Using LK"));
	wasLkUsed = true;
}

void AProject_RGBXCharacter::StartMK()
{
	UE_LOG(LogTemp, Warning, TEXT("Using MK"))
	wasMkUsed = true;

}

void AProject_RGBXCharacter::StartHK()
{
	UE_LOG(LogTemp, Warning, TEXT("Using HK"));
	wasHkUsed = true;
	//TakeDamage(0.05f);
}

void AProject_RGBXCharacter::TakeDamage(float _damageAmount)
{
	UE_LOG(LogTemp, Warning, TEXT("Taking %f points of damage"), _damageAmount);
	playerHealth -= _damageAmount;

	if (playerHealth < 0.00f)
	{
		playerHealth = 0.00f;
	}
}