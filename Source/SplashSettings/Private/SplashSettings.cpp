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

    const FString& Start = GIsEditor ? TEXT("EdSplash") : TEXT("Splash");

	const TArray<FString>& SplashFiles = AllSplashFiles.FilterByPredicate([&](const FString& File) {
        return File.StartsWith(Start);
    });

    FGenericPlatformSplash::SetCustomSplashImage(*FPaths::ConvertRelativePathToFull(FPaths::ProjectContentDir() / TEXT("Splash") / SplashFiles[FMath::RandRange(0, SplashFiles.Num() - 1)]));
}

IMPLEMENT_MODULE(FSplashSettingsModule, SplashSettings)
