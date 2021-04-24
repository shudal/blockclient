// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "VocItem.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class BLOCK_API UVocItem : public UObject
{
	GENERATED_BODY()
	
private:
	TSharedPtr<FJsonObject> vocjo = nullptr;
public:
	FORCEINLINE void SetVoc(TSharedPtr<FJsonObject> vjo) { this->vocjo = vjo; } 
	FORCEINLINE TSharedPtr<FJsonObject> GetVoc() { return this->vocjo;  }
};
