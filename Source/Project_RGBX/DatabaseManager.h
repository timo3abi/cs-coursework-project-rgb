// ©2022 Project RGBX, thxrty. Some Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"


/* Sample SQLite database access code. */
UCLASS()
class TUTORIALDEMO_API UDatabaseManager : public UObject
{
public:
	UFUNCTION(BlueprintCallable)
	void UpdateUsers();

	void SampleSelectQuery();

protected:


private:

	GENERATED_BODY()
};
