// Copyright Epic Games, Inc. All Rights Reserved.

#include "Project_RGBXCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Project_RGBX/Project_RGBXGameMode.h"


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
	characterState = ECharacterState::VE_Default;
	scale = FVector(0.0f, 0.0f, 0.0f);
	gravityScale = GetCharacterMovement()->GravityScale;
	chroMeter = 0.00f;
	stunTime = 0.0f;
	stackLife = 1.0f;
	playerHealth = 1.00f;

	wasLpUsed = false;
	wasMpUsed = false;
	wasHpUsed = false;
	wasLkUsed = false;
	wasMkUsed = false;
	wasHkUsed = false;


	canMove = false;
	isCrouched = false;
	isFlipped = false;
	hitLanded = false;
	wasMRUsed = false;

	demoCMD.CMDTag = "Demo Command";
	demoCMD.CMDReqs.Add("1");
	demoCMD.CMDReqs.Add("1");
	demoCMD.CMDReqs.Add("2");
	wasdemoCMD = false;


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
	wasMRUsed = true;
	if (canMove && !isCrouched && characterState != ECharacterState::VE_Blocking && characterState != ECharacterState::VE_Crouching)
	{
		UE_LOG(LogTemp, Warning, TEXT("Moving by %f"), Value);
		if (characterState != ECharacterState::VE_Jumping && characterState != ECharacterState::VE_Launched)
		{
			if (!isFlipped)
			{
				if (Value > 0.20f)
				{
					characterState = ECharacterState::VE_MovingBWD;
					
				}
				else if (Value < -0.20f)
				{
					characterState = ECharacterState::VE_MovingFWD;
				}
				else// if (Value == 0.0f)
				{

					characterState = ECharacterState::VE_Default;
				}
				AddMovementInput(FVector(0.f, -1.f, 0.f), Value);
			}
			// if the character ends up being flipped the the directional inputs must also be flipped
			else if (isFlipped)
			{
				if (Value > 0.20f)
				{
					characterState = ECharacterState::VE_MovingFWD;
				}
				else if (Value < -0.20f)
				{
					characterState = ECharacterState::VE_MovingBWD;
					
				}
				else// if (Value == 0.0f)
				{
					characterState = ECharacterState::VE_Default;
				}
				AddMovementInput(FVector(0.f, -1.f, 0.f), Value);
			}

		}
	}
}

void AProject_RGBXCharacter::Jump()
{
	ACharacter::Jump();
	characterState = ECharacterState::VE_Jumping;
	UE_LOG(LogTemp, Warning, TEXT("Jumping"));
}

void AProject_RGBXCharacter::StopJumping()
{
	ACharacter::StopJumping();
}

void AProject_RGBXCharacter::Landed(const FHitResult& Hit)
{
	if (characterState == ECharacterState::VE_Launched || characterState == ECharacterState::VE_Jumping)
	{
		GetCharacterMovement()->GravityScale = gravityScale;
		characterState = ECharacterState::VE_Default;
	}
}

void AProject_RGBXCharacter::StartCrouching()
{
	isCrouched = true;
	canMove = false;
	characterState = ECharacterState::VE_Crouching;
}

void AProject_RGBXCharacter::StopCrouching()
{
	isCrouched = false;
	canMove = true;
	characterState = ECharacterState::VE_Default;
}

void AProject_RGBXCharacter::StartBlocking()
{
	characterState = ECharacterState::VE_Blocking;
}

