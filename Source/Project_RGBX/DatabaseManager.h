// ©2022 Project RGBX, thxrty. Some Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DatabaseManager.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class PROJECT_RGBX_API UDatabaseManager : public UObject
{
public:
	UFUNCTION(BlueprintCallable)
	void SampleActionQuery();
	UFUNCTION(BlueprintCallable)
	void SampleSelectQuery();

protected:


private:

	GENERATED_BODY()
};
