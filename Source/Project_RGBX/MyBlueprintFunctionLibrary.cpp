// ©2022 Project RGBX, thxrty. Some Rights Reserved.

#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "MyBlueprintFunctionLibrary.h"


bool UMyBlueprintFunctionLibrary::FileSaveString(FString SaveTextB, FString FileNameB)
{
	return FFileHelper::SaveStringToFile(SaveTextB, *(FPaths::ProjectDir() + FileNameB));
}

bool UMyBlueprintFunctionLibrary::FileLoadString(FString FileNameA, FString& SaveTextA)
{
	return FFileHelper::LoadFileToString(SaveTextA, *(FPaths::ProjectDir() + FileNameA));
}

