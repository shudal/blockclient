// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "VocCardItem.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class BLOCK_API UVocCardItem : public UObject
{
	GENERATED_BODY()
	
private:
	TArray<TSharedPtr<FJsonObject>> Vocs;
public:
	void SetVocs(TArray<TSharedPtr<FJsonObject>>& arr);
	TArray<TSharedPtr<FJsonObject>> GetVocs();
};
