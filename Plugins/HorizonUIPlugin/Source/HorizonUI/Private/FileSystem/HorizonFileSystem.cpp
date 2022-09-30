// Created by dorgon, All Rights Reserved.
// Date of intended publication: 2019/08/01
// email: dorgonman@hotmail.com
// blog: dorgon.horizon-studio.net

#include "FileSystem/HorizonFileSystem.h"
#include "HorizonUIPrivate.h"


// singleton stuff
UHorizonFileSystem* UHorizonFileSystem::Instance = nullptr;

static EImageFormat GetImageFormat(const FString& InFileName)
{

	if (InFileName.EndsWith(".jpg") || InFileName.EndsWith(".JPG")) 
	{
		return EImageFormat::JPEG;
	}
	else if (InFileName.EndsWith(".png") || InFileName.EndsWith(".PNG"))
	{
		return EImageFormat::PNG;
	}
	else if (InFileName.EndsWith(".bmp") || InFileName.EndsWith(".BMP"))
	{
		return EImageFormat::BMP;
	}
	else if (InFileName.EndsWith(".ico") || InFileName.EndsWith(".ICO")) 
	{
		return EImageFormat::ICO;
	}
	else if (InFileName.EndsWith(".exr") || InFileName.EndsWith(".EXR"))
	{
		return EImageFormat::EXR;
	}
	else if (InFileName.EndsWith(".icns") || InFileName.EndsWith(".ICNS"))
	{
		return EImageFormat::ICNS;
	}
	return EImageFormat::PNG;
}

UHorizonFileSystem* UHorizonFileSystem::GetInstance() 
{
	if (!Instance)
	{
		Instance = NewObject<UHorizonFileSystem>();
		//s_instance = new UHorizonFileSystem();
		Instance->AddToRoot();
		//s_instance->SetFlags(EObjectFlags::RF_MarkAsRootSet);
	}

	return Instance;
}

void UHorizonFileSystem::DestroyInstance() 
{
	if (Instance) 
	{
		Instance->RemoveFromRoot();
		//Instance->ConditionalBeginDestroy();
		Instance = nullptr;
	}
}



void UHorizonFileSystem::CreateDirectoryRecursively(FString InFolderToMake)
{
	//Loop Proteciton
	const int32 MAX_LOOP_ITR = 3000;
	FPaths::NormalizeDirectoryName(InFolderToMake);

	//Normalize removes the last "/", but my algorithm wants it
	InFolderToMake += "/";

	FString base;
	FString left;
	FString remaining;

	//Split off the Root
	InFolderToMake.Split(TEXT("/"), &base, &remaining);
	base += "/"; //add root text to Base

	int32 loopCount = 0;
	while (remaining != "" && loopCount < MAX_LOOP_ITR)
	{
		remaining.Split(TEXT("/"), &left, &remaining);
		base += left + FString("/"); 
		FPlatformFileManager::Get().GetPlatformFile().CreateDirectory(*base);
		loopCount++;
	}
}


UObject* UHorizonFileSystem::LoadUAsset(const FString& packageFilePath)
{
	FSoftObjectPath assetRef = packageFilePath;
	UObject* pRet = assetRef.TryLoad();
	if (nullptr == pRet) {
		FString inPath;
		//filePath
		if (packageFilePath.StartsWith(TEXT("/"), ESearchCase::CaseSensitive))
		{
			// overwrite trailing slash with terminator
			inPath = packageFilePath.Mid(1, packageFilePath.Len());
		}
		else {
			inPath = packageFilePath;
		}
		// try search file from search path
		FString LongPackageName;
		if (SearchPathList.Num() > 0) {
			//use GameContentDir as default File path
			LongPackageName = "/Game/" + inPath;
			assetRef = LongPackageName;
			pRet = assetRef.TryLoad();
		}
		else {
			for (auto& it : SearchPathList) {
				FPaths::NormalizeDirectoryName(it);
				LongPackageName = it + "/" + inPath;
				assetRef = LongPackageName;
				pRet = assetRef.TryLoad();
				if (pRet) {
					break;
				}
			}
		}
	}

	return pRet;
}

