// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SGConf.generated.h"

/**
 * 
 */
UCLASS()
class BLOCK_API USGConf : public USaveGame
{
	GENERATED_BODY()
	
private:
	FString slot_name = "";
	uint32 user_idx = 0;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString uri_host = "";
public:
	USGConf();
	void SetUriHost(FString s);
	FORCEINLINE FString GetUriHost() { return uri_host; }
	FString GetSlotName();
	uint32 GetUserIndex();

};
