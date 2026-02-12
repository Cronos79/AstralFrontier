// © 2026 CronoSoft

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Framework/Database/AFRDatabase.h"
#include "AFRUniverseGameMode.generated.h"

UCLASS()
class ASTRALFRONTIER_API AAFRUniverseGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AAFRUniverseGameMode();

	virtual void BeginPlay() override;

	// Server-side auth entry point for PlayerControllers (RPC handlers call this)
	bool AuthValidateAndRotate(
		const FString& InRefreshToken,
		int64& OutUserId,
		int64& OutSessionId,
		FString& OutNewRefreshToken,
		FString& OutError,
		int32 LifetimeDays = 30);

	// Optional helper for login/register later:
	// AFRDatabase& GetDatabase() { return Database; }  // (only if you decide you want it)

private:
	bool OpenAndInitDatabase();

#if WITH_EDITOR
	void DevAuthSelfTest();
#endif

private:
	AFRDatabase Database;
};
