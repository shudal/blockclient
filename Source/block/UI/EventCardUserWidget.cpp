// Fill out your copyright notice in the Description page of Project Settings.


#include "EventCardUserWidget.h"
#include "EventCardItem.h"
#include "../Config/StrConst.h"
#include "Components/TextBlock.h"
#include "Components/UniformGridPanel.h"	
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

	TB_uuid->SetText(FText::FromString(eventJO->GetStringField(StrConst::Get().UUID)));
	TB_action->SetText(FText::FromString(eventJO->GetStringField(StrConst::Get().ACTION)));
	TB_etime->SetText(FText::FromString(eventJO->GetStringField(StrConst::Get().EVENT_TIME)));
	TB_recordtime->SetText(FText::FromString(eventJO->GetStringField(StrConst::Get().RECORD_TIME)));
	TB_tzoff->SetText(FText::FromString(eventJO->GetStringField(StrConst::Get().EVENT_TIME_ZONE_OFFSET)));

	FString default_value = "None";
	{
		FString s = default_value;
		bool x = eventJO->TryGetStringField(StrConst::Get().BIZ_STEP, s);
		if (s.IsEmpty()) s = default_value;
		TB_bizstep->SetText(FText::FromString(s));
	} 
	{
		FString s = default_value;
		bool x = eventJO->TryGetStringField(StrConst::Get().READ_POINT, s);
		if (s.IsEmpty()) s = default_value;
		TB_readpoint->SetText(FText::FromString(s));
	}
	{
		FString s = default_value;
		bool x = eventJO->TryGetStringField(StrConst::Get().BIZ_LOCATION, s);
		if (s.IsEmpty()) s = default_value;
		TB_bizloc->SetText(FText::FromString(s));
	}
	{
		FString s = default_value;
		bool x = eventJO->TryGetStringField(StrConst::Get().DISPOSITION, s);
		if (s.IsEmpty()) s = default_value;
		TB_disposition->SetText(FText::FromString(s));
	}
	{
		FString s = default_value;
		bool x = eventJO->TryGetStringField(StrConst::Get().PARENT_ID, s);
		if (s.IsEmpty()) s = default_value;
		TB_parentid->SetText(FText::FromString(s));
	}
	{
		FString s = default_value;
		bool x = eventJO->TryGetStringField(StrConst::Get().TRANSFORMATION_ID, s);
		if (s.IsEmpty()) s = default_value;
		TB_transid->SetText(FText::FromString(s));
	}

	{
		TArray<TSharedPtr<FJsonValue>> arr; 
		const TArray<TSharedPtr<FJsonValue>>* arrp = &arr;
		bool x = eventJO->TryGetArrayField(StrConst::Get().BIZ_TRANSACTION_LIST, arrp);
		if (x) {
			auto s = FormatMyTypeValue(arrp);
			TB_biztrans->SetText(FText::FromString(s));
		}
	}
	{
		TArray<TSharedPtr<FJsonValue>> arr;
		const TArray<TSharedPtr<FJsonValue>>* arrp = &arr;
		bool x = eventJO->TryGetArrayField(StrConst::Get().SOURCE_LIST, arrp);
		if (x) {
			auto s = FormatMyTypeValue(arrp);
			TB_sourlist->SetText(FText::FromString(s));
		}
	}
	{
		TArray<TSharedPtr<FJsonValue>> arr;
		const TArray<TSharedPtr<FJsonValue>>* arrp = &arr;
		bool x = eventJO->TryGetArrayField(StrConst::Get().DESTINATION_LIST, arrp);
		if (x) {
			auto s = FormatMyTypeValue(arrp);
			TB_destlist->SetText(FText::FromString(s));
		}
	}
	EEventType et = static_cast<EEventType>(event_type_idx);
	switch (et) {
	case EEventType::Object:
		UGP_parentid->SetVisibility(ESlateVisibility::Collapsed); 
		UGP_transid->SetVisibility(ESlateVisibility::Collapsed);
		

		UGP_inputepcs->SetVisibility(ESlateVisibility::Collapsed);
		UGP_outepcs->SetVisibility(ESlateVisibility::Collapsed);
		UGP_inquanlist->SetVisibility(ESlateVisibility::Collapsed);
		UGP_outquanlist->SetVisibility(ESlateVisibility::Collapsed);
		break;
	case EEventType::Aggregation:
		UGP_transid->SetVisibility(ESlateVisibility::Collapsed);

		UGP_inputepcs->SetVisibility(ESlateVisibility::Collapsed);
		UGP_outepcs->SetVisibility(ESlateVisibility::Collapsed);
		UGP_inquanlist->SetVisibility(ESlateVisibility::Collapsed);
		UGP_outquanlist->SetVisibility(ESlateVisibility::Collapsed);
		break;
	case EEventType::Transformation:
		UGP_parentid->SetVisibility(ESlateVisibility::Collapsed);
		break;
	case EEventType::Transaction:
		UGP_parentid->SetVisibility(ESlateVisibility::Collapsed);

		UGP_inputepcs->SetVisibility(ESlateVisibility::Collapsed);
		UGP_outepcs->SetVisibility(ESlateVisibility::Collapsed);
		UGP_inquanlist->SetVisibility(ESlateVisibility::Collapsed);
		UGP_outquanlist->SetVisibility(ESlateVisibility::Collapsed);
		break;
	}
}

FString UEventCardUserWidget::FormatMyTypeValue(const TArray<TSharedPtr<FJsonValue>>* arrp) {
	FString s = "";
	for (auto& p : *arrp) {
		TSharedPtr<FJsonObject> j = p->AsObject();
		FString subs = "";
		auto t = j->GetStringField(StrConst::Get().TYPEVALUE_TYPE);
		auto v = j->GetStringField(StrConst::Get().TYPEVALUE_VALUE);
		subs = FString::Printf(TEXT("Type: %s; Value: %s"), *t, *v);
		s = s + subs + "    ";
	}
	return s;
}