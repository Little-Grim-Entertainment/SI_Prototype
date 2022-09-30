// Created by dorgon, All Rights Reserved.
// Date of intended publication: 2019/08/01
// email: dorgonman@hotmail.com
// blog: dorgon.horizon-studio.net

#pragma once



#include "HorizonFileSystem.generated.h"


class UPaperFlipbook;
UCLASS(BlueprintType, Blueprintable, config = HorizonPlugin, meta = (ShortTooltip = "HorizonFileSystem"))
class HORIZONUI_API UHorizonFileSystem : public UObject 
{
private:
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "HorizonPlugin|UI|FileSystem", meta = (Keywords = "GetInstance"))
	static UHorizonFileSystem* GetInstance();

	UFUNCTION(BlueprintCallable, Category = "HorizonPlugin|UI|FileSystem", meta = (Keywords = "DestroyInstance"))
	static void DestroyInstance();

	UFUNCTION(BlueprintCallable, Category = "HorizonPlugin|UI|FileSystem", meta = (Keywords = "Create Folder recursively"))
	void CreateDirectoryRecursively(FString InFolderToMake);


	UFUNCTION(BlueprintCallable, Category = "HorizonPlugin|UI|FileSystem", meta = (Keywords = "LoadTexture2D"))
	UTexture2D* LoadTexture2D(const FString& InPackageFilePath, int32& OutWidth, int32& OutHeight);

	UFUNCTION(BlueprintCallable, Category = "HorizonPlugin|UI|FileSystem", meta = (Keywords = "LoadFlipBook"))
	UPaperFlipbook* LoadPaperFlipbook(const FString& InPackageFilePath);


	UFUNCTION(BlueprintCallable, Category = "HorizonPlugin|UI|FileSystem", meta = (Keywords = "LoadMaterial"))
	UMaterial* LoadMaterial(const FString& InPackageFilePath);


	UFUNCTION(BlueprintCallable, Category = "HorizonPlugin|UI|FileSystem", meta = (Keywords = "LoadFont"))
	USoundBase* LoadSound(const FString& InPackageFilePath);



	UFUNCTION(BlueprintCallable, Category = "HorizonPlugin|UI|FileSystem", meta = (Keywords = "LoadSound"))
	UFont* LoadFont(const FString& InPackageFilePath);

	UFUNCTION(BlueprintCallable, Category = "HorizonPlugin|UI|FileSystem", meta = (Keywords = "LoadUAsset"))
	UObject* LoadUAsset(const FString& InPackageFilePath);

	UTexture2D* LoadTexture2DImplement(const FString& InFullFilePath, bool& OutIsValid, int32& OutWidth, int32& OutHeight);
private:
	TArray<FString> SearchPathList;

	static UHorizonFileSystem* Instance;
};