UPaperFlipbook* UHorizonFileSystem::LoadPaperFlipbook(const FString& packageFilePath)
{

	UPaperFlipbook* pRet = Cast<UPaperFlipbook>(LoadUAsset(packageFilePath));
	return pRet;
}

UMaterial* UHorizonFileSystem::LoadMaterial(const FString& packageFilePath)
{
	UMaterial* pRet = Cast<UMaterial>(LoadUAsset(packageFilePath));
	return pRet;
}



UFont* UHorizonFileSystem::LoadFont(const FString& packageFilePath) 
{
	UFont* pRet = Cast<UFont>(LoadUAsset(packageFilePath));
	return pRet;
}

USoundBase* UHorizonFileSystem::LoadSound(const FString& packageFilePath)
{
	auto pRet = Cast<USoundBase>(LoadUAsset(packageFilePath));
	return pRet;
}


UTexture2D* UHorizonFileSystem::LoadTexture2D(const FString& packageFilePath, int32& OutWidth, int32& OutHeight) 
{

	//try load uassets
	UTexture2D* pResult = Cast<UTexture2D>(LoadUAsset(packageFilePath));
	//try loading Rawdata
	if (nullptr == pResult) 
	{
		FString realFilePath;
		FPackageName::TryConvertLongPackageNameToFilename(packageFilePath, realFilePath, TEXT(""));

		bool isValid = false;
		// Full path, so we can load texture directly
		if (FPaths::FileExists(realFilePath)) 
		{
			pResult = LoadTexture2DImplement(realFilePath, isValid, OutWidth, OutHeight);
		}
		else
		{
			// try search file from search path
			if (SearchPathList.Num() > 0) 
			{

				for (auto& it : SearchPathList) 
				{
					FPaths::NormalizeDirectoryName(it);
					FString longPackageName = it + "/" + packageFilePath;
					FPackageName::TryConvertLongPackageNameToFilename(longPackageName, realFilePath, TEXT(""));
					if (FPaths::FileExists(realFilePath)) 
					{
						//find file, break
						break;
					}
				}
			}

			pResult = LoadTexture2DImplement(realFilePath, isValid, OutWidth, OutHeight);
		}
	}
	return pResult;

}

UTexture2D* UHorizonFileSystem::LoadTexture2DImplement(const FString& InFullFilePath, bool& OutIsValid, int32& OutWidth, int32& OutHeight)
{
	OutIsValid = false;
	UTexture2D* pResult = nullptr;

	do 
	{
		IImageWrapperModule& imageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(FName("ImageWrapper"));
		TSharedPtr<IImageWrapper> imageWrapperPtr = imageWrapperModule.CreateImageWrapper(GetImageFormat(InFullFilePath));
		TArray<uint8> rawFileData;
		if (!FFileHelper::LoadFileToArray(rawFileData, *InFullFilePath)) break;
		if(!imageWrapperPtr.IsValid()) break;
		if(!imageWrapperPtr->SetCompressed(rawFileData.GetData(), rawFileData.Num())) break;

		TArray<uint8> uncompressedBGRA;
		if (!imageWrapperPtr->GetRaw(ERGBFormat::BGRA, 8, uncompressedBGRA)) break;


		pResult = UTexture2D::CreateTransient(imageWrapperPtr->GetWidth(), imageWrapperPtr->GetHeight(), PF_B8G8R8A8);
		if (!pResult) break;


		OutWidth = imageWrapperPtr->GetWidth();
		OutHeight = imageWrapperPtr->GetHeight();

#if UE_VERSION_OLDER_THAN(5,0,0)
		void* textureData = pResult->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
		FMemory::Memcpy(textureData, uncompressedBGRA.GetData(), uncompressedBGRA.Num());
		pResult->PlatformData->Mips[0].BulkData.Unlock();
#else
		void* textureData = pResult->GetPlatformData()->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
		FMemory::Memcpy(textureData, uncompressedBGRA.GetData(), uncompressedBGRA.Num());
		pResult->GetPlatformData()->Mips[0].BulkData.Unlock();
#endif
		pResult->UpdateResource();
		
		OutIsValid = true;

	} while (0);

	return pResult;

}


