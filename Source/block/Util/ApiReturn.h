// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Interfaces/IHttpRequest.h"

#include "ApiReturn.generated.h"
/**
 * 
 */
UCLASS()
class BLOCK_API UApiReturn : public UObject
{

	GENERATED_BODY()

private:
	void SetCompleted(bool x);
	void SetSuccess(bool x);
protected:
	bool bStartOk=false;
	bool bCompleted=false;
	bool bSuccess=false;
public:
	TSharedPtr<FJsonObject> JRet;

	//UApiReturn(); 
	void ProcessRequestCompleted(FHttpRequestPtr request, FHttpResponsePtr response, bool bWasSuccessful);
	void SetStartOk(bool x); 
};
