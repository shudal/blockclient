// Fill out your copyright notice in the Description page of Project Settings.


#include "VocCardUserWidget.h"
#include "VocCardItem.h"
#include "Components/TextBlock.h"
#include "Components/ListView.h"
#include "Http.h"
#include "Json.h"
#include "../Config/StrConst.h"
#include "VocItem.h"

void UVocCardUserWidget::SetListItemObject(UVocCardItem* ci) {
	SetVocs(ci->GetVocs()); 

	LV_vocitems->ClearListItems();
	for (auto& j : Vocs) {  
		if (j->GetStringField("name") == StrConst::Get().VOC_DES) {
			TB_CardTitle->SetText(FText::FromString(j->GetStringField("value")));
		}
		else { 
			auto it = NewObject<UVocItem>();
			it->SetVoc(j);
			LV_vocitems->AddItem(it);
		}
	}
	 
}

void UVocCardUserWidget::SetVocs(TArray<TSharedPtr<FJsonObject>> arr) { 
	Vocs = arr;
}