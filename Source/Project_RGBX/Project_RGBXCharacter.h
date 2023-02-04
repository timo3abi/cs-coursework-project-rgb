// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BaseGameInstance.h"
#include "GameFramework/Character.h"
#include "Project_RGBXCharacter.generated.h"

// So that We can flag directional inputs alongside attacks

UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	VE_Default			UMETA(DisplayName = "STATIONARY"),
	VE_MovingFWD		UMETA(DisplayName = "MOVING_FWD"),
	VE_MovingBWD		UMETA(DisplayName = "MOVING_BWD"),
	VE_DashingFWD		UMETA(DisplayName = "DASHING_FWD"),
	VE_DashingBWD		UMETA(DisplayName = "DASHING_BWD"),
	VE_Jumping			UMETA(DisplayName = "JUMPING"),
	VE_Crouching		UMETA(DisplayName = "CROUCHING"),
	VE_Blocking			UMETA(DisplayName = "BLOCKING"),
	VE_HitStunned		UMETA(DisplayName = "IN_HIT_STUN"),
	VE_Launched			UMETA(DisplayName = "LAUNCHED"),
	VE_KnockedDown		UMETA(DisplayName = "DOWNED"),
	VE_Invulnerable		UMETA(DisplayName = "INVULNERABLE"),
	VE_BlockStunned		UMETA(DisplayName = "IN_BLOCK_STUN")

};


USTRUCT(BlueprintType)
struct FInputData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
		FString inputTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
		float inputTime;


};

USTRUCT(BlueprintType)
struct FCmd
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
		FString CMDTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
		bool cmdUsed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
		TArray<FString> CMDReqs;

	UENUM(BlueprintType)
		enum class EMoveType : uint8
	{
		MT_BUFF			UMETA(DisplayName = "Buff"),
		MT_THROW		UMETA(DisplayName = "Throw"),
		MT_STRIKE		UMETA(DisplayName = "Strike"),
		MT_TELEPORT		UMETA(DisplayName = "Teleport"),
		MT_SUPER		UMETA(DisplayName = "Super"),
		MT_SPECIAL		UMETA(DisplayName = "Special")
	};


	//Damage that the hitbox applies to the target
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
		float hitboxDamage;

	//Damage that the hitbox applies to the target
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
		float pushbackDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
		float launchDistance;

	//The amount of hitstun time
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
		float hitstunTime;

	//The amount of blockstun time
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
		float blockstunTime;

	//Hitbox type instancing. determining what type of hitbox it is, this property can be referenced in unreal
	UENUM(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
		EMoveType MoveType;

	//Hitbox Location instancing. allowing for us to declare the location of the hitbox in unreal using blueprints
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
		FVector hitboxLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
		float inputTime;

};


USTRUCT(BlueprintType)
struct FMove
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
		FString moveName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
		bool moveUsed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
		TArray<FString> moveInput;

	UENUM(BlueprintType)
		enum class EMoveType : uint8
	{
		MT_BUFF			UMETA(DisplayName = "Buff"),
		MT_THROW		UMETA(DisplayName = "Throw"),
		MT_STRIKE		UMETA(DisplayName = "Strike"),
		MT_TELEPORT		UMETA(DisplayName = "Teleport"),
		MT_SUPER		UMETA(DisplayName = "Super"),
		MT_SPECIAL		UMETA(DisplayName = "Special")
	};


	//Damage that the hitbox applies to the target
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
		float hitboxDamage;

	//Damage that the hitbox applies to the target
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
		float pushbackDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
		float launchDistance;

	//The amount of hitstun time
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
		float hitstunTime;

	//The amount of blockstun time
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
		float blockstunTime;

	//Hitbox type instancing. determining what type of hitbox it is, this property can be referenced in unreal
	UENUM(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
		EMoveType MoveType;

	//Hitbox Location instancing. allowing for us to declare the location of the hitbox in unreal using blueprints
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
		FVector hitboxLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
		float inputTime;

};


UCLASS(config=Game)
class AProject_RGBXCharacter : public ACharacter
{
	GENERATED_BODY()

	// Side view camera 
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	//class UCameraComponent* SideViewCameraComponent;

	// Camera boom positioning the camera beside the character 
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	//class USpringArmComponent* CameraBoom;

	void StartLP();
	void StartMP();
	void StartHP();
	void StartLK();
	void StartMK();
	void StartHK();

	UFUNCTION(BlueprintCallable)
		void P2KLP();
	UFUNCTION(BlueprintCallable)
		void P2KMP();
	UFUNCTION(BlueprintCallable)
		void P2KHP();
	UFUNCTION(BlueprintCallable)
		void P2KLK();
	UFUNCTION(BlueprintCallable)
		void P2KMK();
	UFUNCTION(BlueprintCallable)
		void P2KHK();

