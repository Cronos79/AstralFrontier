// © 2026 CronoSoft

#include "AFRUniverseGameMode.h"
#include "HAL/FileManager.h"
#include "Misc/Paths.h"

AAFRUniverseGameMode::AAFRUniverseGameMode()
{
}

void AAFRUniverseGameMode::BeginPlay()
{
	Super::BeginPlay();

	// DB should only exist/initialize on the server
	if (!HasAuthority())
	{
		return;
	}

	if (!OpenAndInitDatabase())
	{
		// Errors already logged inside OpenAndInitDatabase()
		return;
	}

#if WITH_EDITOR
	// Turn this on only when you're actively testing DB auth at server start.
	// Comment this out once your RPC flow is working.
	//DevAuthSelfTest();
#endif
}

bool AAFRUniverseGameMode::OpenAndInitDatabase()
{
	UE_LOG(LogTemp, Log, TEXT("Opening database..."));

	const FString DbDir = FPaths::ProjectSavedDir() / TEXT("Server");
	IFileManager::Get().MakeDirectory(*DbDir, true);

	const FString DbPath = DbDir / TEXT("astral_frontier.db");

	if (!Database.Open(DbPath))
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to open DB: %s"), *Database.GetLastError());
		return false;
	}

	if (!Database.EnsureSchema())
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to ensure schema: %s"), *Database.GetLastError());
		return false;
	}

	UE_LOG(LogTemp, Log, TEXT("Database ready: %s"), *DbPath);
	return true;
}

bool AAFRUniverseGameMode::AuthValidateAndRotate(
	const FString& InRefreshToken,
	int64& OutUserId,
	int64& OutSessionId,
	FString& OutNewRefreshToken,
	FString& OutError,
	int32 LifetimeDays)
{
	OutUserId = 0;
	OutSessionId = 0;
	OutNewRefreshToken.Empty();
	OutError.Empty();

	if (!HasAuthority())
	{
		OutError = TEXT("AuthValidateAndRotate called on client");
		return false;
	}

	const FString Token = InRefreshToken.TrimStartAndEnd();
	if (Token.IsEmpty())
	{
		OutError = TEXT("Missing refresh token");
		return false;
	}

	// 1) Validate token
	int64 UserId = 0;
	int64 SessionId = 0;

	if (!Database.ValidateRefreshToken(Token, UserId, SessionId))
	{
		OutError = Database.GetLastError().IsEmpty()
			? TEXT("Invalid or expired token")
			: Database.GetLastError();
		return false;
	}

	// 2) Rotate token (revoke old session + create new session)
	AFRSessionCreateResult Rot = Database.RotateSessionRefreshToken(Token, LifetimeDays);
	if (!Rot.bOk)
	{
		OutError = Rot.Error.IsEmpty()
			? TEXT("Token rotation failed")
			: Rot.Error;
		return false;
	}

	OutUserId = UserId;
	OutSessionId = Rot.SessionId;
	OutNewRefreshToken = Rot.RefreshToken;

	return true;
}

#if WITH_EDITOR
void AAFRUniverseGameMode::DevAuthSelfTest()
{
	UE_LOG(LogTemp, Log, TEXT("[DEV] Running auth self-test..."));

	// Ensure test user exists
	int64 UserId = 0;

	AFRUserRow Existing;
	if (Database.FindUserByUsername(TEXT("matt"), Existing))
	{
		UserId = Existing.Id;
		UE_LOG(LogTemp, Log, TEXT("[DEV] User exists: id=%lld username=%s"), Existing.Id, *Existing.Username);
	}
	else
	{
		int64 NewUserId = 0;
		if (Database.CreateUser(TEXT("matt"), TEXT(""), TEXT("TEST_HASH"), NewUserId))
		{
			UserId = NewUserId;
			UE_LOG(LogTemp, Log, TEXT("[DEV] Created user id=%lld"), NewUserId);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("[DEV] CreateUser failed: %s"), *Database.GetLastError());
			return;
		}
	}

	// Create session
	const AFRSessionCreateResult Session = Database.CreateSession(UserId, 30);
	if (!Session.bOk)
	{
		UE_LOG(LogTemp, Error, TEXT("[DEV] CreateSession failed: %s"), *Session.Error);
		return;
	}

	UE_LOG(LogTemp, Log, TEXT("[DEV] Created session id=%lld"), Session.SessionId);

	// Validate+Rotate through the wrapper (this is what the RPC will use)
	int64 AuthedUserId = 0;
	int64 AuthedSessionId = 0;
	FString NewToken;
	FString Error;

	if (AuthValidateAndRotate(Session.RefreshToken, AuthedUserId, AuthedSessionId, NewToken, Error, 30))
	{
		UE_LOG(LogTemp, Log, TEXT("[DEV] AuthValidateAndRotate OK -> user=%lld session=%lld"), AuthedUserId, AuthedSessionId);
		UE_LOG(LogTemp, Log, TEXT("[DEV] New refresh token: %s"), *NewToken);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("[DEV] AuthValidateAndRotate FAILED: %s"), *Error);
	}
}
#endif
