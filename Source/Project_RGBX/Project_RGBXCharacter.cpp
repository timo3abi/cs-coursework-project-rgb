// Copyright Epic Games, Inc. All Rights Reserved.

#include "Project_RGBXCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <Project_RGBX/Project_RGBXGameMode.h>

AProject_RGBXCharacter::AProject_RGBXCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Create a camera boom attached to the root (capsule)
	//CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	//CameraBoom->SetupAttachment(RootComponent);
	//CameraBoom->SetUsingAbsoluteRotation(true); // Rotation of the character should not affect rotation of boom
	//CameraBoom->bDoCollisionTest = false;
	//CameraBoom->TargetArmLength = 500.f;
	//CameraBoom->SocketOffset = FVector(0.f,0.f,75.f);
	//CameraBoom->SetRelativeRotation(FRotator(0.f,180.f,0.f));

	// Create a camera and attach to boom
	//SideViewCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
	//SideViewCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	//SideViewCameraComponent->bUsePawnControlRotation = false; // We don't want the controller rotating the camera

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = false; // Face in the direction we are moving.. i turned this off as we want the characters to always face each other anot freely rotate
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->GravityScale = 2.f;
	GetCharacterMovement()->AirControl = 0.80f;
	GetCharacterMovement()->JumpZVelocity = 1000.f;
	GetCharacterMovement()->GroundFriction = 3.f;
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	GetCharacterMovement()->MaxFlySpeed = 600.f;


	otherFighter = nullptr;

	hurtbox = nullptr;

	directionalInput = EDirectionalInput::VE_Default;

	playerHealth = 1.00f;

	scale = FVector(0.0f, 0.0f, 0.0f);

	canMove = false;
	isCrouched = false;

	isFlipped = false;
	hitLanded = false;

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
	if (auto gameMode = Cast<AProject_RGBXGameMode>(GetWorld()->GetAuthGameMode()))
	{
		if (gameMode->player1==this)
		{
			// set up gameplay key bindings
			PlayerInputComponent->BindAction("Jump1", IE_Pressed, this, &AProject_RGBXCharacter::Jump);
			PlayerInputComponent->BindAction("Jump1", IE_Released, this, &AProject_RGBXCharacter::StopJumping);
			PlayerInputComponent->BindAction("CrouchP1", IE_Released, this, &AProject_RGBXCharacter::StartCrouching);
			PlayerInputComponent->BindAction("CrouchP1", IE_Released, this, &AProject_RGBXCharacter::StopCrouching);
			PlayerInputComponent->BindAxis("MoveRightP1", this, &AProject_RGBXCharacter::MoveRight);

			PlayerInputComponent->BindAction("LP1", IE_Pressed, this, &AProject_RGBXCharacter::StartLP);
			PlayerInputComponent->BindAction("MP1", IE_Pressed, this, &AProject_RGBXCharacter::StartMP);
			PlayerInputComponent->BindAction("HP1", IE_Pressed, this, &AProject_RGBXCharacter::StartHP);
			PlayerInputComponent->BindAction("LK1", IE_Pressed, this, &AProject_RGBXCharacter::StartLK);
			PlayerInputComponent->BindAction("MK1", IE_Pressed, this, &AProject_RGBXCharacter::StartMK);
			PlayerInputComponent->BindAction("HK1", IE_Pressed, this, &AProject_RGBXCharacter::StartHK);
		}
		else
		{
			// set up gameplay key bindings
			PlayerInputComponent->BindAction("Jump2", IE_Pressed, this, &AProject_RGBXCharacter::Jump);
			PlayerInputComponent->BindAction("Jump2", IE_Released, this, &AProject_RGBXCharacter::StopJumping);
			PlayerInputComponent->BindAction("CrouchP2", IE_Released, this, &AProject_RGBXCharacter::StartCrouching);
			PlayerInputComponent->BindAction("CrouchP2", IE_Released, this, &AProject_RGBXCharacter::StopCrouching);
			PlayerInputComponent->BindAxis("MoveRightP2", this, &AProject_RGBXCharacter::MoveRight);

			PlayerInputComponent->BindAction("LP2", IE_Pressed, this, &AProject_RGBXCharacter::StartLP);
			PlayerInputComponent->BindAction("MP2", IE_Pressed, this, &AProject_RGBXCharacter::StartMP);
			PlayerInputComponent->BindAction("HP2", IE_Pressed, this, &AProject_RGBXCharacter::StartHP);
			PlayerInputComponent->BindAction("LK2", IE_Pressed, this, &AProject_RGBXCharacter::StartLK);
			PlayerInputComponent->BindAction("MK2", IE_Pressed, this, &AProject_RGBXCharacter::StartMK);
			PlayerInputComponent->BindAction("HK2", IE_Pressed, this, &AProject_RGBXCharacter::StartHK);
		}
	}
}

