// Fill out your copyright notice in the Description page of Project Settings.


#include "VocItemUserWidget.h"
#include "VocItem.h"
#include "Components/TextBlock.h"

void  UVocItemUserWidget::SetListItemObject(UVocItem* vi) {
	auto vocjo = vi->GetVoc();

	TB_name->SetText(FText::FromString(vocjo->GetStringField("name")));
	TB_value->SetText(FText::FromString(vocjo->GetStringField("value")));
}