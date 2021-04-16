// Fill out your copyright notice in the Description page of Project Settings.


#include "MainUserWidget.h"

#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/UniformGridPanel.h"	
#include "Components/EditableTextBox.h" 
#include "Components/Overlay.h"
#include "Components/TextBlock.h"
#include "Json.h"
#include "../Config/StrConst.h"
#include "Components/ComboBoxString.h"
#include "../Util/MyHttpUtil.h"



bool UMainUserWidget::Initialize() {
	if (!Super::Initialize()) {
		return false;
	}  

	this->SetFormLayoutFromEventType(FString("Object"));
	this->OL_Typevalue->SetVisibility(ESlateVisibility::Collapsed);
	return true;
}

void UMainUserWidget::SwitchWidgetTo(int32 i) {
	verifyf(i >= 0 && i < 4, TEXT("i not right,i=%d"), i);
	if (MyWS != nullptr) {
		MyWS->SetActiveWidgetIndex(i);
	}
}

void UMainUserWidget::SetFormLayoutFromEventType(FString ets) {
	EEventType et;
	if (ets.Equals("Object")) et = EEventType::Object; 
	if (ets.Equals("Aggregation")) et = EEventType::Aggregation;
	if (ets.Equals("Transformation")) et = EEventType::Transformation;
	if (ets.Equals("Transaction")) et = EEventType::Transaction;

	this->SetAllUGPState(ESlateVisibility::Collapsed);
	this->ET_parentid->SetVisibility(ESlateVisibility::Collapsed);
	this->ET_transid->SetVisibility(ESlateVisibility::Collapsed);

	now_et = et;
	switch (et) {
	case EEventType::Object:
		UGP_Action->SetVisibility(ESlateVisibility::Visible);
		UGP_EpcList->SetVisibility(ESlateVisibility::Visible);
		UGP_QuantityList->SetVisibility(ESlateVisibility::Visible);
		break;
	case EEventType::Aggregation: 
		UGP_Action->SetVisibility(ESlateVisibility::Visible);
		UGP_ChildEpcs->SetVisibility(ESlateVisibility::Visible);
		UGP_ChildQuantityList->SetVisibility(ESlateVisibility::Visible);
		ET_parentid->SetVisibility(ESlateVisibility::Visible);
		break;
	case EEventType::Transformation:
		UGP_InputEpcs->SetVisibility(ESlateVisibility::Visible);
		UGP_InputQuantityList->SetVisibility(ESlateVisibility::Visible);
		UGP_OutputEpcs->SetVisibility(ESlateVisibility::Visible);
		UGP_OutputQuantityList->SetVisibility(ESlateVisibility::Visible);
		ET_transid->SetVisibility(ESlateVisibility::Visible);
		break;
	case EEventType::Transaction: 
		UGP_Action->SetVisibility(ESlateVisibility::Visible);
		UGP_EpcList->SetVisibility(ESlateVisibility::Visible);
		UGP_QuantityList->SetVisibility(ESlateVisibility::Visible);
		ET_parentid->SetVisibility(ESlateVisibility::Visible);
		break;
	}
}


void UMainUserWidget::SetAllUGPState(ESlateVisibility v) {
	UGP_Action->SetVisibility(v);
	UGP_EpcList->SetVisibility(v);
	UGP_QuantityList->SetVisibility(v);
	UGP_ChildEpcs->SetVisibility(v);
	UGP_ChildQuantityList->SetVisibility(v);
	UGP_InputEpcs->SetVisibility(v);
	UGP_OutputEpcs->SetVisibility(v);
	UGP_InputQuantityList->SetVisibility(v);
	UGP_OutputQuantityList->SetVisibility(v);
}

