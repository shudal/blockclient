// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHttpUtil.h"
#include "HttpModule.h"
MyHttpUtil::MyHttpUtil()
{
}

MyHttpUtil::~MyHttpUtil()
{
} 
UApiReturn* MyHttpUtil::PostFormData(FString url, TMap<FString, FString> Parameters) { 
	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest(); 
	UApiReturn* ret = NewObject<UApiReturn>();
	HttpRequest->OnProcessRequestComplete().BindUObject(ret, &UApiReturn::ProcessRequestCompleted);
	
	FString Boundary = "---------------------------" + FString::FromInt(FDateTime::Now().GetTicks());
	HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("multipart/form-data;boundary =" + Boundary));
	HttpRequest->SetVerb("POST");  
	HttpRequest->SetURL(url); 

	FString ContentString;

	TArray<FString>Keys;

	Parameters.GetKeys(Keys);


	for (size_t i = 0; i < Keys.Num(); i++)
	{

		ContentString.Append("\r\n--" + Boundary + "\r\n");
		ContentString.Append("Content-Disposition: form-data; name=\"" + Keys[i] + "\"\r\n\r\n");
		ContentString.Append(*Parameters.Find(Keys[i]) + "\r\n");


	}


	FString EndBoundary = "\r\n--" + Boundary + "--\r\n";
	ContentString.Append(EndBoundary);

	HttpRequest->SetContentAsString(ContentString);

	ret->SetStartOk(HttpRequest->ProcessRequest());



	return ret;
}
 

UApiReturn* MyHttpUtil::Get(FString url, TMap<FString, FString> Parameters) {
	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	UApiReturn* ret = NewObject<UApiReturn>();
	HttpRequest->OnProcessRequestComplete().BindUObject(ret, &UApiReturn::ProcessRequestCompleted);

	HttpRequest->SetVerb("GET"); 

	FString AllURL = url + "?"; 
	TArray<FString>Keys; 
	Parameters.GetKeys(Keys); 
	for (size_t i = 0; i < Keys.Num(); i++)
	{
		if (i == 0) AllURL += Keys[i] + "=" + *Parameters.Find(Keys[i]);
		else AllURL += "&" + Keys[i] + "=" + *Parameters.Find(Keys[i]);
	}
	HttpRequest->SetURL(AllURL);

	ret->SetStartOk(HttpRequest->ProcessRequest());
	return ret;
}