	UFUNCTION(BlueprintCallable)
		void P2KCrouch();
	UFUNCTION(BlueprintCallable)
		void P2KStopCrouching();

	UFUNCTION(BlueprintCallable)
		void P2KJump();
	UFUNCTION(BlueprintCallable)
		void P2KStopJumping();
	UFUNCTION(BlueprintCallable)
		void P2KMoveRight(float _value);

protected:

	/** Called for side to side input */
	void MoveRight(float Value);

	/** Handle touch inputs. */
	//void TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location);

	/** Handle touch stop event. */
	//void TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location);

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface

	virtual void Tick(float DeltaTime) override;

	virtual void Jump() override;
	virtual void StopJumping() override;
	virtual void Landed(const FHitResult& Hit) override;

	UFUNCTION(BlueprintCallable)
	void StartCrouching();

	UFUNCTION(BlueprintCallable)
	void StopCrouching();

	UFUNCTION(BlueprintCallable)
	void StartBlocking();

	UFUNCTION(BlueprintCallable)
	void StopBlocking();
	
	UFUNCTION(BlueprintCallable)
	void ProximityHitboxCollision();  
	  
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
		AActor* hurtbox;

	// How the player takes damage
	UFUNCTION(BlueprintCallable)
	void TakeDamage(float _damageAmount,float _stunTime, float _blockstunTime,float _knockbackDistance, float _launchAmount );

	UFUNCTION(BlueprintCallable)
	void InitialiseCombo(float _startingDamage);

	UFUNCTION(BlueprintCallable)
	void UpdateComboInfo(float _totalDamage, float _damageBuffer );

	UFUNCTION(BlueprintCallable)
	void EndCombo();

	void BeginStun();

	void EndStun();

	void KnockBack(float _knockbackDistance, bool _isBlocking, float _launchAmount);

	UFUNCTION(BlueprintCallable)
	void AddInput(FInputData _inputData);

	UFUNCTION(BlueprintCallable)
	void CheckInputStackForCMD();

	UFUNCTION(BlueprintCallable)
	void StartCMD(FString _CMDTag);


	UFUNCTION(BlueprintCallable)
		void CheckInputStackForMove();

	UFUNCTION(BlueprintCallable)
		void StartMove(FString _moveName);

	UFUNCTION(BlueprintCallable)
	void WinRound();

	UFUNCTION(BlueprintCallable)
	void WinMatch();

	UFUNCTION(BlueprintImplementableEvent)
	void RoundStartNotice();

	UFUNCTION(BlueprintImplementableEvent)
	void RoundEndNotice();

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateRoundScore();

	UFUNCTION(BlueprintImplementableEvent)
	void AddInputIconToScreen(int _iconIndex, bool _toBeAdded = true);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TArray<FCmd> FighterCmds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TArray<FInputData> inputStack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Moves")
		TArray<FMove> Moveset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player References")
	AProject_RGBXCharacter * otherFighter;

	// direction the character is moving. instance of enum declared above
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fighter Data")
	ECharacterState characterState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fighter Data")
		EFighterTag WhatFighter;

	// Current amount of health
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float playerHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meter")
	float chroMeter;

	FTimerHandle stunTimerHandle;

	FTimerHandle inputStackTimeHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float stunTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	float damageBuffer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
		float totalDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
		int comboHits;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	bool comboUsed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	float stackLife;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float gravityScale;

	// Has the player used LP
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Normals")
	bool wasLpUsed;

	// Has the player used MP
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Normals")
	bool wasMpUsed;

	// Has the player used HP
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Normals")
	bool wasHpUsed;

	// Has the player used LK
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Normals")
	bool wasLkUsed;

	// Has the player used MK
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Normals")
	bool wasMkUsed;

	// Has the player used HK
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Normals")
	bool wasHkUsed;

	// Has the player used the Demo Commands
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Commands")
	bool wasdemoCMD;

	// Has the player used HK
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		bool wasMRUsed;

	// boolean variable for if the model is flipped
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Model")
	bool isFlipped;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Normals")
	bool hitLanded;

	//character model location
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Model")
	FTransform transform;

	// character model size
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Model")
	FVector scale;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	bool canMove;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
		bool canAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	bool isCrouched;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input Stack")
	bool isPlayer1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controller")
	bool is2PController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input Stack")
	bool AxisInputReleased;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	bool WonRound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
		bool lostRound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
		bool wonTheMatch;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	int RoundsWon;

public:
	AProject_RGBXCharacter();



	// Returns SideViewCameraComponent subobject 
	//FORCEINLINE class UCameraComponent* GetSideViewCameraComponent() const { return SideViewCameraComponent; }
	// Returns CameraBoom subobject 
	//FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
};
