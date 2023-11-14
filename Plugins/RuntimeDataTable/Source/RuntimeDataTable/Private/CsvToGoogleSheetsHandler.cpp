// Copyright Jared Therriault 2019, 2022

#include "CsvToGoogleSheetsHandler.h"

#include "EasyCsv.h"
#include "RuntimeDataTableModule.h"

void FCsvToGoogleSheetsHandler::InferSpecifiedRangeFromTitleAndStartingCell(const FString& InTitle,
                                                                            const FString& InStartingCell)
{
	if (InTitle.IsEmpty())
	{
		return;
	}

	if (!ValidateCellIsNotRangeOrEmpty(InStartingCell))
	{
		return;
	}

	// Do this to set the starting cell which is required for GetActualEndingCell
	SpecifiedRange = FString::Printf(TEXT("'%s'!%s:%s"), *InTitle, *InStartingCell, *InStartingCell);

	FString EndingCell;
	GetActualEndingCell(EndingCell);
	SpecifiedRange = FString::Printf(TEXT("'%s'!%s:%s"), *InTitle, *InStartingCell, *EndingCell);
}

bool FCsvToGoogleSheetsHandler::ValidateCellIsNotRangeOrEmpty(const FString InCell)
{
	if (InCell.Contains("!") || InCell.Contains(":"))
	{
		FRuntimeDataTableModule::Print(FString::Printf(
			TEXT("%hs: Cell is input as range, but ranges are not permitted."),
			__FUNCTION__), FRuntimeDataTableModule::ELogType::Error);
	
		return false;
	}

	if (InCell.IsEmpty())
	{
		FRuntimeDataTableModule::Print(FString::Printf(
			TEXT("%hs: Cell is input as empty."),
			__FUNCTION__), FRuntimeDataTableModule::ELogType::Error);

		return false;
	}

	return true;
}

bool FCsvToGoogleSheetsHandler::GetActualEndingCell(FString& OutCell)
{
	const FString StartingCell = GetStartingCell();

	int32 ColumnIndex = -1;
	int32 RowIndex = -1;

	if (A1_CellToColumnAndRowIndices(StartingCell, ColumnIndex, RowIndex))
	{
		const int32 LastColumnIndex = ColumnIndex + (GetColumnCount() - 1);
		const int32 LastRowIndex = RowIndex + (GetRowCount() - 1);

		OutCell = GetCellInA1_NotationFromColumnAndRowIndices(LastColumnIndex, LastRowIndex);

		return true;
	}

	return false;
}

FString FCsvToGoogleSheetsHandler::GetStartingCell()
{
	FString StartingCell;
	FString EndingCell;

	if (SpecifiedRange.Split(":", &StartingCell, &EndingCell))
	{
		if (StartingCell.Contains("!"))
		{
			FString SheetName;

			StartingCell.Split("!", &SheetName, &StartingCell);
		}

		return StartingCell;
	}

	return SpecifiedRange;
}

bool FCsvToGoogleSheetsHandler::A1_CellToColumnAndRowIndices(const FString& InCell, int32& OutColumnIndex, int32& OutRowIndex)
{
	if (!ValidateCellIsNotRangeOrEmpty(InCell))
	{
		return false;
	}

	FString ColumnLetterIndex;
	FString RowIndexString;

	for (const wchar_t Char : InCell.GetCharArray())
	{
		FString CharAsString;
		CharAsString.AppendChar(Char);

		if (CharAsString.IsNumeric())
		{
			RowIndexString += CharAsString;
		}
		else
		{
			ColumnLetterIndex += CharAsString;
		}
	}

	OutColumnIndex = ColumnLetterToIndex(ColumnLetterIndex);

	if (OutColumnIndex > 0)
	{
		OutRowIndex = FCString::Atoi(*RowIndexString);

		return OutRowIndex > 0;
	}

	return false;
}

FString FCsvToGoogleSheetsHandler::GetCellInA1_NotationFromColumnAndRowIndices(int32 InColumnNumber, int32 InRowNumber)
{
	if (InColumnNumber < 1)
	{
		InColumnNumber = 1;
	}

	if (InRowNumber < 1)
	{
		InRowNumber = 1;
	}

	return FString::Printf(TEXT("%s%i"), *ColumnIndexToLetter(InColumnNumber), InRowNumber);
}