void AProject_RGBXCharacter::StopBlocking()
{
	characterState = ECharacterState::VE_Blocking;
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

void AProject_RGBXCharacter::ProximityHitboxCollision()
{
	UE_LOG(LogTemp, Warning, TEXT("called"));
	if ((characterState == ECharacterState::VE_MovingBWD && !isFlipped) || (characterState == ECharacterState::VE_MovingBWD && isFlipped))
	{
		UE_LOG(LogTemp, Warning, TEXT("Auto-blocking"));
		characterState = ECharacterState::VE_Blocking;
	}
}

void AProject_RGBXCharacter::TakeDamage(float _damageAmount, float _stunTime, float _blockstunTime, float _knockbackDistance, float _launchAmount)
{
	if (characterState != ECharacterState::VE_Blocking)
	{

		UE_LOG(LogTemp, Warning, TEXT("Taking %f points of damage"), _damageAmount);
		playerHealth -= _damageAmount;
		chroMeter += _damageAmount * 0.60f;


		stunTime = _stunTime;
		if (stunTime > 0.0f)
		{		
		characterState = ECharacterState::VE_HitStunned;
		BeginStun();
		}


		if (otherFighter)
		{
			otherFighter->hitLanded = true;
			otherFighter->KnockBack(_knockbackDistance, false,0.0f);
			otherFighter->chroMeter += _damageAmount * 0.30f;
		}
		KnockBack(_knockbackDistance, false, _launchAmount);
	}
	else
	{
		float chipDamage = _damageAmount * 0.2f;
		UE_LOG(LogTemp, Warning, TEXT("Taking %f points of chip damage"), chipDamage);
		playerHealth -= chipDamage;
		chroMeter += _damageAmount * 0.80f;

		stunTime = _blockstunTime;
		if (stunTime > 0.0f)
		{
			BeginStun();

		}

		else
		{
			characterState = ECharacterState::VE_Default;
		}

		if (otherFighter)
		{
			otherFighter->hitLanded = false;
			otherFighter->KnockBack(_knockbackDistance, false,0.0f);
			otherFighter->chroMeter += _damageAmount * 0.50f;
		}
		KnockBack(_knockbackDistance, true, 0.0f);
	}

	if (playerHealth < 0.00f)
	{
		playerHealth = 0.00f;
	}
}

void AProject_RGBXCharacter::KnockBack(float _knockbackDistance, bool _isBlocking, float _launchAmount)
{
	if (_isBlocking)
	{
		if (isFlipped)
		{
			// inbuilt unreal function that applies a force to an object of the character class
			LaunchCharacter(FVector(0.0f, -_knockbackDistance * 2.0f, 0.0f), false, false);
		}
		else
		{
			LaunchCharacter(FVector(0.0f, _knockbackDistance * 2.0f, 0.0f), false, false);
		}
	}
	else
	{
		if (_launchAmount > 0.0f)
		{
			GetCharacterMovement()->GravityScale *= 0.7;
			characterState = ECharacterState::VE_Launched;
		}
		if (isFlipped)
		{
			LaunchCharacter(FVector(0.0f, -_knockbackDistance, _launchAmount), false, false);
		}
		else
		{
			LaunchCharacter(FVector(0.0f, _knockbackDistance, _launchAmount), false, false);
		}
	}
}

void AProject_RGBXCharacter::BeginStun()
{
	canMove = false;
	GetWorld()->GetTimerManager().SetTimer(stunTimerHandle, this, &AProject_RGBXCharacter::EndStun, stunTime, false);
}

void AProject_RGBXCharacter::EndStun()
{
	canMove = true;
	if (characterState != ECharacterState::VE_Launched)
	{
		characterState = ECharacterState::VE_Default;
	}
}

void AProject_RGBXCharacter::AddInput(FInputData _inputData)
{
	inputStack.Add(_inputData);
	CheckInputStackForCMD();
}

void AProject_RGBXCharacter::CheckInputStackForCMD()
{
	int ValidOrderCount = 0;

	for (int CMDinput = 0; CMDinput < demoCMD.CMDReqs.Num(); ++CMDinput)
	{
		for (int input = 0; input < inputStack.Num(); ++input)
		{
			if (input + ValidOrderCount < inputStack.Num())
			{
				if (inputStack[input + ValidOrderCount].inputTag.Compare(demoCMD.CMDReqs[CMDinput]) == 0)
				{
					UE_LOG(LogTemp, Warning, TEXT("Input added to CMD sequence"));
					++ValidOrderCount;

					if (ValidOrderCount == demoCMD.CMDReqs.Num())
					{
						StartCMD(demoCMD.CMDTag);
					}

					break;
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("CMD sequence broken"));
					ValidOrderCount = 0;
				}
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("CMD sequence incomplete"));
				ValidOrderCount = 0;
			}
		}
	}
}

void AProject_RGBXCharacter::StartCMD(FString _CMDtag)
{
	if (_CMDtag.Compare(demoCMD.CMDTag) == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Using CMD: &s."), *_CMDtag);
		wasdemoCMD = true;
	}
}

void AProject_RGBXCharacter::RemoveInput()
{

}

// the tick function is called every frame of the game session
void AProject_RGBXCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (characterState != ECharacterState::VE_Jumping)
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
