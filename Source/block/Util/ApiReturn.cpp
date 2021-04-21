// Fill out your copyright notice in the Description page of Project Settings.


#include "ApiReturn.h"
#include "Http.h"
#include "Json.h" 

/*
UApiReturn::UApiReturn()
{
	bStartOk = false;
	bCompleted = false;
	bSuccess = false;
} 
*/
void UApiReturn::SetStartOk(bool x) {
	bStartOk = x;
}
void UApiReturn::SetCompleted(bool x) {
	bCompleted = x;
}

void UApiReturn::SetSuccess(bool x) {
	bSuccess = x;
}
void UApiReturn::ProcessRequestCompleted(FHttpRequestPtr request, FHttpResponsePtr response, bool bWasSuccessful) {

	//static int x = 0;
	//x++;
	//UE_LOG(LogTemp, Warning, TEXT("%d"), x);
	TArray<uint8> byteArray;
	
	if (response)
	{
		this->res = response;

		FString content1, content2 = "";
		int code;

		response->GetHeader(content1);
		content2 = response->GetContentAsString();
		code = response->GetResponseCode();

		content2.Append(content1);
		byteArray = response->GetContent(); 

		UE_LOG(LogTemp, Warning, TEXT("%s"), *content2);

		if (bWasSuccessful) { 
			JRet = MakeShared<FJsonObject>();
			TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(response->GetContentAsString());
			bool ok = FJsonSerializer::Deserialize(JsonReader, JRet);

			if (ok) SetSuccess(true);
		}
	};
 
	SetCompleted(true);
}

bool UApiReturn::IsStartOk() { return bStartOk; }
bool UApiReturn::IsCompleted() { return bCompleted; }
bool UApiReturn::IsSuccess() { return bSuccess; }