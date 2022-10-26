// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HitboxActor.generated.h"

UENUM(BlueprintType)
enum class EHitboxEnum : uint8
{
	HB_PROXIMITY	UMETA(DisplayName = "Proximity"),
	HB_STRIKE		UMETA(DisplayName = "Strike"),
	HB_HURTBOX		UMETA(DisplayName = "Hurtbox")
};

UCLASS()
class PROJECT_RGBX_API AHitboxActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHitboxActor();

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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
	EHitboxEnum hitboxType;

	//Hitbox Location instancing. allowing for us to declare the location of the hitbox in unreal using blueprints
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
	FVector hitboxLocation;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

