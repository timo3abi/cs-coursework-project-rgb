// ©2022 Project RGBX, thxrty. Some Rights Reserved.


#include "DatabaseManager.h"
#include "SQLiteDatabase.h"

void UDatabaseManager::SampleActionQuery()
{
	/* Database file in the content subfolder we created. */
	const FString DbFilePath = FPaths::ProjectContentDir() + "Database/MyDatabase.db";

	/* Ugly inline SQL declaration, its just an example. */
	const FString ExampleSQL = TEXT("UPDATE TestTable SET FakeField = 17 WHERE ID = @ID;");

	/* SQL parameter name */
	const FString ExampleParameterName = TEXT("@ID");
	FSQLiteDatabase* MyDb = new FSQLiteDatabase();
	/* Open database. */
	if (MyDb->Open(*DbFilePath, ESQLiteDatabaseOpenMode::ReadWrite))
	{
		FSQLitePreparedStatement* PreparedStatement = new FSQLitePreparedStatement();
		/* Initialize prepared statement. */
		if (PreparedStatement->Create(*MyDb, *ExampleSQL, ESQLitePreparedStatementFlags::Persistent))
		{
			/* Bind parameters to values. */
			PreparedStatement->SetBindingValueByName(*ExampleParameterName, 1);

			bool Success = PreparedStatement->Execute();

			/* Might want to check the return value, to see if it actually was destroyed. */
			PreparedStatement->Destroy();
			delete PreparedStatement;
		}
		MyDb->Close();
		delete MyDb;
	}

}

void UDatabaseManager::SampleSelectQuery()
{
	/* Database file in the content subfolder we created. */
	const FString DbFilePath = FPaths::ProjectContentDir() + "Database/MyDatabase.db";

	/* Ugly inline SQL declaration, its just an example. */
	const FString ExampleSQL = TEXT("SELECT * FROM TestTable T WHERE T.ID = @ID;");

	/* SQL parameter name */
	const FString ExampleParameterName = TEXT("@ID");
	FSQLiteDatabase* MyDb = new FSQLiteDatabase();
	/* Open database. */
	if (MyDb->Open(*DbFilePath, ESQLiteDatabaseOpenMode::ReadWrite))
	{
		FSQLitePreparedStatement* PreparedStatement = new FSQLitePreparedStatement();
		/* Initialize prepared statement. */
		if (PreparedStatement->Create(*MyDb, *ExampleSQL, ESQLitePreparedStatementFlags::Persistent))
		{
			/* Bind parameters to values. */
			PreparedStatement->SetBindingValueByName(*ExampleParameterName, 1);

			/* Loop while there are result rows to process... */
			while (PreparedStatement->Step() == ESQLitePreparedStatementStepResult::Row)
			{
				/* Example of getting the data for a column. */
				int64 ExampleIntValue;
				if (PreparedStatement->GetColumnValueByIndex(0, ExampleIntValue))
				{
					// value is good, do something with it...
				}
			}

			/* Might want to check the return value, to see if it actually was destroyed. */
			PreparedStatement->Destroy();
			delete PreparedStatement;
		}
		MyDb->Close();
		delete MyDb;
	}
}