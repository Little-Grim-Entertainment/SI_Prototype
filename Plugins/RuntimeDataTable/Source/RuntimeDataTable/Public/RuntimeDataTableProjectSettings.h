//Copyright Jared Therriault 2021, 2022

#pragma once

#include "RuntimeDataTableProjectSettings.generated.h"

UCLASS(config = Engine, defaultconfig)
class RUNTIMEDATATABLE_API URuntimeDataTableProjectSettings : public UObject
{
	GENERATED_BODY()
public:
	
	URuntimeDataTableProjectSettings(const FObjectInitializer& ObjectInitializer)
	{
		LogCharacterLimit = 25000;
		bPrintDisplayMessagesToLog = true;
		bPrintDisplayMessagesToScreen = false;
		bPrintWarningMessagesToLog = true;
		bPrintWarningMessagesToScreen = true;
		bPrintErrorMessagesToLog = true;
		bPrintErrorMessagesToScreen = true;

		DisplayMessagesOnScreenLifetime = 30.f;
		WarningMessagesOnScreenLifetime = 30.f;
		ErrorMessagesOnScreenLifetime = 30.f;
	}

	/**
	 *The number of characters that can be printed in any given print. -1 means no limit.
	 *This is useful when printing responses which can be enormous with very large sheets.
	 */
	UPROPERTY(Config, EditAnywhere, Category="Google Sheets Operator|Logging")
	int32 LogCharacterLimit;

	/**
	 *If true, "Display" type messages will be printed to the log. These will not display on screen.
	 *"Display" type messages are informational messages most end users don't have much interest in seeing.
	 */
	UPROPERTY(Config, EditAnywhere, Category="Google Sheets Operator|Logging")
	bool bPrintDisplayMessagesToLog;

	/**
	 *If true, "Display" type messages will be printed to the screen. These will not appear in the output log.
	 *"Display" type messages are informational messages most end users don't have much interest in seeing.
	 */
	UPROPERTY(Config, EditAnywhere, Category="Google Sheets Operator|Logging")
	bool bPrintDisplayMessagesToScreen;

	UPROPERTY(Config, EditAnywhere, Category="Google Sheets Operator|Logging")
	float DisplayMessagesOnScreenLifetime;

	/**
	 *If true, "Warning" type messages will be printed to the log. These will not display on screen.
	 *"Warning" type messages are important to most end users, but warnings are not fatal.
	 */
	UPROPERTY(Config, EditAnywhere, Category="Google Sheets Operator|Logging")
	bool bPrintWarningMessagesToLog;

	/**
	 *If true, "Warning" type messages will be printed to the screen. These will not appear in the output log.
	 *"Warning" type messages are important to most end users, but warnings are not fatal. 
	 */
	UPROPERTY(Config, EditAnywhere, Category="Google Sheets Operator|Logging")
	bool bPrintWarningMessagesToScreen;

	UPROPERTY(Config, EditAnywhere, Category="Google Sheets Operator|Logging")
	float WarningMessagesOnScreenLifetime;

	/**
	 *If true, "Error" type messages will be printed to the log. These will not display on screen.
	 *"Error" type messages are very important to the end user as they explain fatal issues.
	 */
	UPROPERTY(Config, EditAnywhere, Category="Google Sheets Operator|Logging")
	bool bPrintErrorMessagesToLog;

	/**
	 *If true, "Error" type messages will be printed to the screen. These will not appear in the output log.
	 *"Error" type messages are very important to the end user as they explain fatal issues.
	 */
	UPROPERTY(Config, EditAnywhere, Category="Google Sheets Operator|Logging")
	bool bPrintErrorMessagesToScreen;

	UPROPERTY(Config, EditAnywhere, Category="Google Sheets Operator|Logging")
	float ErrorMessagesOnScreenLifetime;

	/**
	 *Determines the beginning of the URL used to build a locator for a spreadsheet resource.
	 *Only change this parameter if you know you need to.
	 */
	UPROPERTY(Config, EditAnywhere, Category="Google Sheets Operator|Advanced|URI")
	FString GoogleSheetsUrlPrefix = "https://docs.google.com/spreadsheets/d/";

	/**
	 *Determines the beginning of the URL used to build a locator for a spreadsheet resource as it relates to the Google Sheets API.
	 *Only change this parameter if you know you need to.
	 */
	UPROPERTY(Config, EditAnywhere, Category="Google Sheets Operator|Advanced|URI")
	FString GoogleSheetsApiUrlPrefix = "https://sheets.googleapis.com/v4/spreadsheets/";

	/**
	 *The command used to perform a batch update of sheet properties.
	 *Only change this parameter if you know you need to.
	 */
	UPROPERTY(Config, EditAnywhere, Category="Google Sheets Operator|Advanced|URI")
	FString GoogleSheetsBatchUpdateCommand = ":batchUpdate";

	/**
	 *The command used to perform a batch update of sheet values.
	 *Only change this parameter if you know you need to.
	 */
	UPROPERTY(Config, EditAnywhere, Category="Google Sheets Operator|Advanced|URI")
	FString GoogleSheetsValuesBatchUpdateCommand = "/values:batchUpdate";

	/**
	 *The selector used to specify data as type CSV.
	 *Only change this parameter if you know you need to.
	 */
	UPROPERTY(Config, EditAnywhere, Category="Google Sheets Operator|Advanced|URI")
	FString GoogleSheetsMimeCsv = "text/csv";
};