int32 FCsvToGoogleSheetsHandler::ColumnLetterToIndex(const FString& InColumnLetter)
{
	if (InColumnLetter.TrimStartAndEnd().IsEmpty() || InColumnLetter.IsNumeric())
	{
		FRuntimeDataTableModule::Print(FString::Printf(
			TEXT("%hs: Input is either empty or numeric. Aborting operation. Character: %s"),
			__FUNCTION__, *InColumnLetter), FRuntimeDataTableModule::ELogType::Error);
		return -1;
	}

	FString ColumnLetterAsUppercase = InColumnLetter.ToUpper();

	const TArray<FString>& Alphabet = GetAlphabet();
	const int32 AlphabetCount = Alphabet.Num(); // Count of English Alphabet letters

	int32 NewIndex = 0;

	uint8 Count = 0;
	while (ColumnLetterAsUppercase.Len() > 0)
	{
		const FString& LastLetter = ColumnLetterAsUppercase.Right(1);
		ColumnLetterAsUppercase = ColumnLetterAsUppercase.LeftChop(1);
		const int32 KeyIndex = Alphabet.IndexOfByKey(LastLetter);
		if (KeyIndex < 0)
		{
			FRuntimeDataTableModule::Print(
				FString::Printf(
					TEXT("%hs: Only letters found in the English alphabet are considered for converting to index. Character: %s"),
					__FUNCTION__, *LastLetter), FRuntimeDataTableModule::ELogType::Error);
			return -1;
		}
		Count++;

		switch (Count)
		{
		default:
			checkNoEntry();

		case 1:
		
			NewIndex += KeyIndex;
			break;

		case 2:
			NewIndex += (KeyIndex + 1) * AlphabetCount;
			break;

		case 3:
			NewIndex += (KeyIndex + 1) * AlphabetCount * AlphabetCount;
			return NewIndex; // we return so we don't even consider counts greater than 3
		}
	}

	return NewIndex + 1;
}

FString FCsvToGoogleSheetsHandler::ColumnIndexToLetter(const int32 Index)
{ 
	FString LetterRep;
	if (Index < 1 || Index > MaxColumnCount - 1)
	{
		FRuntimeDataTableModule::Print(FString::Printf(
			TEXT("%hs: Input is either less than 1 or greater than %i. Aborting operation. Input is: %i"), 
			__FUNCTION__, MaxColumnCount - 1, Index), FRuntimeDataTableModule::ELogType::Error);
		return LetterRep;
	}

	int32 ZeroBasedIndex = Index - 1;

	const TArray<FString>& Alphabet = GetAlphabet();
	const int32 AlphabetCount = Alphabet.Num(); // Count of English Alphabet letters
	const int32 Algo =
		(int32)FMath::Floor(FMath::LogX( (double)AlphabetCount, ((double)ZeroBasedIndex) * ((double)AlphabetCount - 1) / (double)AlphabetCount + 1));
	ZeroBasedIndex -= (int32)(FMath::Pow((double)AlphabetCount, (double)Algo) - 1) * AlphabetCount / (AlphabetCount - 1);
	for (int i = Algo + 1; ZeroBasedIndex + i > 0; i--)
	{
		LetterRep = Alphabet[ZeroBasedIndex % AlphabetCount] + LetterRep;
		ZeroBasedIndex /= AlphabetCount;
	}
	return LetterRep;
}

FCsvToGoogleSheetsHandler FCsvToGoogleSheetsHandler::CsvToSheetTabData(FString InCSVString)
{
	// Provision string
	
	// Remove encapsulating parentheses
	if (InCSVString.StartsWith("(")) { InCSVString = InCSVString.RightChop(1); }
	if (InCSVString.EndsWith(")")) { InCSVString = InCSVString.LeftChop(1); }

	FCsvToGoogleSheetsHandler NewSheetTabData;
	NewSheetTabData.ArrayValues = UEasyCsv::ReadCsv(InCSVString);

	return NewSheetTabData;
}

FString FCsvToGoogleSheetsHandler::GetAllArrayValuesAsJsonString(const bool bAddValuesKey,
	const bool bWrapInCurlyBraces) const
{
	FString FinalJson = "[";
	
	for (const TArray<FString>& Row : ArrayValues)
	{
		FinalJson += "[";

		for (const FString& Cell : Row)
		{
			FinalJson += FString::Printf(TEXT("\"%s\","), *Cell);
		}

		// Remove last comma
		FinalJson = FinalJson.LeftChop(1);

		FinalJson += "],";
	}
	
	// Remove last comma
	FinalJson = FinalJson.LeftChop(1);
	
	FinalJson += "]";

	if (bAddValuesKey)
	{
		FinalJson = "\"values\": " + FinalJson;
	}

	if (bWrapInCurlyBraces)
	{
		FinalJson = "{" + FinalJson + "}";
	}

	return FinalJson;
}
