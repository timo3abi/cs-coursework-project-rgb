// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Project_RGBXCharacter.generated.h"

UCLASS(config=Game)
class AProject_RGBXCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Side view camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* SideViewCameraComponent;

	/** Camera boom positioning the camera beside the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	void StartLP();
	void StartMP();
	void StartHP();
	void StartLK();
	void StartMK();
	void StartHK();

protected:

	/** Called for side to side input */
	void MoveRight(float Val);

	/** Handle touch inputs. */
	void TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location);

	/** Handle touch stop event. */
	void TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location);

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
		AActor* hurtbox;

	// How the player takes damage
	UFUNCTION(BlueprintCallable)
	void TakeDamage(float _damageAmount);

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

public:
	AProject_RGBXCharacter();

	/** Returns SideViewCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetSideViewCameraComponent() const { return SideViewCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
};