void UMainUserWidget::SubmitEvent() {
	TSharedPtr<FJsonObject> j = MakeShared<FJsonObject>();
	
	j->SetStringField(StrConst::Get().UUID, ET_uuid->GetText().ToString()); 
	j->SetStringField(StrConst::Get().RECORD_TIME, ET_recordtime->GetText().ToString());
	j->SetStringField(StrConst::Get().EVENT_TIME, ET_eventtime->GetText().ToString());
	j->SetStringField(StrConst::Get().EVENT_TIME_ZONE_OFFSET, ET_timezoneoff->GetText().ToString());

	if (ET_bizstep->GetText().ToString() != "") j->SetStringField(StrConst::Get().BIZ_STEP, ET_bizstep->GetText().ToString());
	if (ET_disposition->GetText().ToString() != "") j->SetStringField(StrConst::Get().DISPOSITION, ET_disposition->GetText().ToString());
	if (ET_readpoint->GetText().ToString() != "") j->SetStringField(StrConst::Get().READ_POINT, ET_readpoint->GetText().ToString());
	if (ET_bizloc->GetText().ToString() != "") j->SetStringField(StrConst::Get().BIZ_LOCATION, ET_bizloc->GetText().ToString());
 

	auto etype = CB_etype->GetSelectedOption(), action = CB_action->GetSelectedOption();
	j->SetNumberField(StrConst::Get().EVENT_TYPE, (double)((uint8)now_et));
	switch (now_et) {
	case EEventType::Object: 
		j->SetStringField(StrConst::Get().ACTION, action);
		break;
	case EEventType::Aggregation:
		j->SetStringField(StrConst::Get().ACTION, action);
		if (ET_parentid->GetText().ToString() != "") j->SetStringField(StrConst::Get().PARENT_ID, ET_parentid->GetText().ToString());
		break;
	case EEventType::Transformation: 
		if (ET_transid->GetText().ToString() != "") j->SetStringField(StrConst::Get().TRANSFORMATION_ID, ET_transid->GetText().ToString());
		break;
	case EEventType::Transaction:
		j->SetStringField(StrConst::Get().ACTION, action); 
		if (ET_parentid->GetText().ToString() != "") j->SetStringField(StrConst::Get().PARENT_ID, ET_parentid->GetText().ToString());
		break;
	}

	if (biztrans.Num() > 0) j->SetArrayField(StrConst::Get().BIZ_TRANSACTION_LIST, biztrans);
	if (sourlist.Num() > 0) j->SetArrayField(StrConst::Get().SOURCE_LIST, sourlist);
	if (destlist.Num() > 0) j->SetArrayField(StrConst::Get().DESTINATION_LIST, destlist);


	TSharedPtr<FJsonObject> inputJS = MakeShared<FJsonObject>();
	TArray<TSharedPtr<FJsonValue>> events;
	auto e1 = MakeShareable(new FJsonValueObject(j));
	events.Add(e1);
	inputJS->SetArrayField("data", events);

	FString OutputString;
	TSharedRef<TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<>::Create(&OutputString);
	FJsonSerializer::Serialize(inputJS.ToSharedRef(), JsonWriter);
	UE_LOG(LogTemp, Warning, TEXT("%s"), *OutputString);

	TMap<FString, FString> params;
	params.Emplace("input", OutputString);
	UApiReturn* apiret = MyHttpUtil::PostFormData(StrConst::Get().uri_add_event, params);
	if (apiret->IsStartOk()) {

		UE_LOG(LogTemp, Warning, TEXT("request ok"));
		//while (!apiret->IsCompleted());
		UE_LOG(LogTemp, Warning, TEXT("request completed"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("request faield"));
	} 
}

void UMainUserWidget::InputTypeValue(ETypeValueType tvt) { 
	this->OL_Typevalue->SetVisibility(ESlateVisibility::Visible);
	FString t1 = "";
	switch (tvt) {
	case ETypeValueType::BizTransaction: 
		t1 = "BizTransaction";
		now_add_typevalue = &biztrans;
		break;
	case ETypeValueType::SourceList: 
		t1 = "SourceList";
		now_add_typevalue = &sourlist;
		break;
	case ETypeValueType::DestList: 
		t1 = "DestList";
		now_add_typevalue = &destlist;
		break;
	}
	FString tip = FString::Printf(TEXT("������%s(����%d)"), *t1,now_add_typevalue->Num());
	this->TB_typevaluetip->SetText(FText::FromString(tip));
}

void UMainUserWidget::InputEpc(EEpcType et) { 
	this->OL_EpcList->SetVisibility(ESlateVisibility::Visible);

	FString t1 = "";
	switch (et) { 
	case EEpcType::Epclist:
		now_add_epc = &epclist;
		t1 = "Epclist";
		break;
	case EEpcType::InEpclist:
		now_add_epc = &inepclist;
		t1 = "InEpclist";
		break;
	case EEpcType::OutEpclist:
		now_add_epc = &outepclist;
		t1 = "OutEpclist";
		break;
	}

	FString tip = FString::Printf(TEXT("%s(already count %d)"), *t1, now_add_epc->Num());
	this->TB_epctip->SetText(FText::FromString(tip));
}
void UMainUserWidget::SubmitTypeValue() { 
	this->CollapseTypeValueInput();
	auto type = this->ET_typevalue_type->GetText().ToString();
	auto value = this->ET_typevlaue_value->GetText().ToString();


	TSharedPtr<FJsonObject> j = MakeShared<FJsonObject>(); 
	j->SetStringField(StrConst::Get().TYPEVALUE_TYPE, type);
	j->SetStringField(StrConst::Get().TYPEVALUE_VALUE, value); 
	auto j1 = MakeShareable(new FJsonValueObject(j));
	now_add_typevalue->Add(j1);
}

void UMainUserWidget::SubmitEpc() {
	this->CollapseEpcInput();

	auto epcclass = this->ET_epc->GetText().ToString();
	auto j1 = MakeShareable(new FJsonValueString(epcclass));
	now_add_epc->Add(j1);
}
void UMainUserWidget::CollapseTypeValueInput() { 
	this->OL_Typevalue->SetVisibility(ESlateVisibility::Collapsed);
} 
void UMainUserWidget::CollapseEpcInput() {
	this->OL_EpcList->SetVisibility(ESlateVisibility::Collapsed);
}