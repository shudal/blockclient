// Fill out your copyright notice in the Description page of Project Settings.


#include "EventCardUserWidget.h"
#include "EventCardItem.h"
#include "../Config/StrConst.h"
#include "Components/TextBlock.h"
#include "MainUserWidget.h"

void UEventCardUserWidget::SetListItemObject(UEventCardItem* i) {
	auto j = i->GetEventCardItem();

	FString OutputString;
	TSharedRef<TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<>::Create(&OutputString);
	FJsonSerializer::Serialize(j.ToSharedRef(), JsonWriter); 

	//TB_EType->SetText(FText::FromString(j->GetStringField(StrConst::Get().EVENT_TYPE)));
	//TB_EType->SetText(FText::FromString(OutputString));

	auto eventJO = j->GetObjectField("event");

	auto event_type_idx = eventJO->GetIntegerField(StrConst::Get().EVENT_TYPE);
	FString event_type_strs[5]{ "ShouldNotExist","Object","Aggregation","Transformation","Transaction"};
	TB_EType->SetText(FText::FromString(event_type_strs[event_type_idx]));
}