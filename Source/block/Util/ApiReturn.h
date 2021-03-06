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
	FHttpResponsePtr res = nullptr;
	void SetCompleted(bool x);
	void SetSuccess(bool x);
protected:
	bool bStartOk=false;
	bool bCompleted=false;
	bool bSuccess=false;
public:
	~UApiReturn();

	TSharedPtr<FJsonObject> JRet = nullptr;

	//UApiReturn(); 
	void ProcessRequestCompleted(FHttpRequestPtr request, FHttpResponsePtr response, bool bWasSuccessful);
	void SetStartOk(bool x);

	bool IsStartOk();
	bool IsCompleted();
	bool IsSuccess();
	FHttpResponsePtr GetRes() { return res; }
};
