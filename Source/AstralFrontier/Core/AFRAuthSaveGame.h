// © 2026 CronoSoft
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "AFRAuthSaveGame.generated.h"

UCLASS()
class ASTRALFRONTIER_API UAFRAuthSaveGame : public USaveGame
{
    GENERATED_BODY()

public:
    UPROPERTY()
    FString RefreshToken; // raw token (client-held)

    UPROPERTY()
    FString LastServerAddr; // optional: "127.0.0.1"
};