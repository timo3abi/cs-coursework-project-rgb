#pragma once

#include "SQLiteDatabase.h"

class DatabaseManager
{
public:
    DatabaseManager(FString Path, ESQLiteDatabaseOpenMode OpenMode);
    ~DatabaseManager();

    UFUNCTION(BlueprintCallable)
    bool SavePlayerPosition(int32 PlayerId, FVector Position);

    UFUNCTION(BlueprintCallable)
    FVector LoadPlayerPosition(int32 PlayerId);

private:
    FSQLiteDatabase* Database;

    FSQLitePreparedStatement SaveStatement;
    FSQLitePreparedStatement LoadStatement;
};