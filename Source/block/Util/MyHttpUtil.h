// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ApiReturn.h"
/**
 * 
 */
class BLOCK_API MyHttpUtil
{
public:
	MyHttpUtil();
	~MyHttpUtil(); 
	
	UFUNCTION(BlueprintCallable)
		static UApiReturn* PostFormData(FString url, TMap<FString, FString> Parameters);

};
 