// when the character moves fwds/bwds the enum is set accordingly meaning we can script blueprint for directional input functionality
void AProject_RGBXCharacter::MoveRight(float Value)
{
	if (canMove && !isCrouched)
	{
		if (directionalInput != EDirectionalInput::VE_Jumping)
		{
			if (!isFlipped)
			{
				if (Value > 0.20f)
				{
					UE_LOG(LogTemp, Warning, TEXT("Moving by %f"), Value);
					directionalInput = EDirectionalInput::VE_MovingLeft;
				}
				else if (Value < -0.20f)
				{
					UE_LOG(LogTemp, Warning, TEXT("Moving by %f"), Value);
					directionalInput = EDirectionalInput::VE_MovingRight;
				}
				else
				{
					directionalInput = EDirectionalInput::VE_Default;
				}
				AddMovementInput(FVector(0.f, -1.f, 0.f), Value);
			}
			// if the character ends up being flipped the the directional inputs must also be flipped
			else if (isFlipped)
			{
				if (Value > 0.20f)
				{
					UE_LOG(LogTemp, Warning, TEXT("Moving by %f"), Value);
					directionalInput = EDirectionalInput::VE_MovingRight;
				}
				else if (Value < -0.20f)
				{
					UE_LOG(LogTemp, Warning, TEXT("Moving by %f"), Value);
					directionalInput = EDirectionalInput::VE_MovingLeft;
				}
				else
				{
					directionalInput = EDirectionalInput::VE_Default;
				}
				AddMovementInput(FVector(0.f, -1.f, 0.f), Value);
			}

		}
	}
}

void AProject_RGBXCharacter::Jump()
{
	ACharacter::Jump();
	directionalInput = EDirectionalInput::VE_Jumping;
}

void AProject_RGBXCharacter::StopJumping()
{
	ACharacter::StopJumping();
}

void AProject_RGBXCharacter::Landed(const FHitResult& Hit)
{
	directionalInput = EDirectionalInput::VE_Default;
}

void AProject_RGBXCharacter::StartCrouching()
{
	isCrouched = true;
	directionalInput = EDirectionalInput::VE_Crouching;
}

void AProject_RGBXCharacter::StopCrouching()
{
	isCrouched = false;
	directionalInput = EDirectionalInput::VE_Default;
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
}

void AProject_RGBXCharacter::P2KLP()
{
	StartLP();
}

void AProject_RGBXCharacter::P2KMP()
{
	StartMP();
}

void AProject_RGBXCharacter::P2KHP()
{
	StartHP();
}

void AProject_RGBXCharacter::P2KLK()
{
	StartLK();
}

void AProject_RGBXCharacter::P2KMK()
{
	StartMK();
}

void AProject_RGBXCharacter::P2KHK()
{
	StartHK();
}

void AProject_RGBXCharacter::P2KJump()
{
	Jump();
}

void AProject_RGBXCharacter::P2KStopJumping()
{
	StopJumping();
}

void AProject_RGBXCharacter::P2KCrouch()
{
	StartCrouching();
}

void AProject_RGBXCharacter::P2KStopCrouching()
{
	StopCrouching();
}

void AProject_RGBXCharacter::P2KMoveRight(float _value)
{
	MoveRight( _value);
}



void AProject_RGBXCharacter::TakeDamage(float _damageAmount)
{
	UE_LOG(LogTemp, Warning, TEXT("Taking %f points of damage"), _damageAmount);

	playerHealth -= _damageAmount;

	otherFighter->hitLanded = true;

	if (playerHealth < 0.00f)
	{
		playerHealth = 0.00f;
	}
}

// the tick function is called every frame of the game session
void AProject_RGBXCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	{
		if (otherFighter)
		{
			if (auto characterMovement = GetCharacterMovement())
			{
				if (auto enemyMovement = otherFighter->GetCharacterMovement())
				{
					// if the other fighter is to the right 
					if (enemyMovement->GetActorLocation().Y >= characterMovement->GetActorLocation().Y)
					{
						if (isFlipped)
						{
							if (auto mesh = GetCapsuleComponent()->GetChildComponent(1))
							{
								transform = mesh->GetRelativeTransform();
								scale = transform.GetScale3D();
								scale.Y = -1;
								transform.SetScale3D(scale);
								mesh->SetRelativeTransform(transform);

							}
							isFlipped = false;

						}
					}
					else
					{
						if (!isFlipped)
						{
							if (auto meshComponent = GetCapsuleComponent()->GetChildComponent(1))
							{
								transform = meshComponent->GetRelativeTransform();
								scale = transform.GetScale3D();
								scale.Y = 1;
								transform.SetScale3D(scale);
								meshComponent->SetRelativeTransform(transform);

							}
							isFlipped = true;
						}

					}
				}
			}
		}
	}
}
