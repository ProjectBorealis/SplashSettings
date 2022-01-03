#include "SplashSettings.h"
#include "CoreGlobals.h"
#include "GenericPlatform/GenericPlatformSplash.h"

void FSplashSettingsModule::StartupModule()
{
    const FString& SplashDirectory = FPaths::ConvertRelativePathToFull(FPaths::ProjectContentDir() + TEXT("Splash/"));
    TArray<FString> AllSplashFiles;
    IFileManager::Get().FindFiles(AllSplashFiles, *(SplashDirectory / TEXT("*.png")), true, false);
    IFileManager::Get().FindFiles(AllSplashFiles, *(SplashDirectory / TEXT("*.jpg")), true, false);
    IFileManager::Get().FindFiles(AllSplashFiles, *(SplashDirectory / TEXT("*.bmp")), true, false);

	const TArray<FString>& SplashFiles = AllSplashFiles.FilterByPredicate([&](const FString& File) {
#if WITH_EDITOR
        return File.StartsWith(TEXT("EdSplash"));
#else
		return File.StartsWith(TEXT("Splash"));
#endif
    });

	if (!SplashFiles.Num())
	{
		return;
	}

    FGenericPlatformSplash::SetCustomSplashImage(*FPaths::ConvertRelativePathToFull(FPaths::ProjectContentDir() / TEXT("Splash") / SplashFiles[FMath::RandRange(0, SplashFiles.Num() - 1)]));
}

IMPLEMENT_MODULE(FSplashSettingsModule, SplashSettings)
