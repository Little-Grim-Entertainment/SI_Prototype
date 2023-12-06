// Copyright Jared Therriault 2019, 2022

#pragma once

#include "Containers/UnrealString.h"

struct FCsvToGoogleSheetsHandler
{
	void InferSpecifiedRangeFromTitleAndStartingCell(
		const FString& InTitle, const FString& InStartingCell);

	static bool ValidateCellIsNotRangeOrEmpty(const FString InCell);

	bool GetActualEndingCell(FString& OutCell);

	FString GetStartingCell();

	static bool A1_CellToColumnAndRowIndices(const FString& InCell, int32& OutColumnIndex, int32& OutRowIndex);

	static FString GetCellInA1_NotationFromColumnAndRowIndices(
		int32 InColumnNumber, int32 InRowNumber);

	static int32 ColumnLetterToIndex(const FString& InColumnLetter);

	static FString ColumnIndexToLetter(const int32 Index);

	int32 GetRowCount() const
	{
		return ArrayValues.Num();
	}

	int32 GetColumnCount() const
	{
		if (GetRowCount() > 0)
		{
			return ArrayValues[0].Num();
		}

		return 0;
	}

	static FCsvToGoogleSheetsHandler CsvToSheetTabData(FString InCSVString);
	
	FString GetAllArrayValuesAsJsonString(const bool bAddValuesKey, const bool bWrapInCurlyBraces) const;
	
	FString SpecifiedRange = "A1";

	// ReSharper disable once CppConstValueFunctionReturnType
	static const TArray<FString> GetAlphabet()
	{
		return { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M",
			"N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z" };
	}

	TArray<TArray<FString>> ArrayValues;

	static constexpr int32 MaxColumnCount = 18278;
};
