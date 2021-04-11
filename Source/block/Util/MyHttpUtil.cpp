// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHttpUtil.h"
#include "HttpModule.h"
MyHttpUtil::MyHttpUtil()
{
}

MyHttpUtil::~MyHttpUtil()
{
} 
TSharedPtr<UApiReturn> MyHttpUtil::PostParameter(FString url, TMap<FString, FString> Parameters) {
	//TSharedPtr<UApiReturn> ret = MakeShared<UApiReturn>();

	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	TSharedPtr<UApiReturn> ret = MakeShareable(NewObject<UApiReturn>());
	HttpRequest->OnProcessRequestComplete().BindUObject(ret.Get(), &UApiReturn::ProcessRequestCompleted);
	HttpRequest->SetVerb("POST");
	HttpRequest->SetHeader("Content-Type", "application/x-www-form-urlencoded");   
	HttpRequest->SetURL(url); 

	FString ContentString;

	TArray<FString>Keys;

	Parameters.GetKeys(Keys);


	for (size_t i = 0; i < Keys.Num(); i++)
	{
		if (i == 0)
		{
			ContentString += Keys[i] + "=" + *Parameters.Find(Keys[i]);
		}
		else
		{
			ContentString += "&" + Keys[i] + "=" + *Parameters.Find(Keys[i]);
		}


	}


	HttpRequest->SetContentAsString(ContentString);

	ret->SetStartOk(HttpRequest->ProcessRequest());



	return ret;
}
 

