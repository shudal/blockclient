// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EventCardItem.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class BLOCK_API UEventCardItem : public UObject
{
	GENERATED_BODY()
	
private:
	TSharedPtr<FJsonObject> EventCardJO = nullptr;
public:
	FORCEINLINE void SetEventCardItem(TSharedPtr<FJsonObject> ejo) { this->EventCardJO = ejo; }
	FORCEINLINE TSharedPtr<FJsonObject> GetEventCardItem() { return  EventCardJO; }
};
