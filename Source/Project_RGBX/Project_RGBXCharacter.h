// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Project_RGBXCharacter.generated.h"

// So that We can flag directional inputs alongside attacks

UENUM(BlueprintType)
enum class EDirectionalInput : uint8
{
	VE_Default			UMETA(DisplayName = "STATIONARY"),
	VE_MovingRight		UMETA(DisplayName = "MOVING_RIGHT"),
	VE_MovingLeft		UMETA(DisplayName = "MOVING_LEFT"),
	VE_Jumping			UMETA(DisplayName = "JUMPING"),
	VE_Crouching		UMETA(DisplayName = "Crouching")
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


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
		AActor* hurtbox;

	// How the player takes damage
	UFUNCTION(BlueprintCallable)
	void TakeDamage(float _damageAmount);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player References")
	AProject_RGBXCharacter * otherFighter;

	// direction the character is moving. instance of enum declared above
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	EDirectionalInput directionalInput;

	// Current amount of health
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float playerHealth;

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	bool isCrouched;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controller")
	bool is2PController;

public:
	AProject_RGBXCharacter();



	// Returns SideViewCameraComponent subobject 
	//FORCEINLINE class UCameraComponent* GetSideViewCameraComponent() const { return SideViewCameraComponent; }
	// Returns CameraBoom subobject 
	//FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
};
