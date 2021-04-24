// Fill out your copyright notice in the Description page of Project Settings.


#include "MainUserWidget.h"

#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/UniformGridPanel.h"	
#include "Components/EditableTextBox.h" 
#include "Components/Overlay.h"
#include "Components/TextBlock.h"
#include "Components/ListView.h"
#include "Json.h"
#include "../Config/StrConst.h"
#include "Components/ComboBoxString.h"
#include "../Util/MyHttpUtil.h"
#include "../Util/FThreadUtils.h" 
#include "VocCardItem.h"
#include "Http.h"
#include "EventCardItem.h"

bool UMainUserWidget::Initialize() {
	if (!Super::Initialize()) {
		return false;
	}  

	this->SetFormLayoutFromEventType(FString("Object"));
	this->OL_Typevalue->SetVisibility(ESlateVisibility::Collapsed);
	this->OL_EpcList->SetVisibility(ESlateVisibility::Collapsed);
	this->OL_QuantityList->SetVisibility(ESlateVisibility::Collapsed);
	this->CollapseVocattr();
	CollapseVocchild();
	CollapseOknotify();

	if (GetWorld() != nullptr) GetWorld()->GetTimerManager().SetTimer(TimerHandle_DefaultTimer, this, &UMainUserWidget::DefaultTimer, 1.0f, true);
	return true;
}

void UMainUserWidget::SwitchWidgetTo(EUIType t) {
	const int32 maxi = 4;
	int32 i = 0;
	switch (t) { 
	case EUIType::EventAdd:
		i = 0;
		break;
	case EUIType::VocAdd:
		i = 1;
		break;
	case EUIType::VocQuery:
		i = 2;
		break;
	case EUIType::Settings:
		i = 3;
		break;
	case EUIType::VocShow:
		i = 4;
		break;
	}

	verifyf(i >= 0 && i <= maxi, TEXT("i not right,i=%d"), i);
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
		if (epclist.Num() > 0) j->SetArrayField(StrConst::Get().EPC_LIST, epclist); 
		if (quantitylist.Num() > 0) j->SetArrayField(StrConst::Get().QUANTITY_LIST, quantitylist);
		break;
	case EEventType::Aggregation:
		j->SetStringField(StrConst::Get().ACTION, action);
		if (ET_parentid->GetText().ToString() != "") j->SetStringField(StrConst::Get().PARENT_ID, ET_parentid->GetText().ToString());
		if (epclist.Num() > 0) j->SetArrayField(StrConst::Get().CHILD_EPCS, epclist);
		if (quantitylist.Num() > 0) j->SetArrayField(StrConst::Get().CHILD_QUANTITY_LIST, quantitylist);
		break;
	case EEventType::Transformation: 
		if (ET_transid->GetText().ToString() != "") j->SetStringField(StrConst::Get().TRANSFORMATION_ID, ET_transid->GetText().ToString());

		if (inepclist.Num() > 0) j->SetArrayField(StrConst::Get().INPUT_LIST, inepclist);
		if (outepclist.Num() > 0) j->SetArrayField(StrConst::Get().OUTPUT_LIST, outepclist);
		if (inquantitylist.Num() > 0) j->SetArrayField(StrConst::Get().INPUT_QUANTITY_LIST, inquantitylist);
		if (outquantitylist.Num() > 0) j->SetArrayField(StrConst::Get().OUTPUT_QUANTITY_LIST, outquantitylist);
		break;
	case EEventType::Transaction:
		j->SetStringField(StrConst::Get().ACTION, action); 
		if (ET_parentid->GetText().ToString() != "") j->SetStringField(StrConst::Get().PARENT_ID, ET_parentid->GetText().ToString());
		if (epclist.Num() > 0) j->SetArrayField(StrConst::Get().EPC_LIST, epclist);
		if (quantitylist.Num() > 0) j->SetArrayField(StrConst::Get().QUANTITY_LIST, quantitylist);
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
		ConfirmMsgs.Enqueue(FConfirmMsg(TEXT("sending request")));  
		FThread* t = new FThread(TEXT("hi"), [=]()->void {
			while (!apiret->IsCompleted());	
			ConfirmMsgs.Enqueue(FConfirmMsg(TEXT("request completed")));

			if (apiret->GetRes() != nullptr) {
				FString content1, content2 = "";
				apiret->GetRes()->GetHeader(content1);
				content2 = apiret->GetRes()->GetContentAsString();
				content2.Append(content1);
				ConfirmMsgs.Enqueue(FConfirmMsg(FString::Printf(TEXT("%s"), *content2)));
			}

			if (apiret->IsSuccess()) {  
				if (apiret->JRet->HasField("code")) {
					int32 code = apiret->JRet->GetIntegerField("code");
					if (code == 0) {
						ConfirmMsgs.Enqueue(FConfirmMsg(TEXT("request succeess, code = 0")));
					}
					else {
						ConfirmMsgs.Enqueue(FConfirmMsg(TEXT("request succeess, but code != 0")));
					}
				}
				else {
					ConfirmMsgs.Enqueue(FConfirmMsg(TEXT("request success, but no code")));
				} 
			} else {
				ConfirmMsgs.Enqueue(FConfirmMsg(TEXT("request failed")));
			}
		});
		t->Execute();
	} else {
		ConfirmMsgs.Enqueue(FConfirmMsg(TEXT("sending request failed"))); 
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
	FString tip = FString::Printf(TEXT("%s(already count %d)"), *t1,now_add_typevalue->Num());
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

void UMainUserWidget::InputQuantity(EQuantityType  qt) {
	this->OL_QuantityList->SetVisibility(ESlateVisibility::Visible);

	FString t1 = "";
	switch (qt) { 
	case EQuantityType::Quantitylist:
		now_add_quantity = &quantitylist;
		t1 = "QuantityList";
		break;
	case EQuantityType::InQuantitylist:
		now_add_quantity = &inquantitylist;
		t1 = "InQuantityList";
		break;
	case EQuantityType::OutQuantitylist:
		now_add_quantity = &outquantitylist;
		t1 = "OutQuantityList";
		break;
	}

	FString tip = FString::Printf(TEXT("%s(already count %d)"), *t1, now_add_quantity->Num());
	this->TB_quantip->SetText(FText::FromString(tip));
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
void UMainUserWidget::SubmitQuantity() {
	this->CollapseQuantityInput();


	TSharedPtr<FJsonObject> j = MakeShared<FJsonObject>();
	j->SetStringField(StrConst::Get().EPC_CLASS, this->ET_quanuuid->GetText().ToString());
	if (this->ET_quantity->GetText().ToString() != "") j->SetStringField(StrConst::Get().QUANTITY, this->ET_quantity->GetText().ToString());
	if (this->ET_uom->GetText().ToString() != "") j->SetStringField(StrConst::Get().UOM, this->ET_uom->GetText().ToString());

	auto j1 = MakeShareable(new FJsonValueObject(j));
	now_add_quantity->Add(j1);
}
void UMainUserWidget::CollapseTypeValueInput() { 
	this->OL_Typevalue->SetVisibility(ESlateVisibility::Collapsed);
} 
void UMainUserWidget::CollapseEpcInput() {
	this->OL_EpcList->SetVisibility(ESlateVisibility::Collapsed);
}
void UMainUserWidget::CollapseQuantityInput() {
	this->OL_QuantityList->SetVisibility(ESlateVisibility::Collapsed);
} 
 
void UMainUserWidget::SubmitVoc() { 
	TSharedPtr<FJsonObject> j = MakeShared<FJsonObject>();
	 
	j->SetStringField("uuid", ET_vocuuid->GetText().ToString());
	if (ET_voctype->GetText().ToString() != "") j->SetStringField("vtype", ET_voctype->GetText().ToString());
	if (ET_vocuri->GetText().ToString() != "") j->SetStringField("uri", ET_vocuri->GetText().ToString());

	if (vocattrs.Num() > 0) j->SetArrayField("vocattr", vocattrs);
	if (vocchilds.Num() > 0) j->SetArrayField("vochild", vocchilds);

	FString OutputString;
	TSharedRef<TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<>::Create(&OutputString);
	FJsonSerializer::Serialize(j.ToSharedRef(), JsonWriter);

	TMap<FString, FString> params;
	params.Emplace("data", OutputString);
	UApiReturn* apiret = MyHttpUtil::PostFormData(StrConst::Get().uri_add_voc, params);
	if (apiret->IsStartOk()) { 
		ConfirmMsgs.Enqueue(FConfirmMsg(TEXT("sending request"))); 
		FThread* t = new FThread(TEXT("hi"), [=]()->void {
			while (!apiret->IsCompleted()); 
			ConfirmMsgs.Enqueue(FConfirmMsg(TEXT("request completed")));
			if (apiret->GetRes() != nullptr) {
				FString content1, content2 = "";
				apiret->GetRes()->GetHeader(content1);
				content2 = apiret->GetRes()->GetContentAsString();
				content2.Append(content1);
				ConfirmMsgs.Enqueue(FConfirmMsg(FString::Printf(TEXT("%s"), *content2)));
			}
			if (apiret->IsSuccess()) {
				if (apiret->JRet->HasField("code")) {
					int32 code = apiret->JRet->GetIntegerField("code");
					if (code == 0) {
						ConfirmMsgs.Enqueue(FConfirmMsg(TEXT("request succeess, code = 0")));
					}
					else {
						ConfirmMsgs.Enqueue(FConfirmMsg(TEXT("request succeess, but code != 0")));
					}
				}
				else {
					ConfirmMsgs.Enqueue(FConfirmMsg(TEXT("request success, but no code")));
				}
			}
			else {
				ConfirmMsgs.Enqueue(FConfirmMsg(TEXT("request failed")));
			}
		});
		t->Execute();  
	}
	else {
		ConfirmMsgs.Enqueue(FConfirmMsg(TEXT("sending request failed"))); 
	}
}


void UMainUserWidget::InputVocattr() { 
	this->OL_vocattr->SetVisibility(ESlateVisibility::Visible);

	FString tip = FString::Printf(TEXT("Enter vocattr(already count %d)"), vocattrs.Num());
	this->TB_inputvocattrtip->SetText(FText::FromString(tip));
}

void UMainUserWidget::InputVocchild() {

	OL_vocchild->SetVisibility(ESlateVisibility::Visible);

	FString tip = FString::Printf(TEXT("Enter vocchild(already count %d)"), vocchilds.Num());
	this->TB_vocchildtip->SetText(FText::FromString(tip));
}

void UMainUserWidget::SubmitVocAttr() {
	this->CollapseVocattr();

	TSharedPtr<FJsonObject> j = MakeShared<FJsonObject>();
	j->SetStringField("name", this->ET_vocattrname->GetText().ToString());
	j->SetStringField("value", this->ET_vocattrvalue->GetText().ToString());
	auto j1 = MakeShareable(new FJsonValueObject(j));
	this->vocattrs.Add(j1);
}

void UMainUserWidget::CollapseVocattr() {
	this->OL_vocattr->SetVisibility(ESlateVisibility::Collapsed);
}
 
void UMainUserWidget::CollapseOknotify() {
	this->OL_oknotify->SetVisibility(ESlateVisibility::Collapsed);
	SetIsViewingNotifyConfirm(false);
}
void UMainUserWidget::SubmitVocchild() {
	CollapseVocchild();

	auto j1 = MakeShareable(new FJsonValueString(ET_childvocuuid->GetText().ToString()));
	vocchilds.Add(j1);
}

void UMainUserWidget::CollapseVocchild() {
	OL_vocchild->SetVisibility(ESlateVisibility::Collapsed);
}

void UMainUserWidget::SubmitQueryVoc() {
	TMap<FString, FString> params;

	params.Emplace("uri", ET_queryvocuri->GetText().ToString());
	auto apiret = MyHttpUtil::Get(StrConst::Get().uri_query_voc, params); 
	if (apiret->IsStartOk()) {
		ConfirmMsgs.Enqueue(FConfirmMsg(TEXT("sending request")));
		FThread* t = new FThread(TEXT("hi"), [=]()->void {
			while (!apiret->IsCompleted());
			ConfirmMsgs.Enqueue(FConfirmMsg(TEXT("request completed")));
			if (apiret->GetRes() != nullptr) {
				FString content1, content2 = "";
				apiret->GetRes()->GetHeader(content1);
				content2 = apiret->GetRes()->GetContentAsString();
				content2.Append(content1);
				ConfirmMsgs.Enqueue(FConfirmMsg(FString::Printf(TEXT("%s"), *content2)));
			}
			if (apiret->IsSuccess()) {
				if (apiret->JRet->HasField("code")) {
					int32 code = apiret->JRet->GetIntegerField("code");
					if (code == 0) {
						ConfirmMsgs.Enqueue(FConfirmMsg(TEXT("request succeess, code = 0")));
						//ConfirmMsgs.Enqueue(FConfirmMsg(FString::Printf(TEXT("%s"),apiret->JRet->GetStringField(""))));
						auto ret = apiret->JRet;
						auto dataJO = ret->GetObjectField("data");
						auto vocall = dataJO->GetArrayField("vocall");
						auto events = dataJO->GetArrayField("events");

						TArray<TSharedPtr<FJsonObject>> ejs;
						for (auto& e : events) {
							auto ej = e->AsObject();
							ejs.Add(ej);
						}


						TMap < FString, TArray<TSharedPtr<FJsonObject>>> vocs;
						for (auto& vocv : vocall) {
							auto voc = vocv->AsObject();
							auto unikey = voc->GetStringField("uri");
							
							if (!vocs.Contains(unikey)) vocs.Add(unikey);
							vocs[unikey].Emplace(voc);
						}


						SetEventItems(ejs);
						SetVocCardItems(vocs);
						SetWhetherSetVocCard(true);
						 
					}
					else {
						ConfirmMsgs.Enqueue(FConfirmMsg(TEXT("request succeess, but code != 0")));
					}
				}
				else {
					ConfirmMsgs.Enqueue(FConfirmMsg(TEXT("request success, but no code")));
				}
			}
			else {
				ConfirmMsgs.Enqueue(FConfirmMsg(TEXT("request failed")));
			}
		});
		t->Execute();
	}
	else {
		ConfirmMsgs.Enqueue(FConfirmMsg(TEXT("sending request failed")));
	}
}

FString UMainUserWidget::GetHostUri() {
	return StrConst::Get().uri_host;
}

void UMainUserWidget::NotifyConfirm(FString tip) {
	SetIsViewingNotifyConfirm(true);
	this->OL_oknotify->SetVisibility(ESlateVisibility::Visible);
	TB_oknotify->SetText(FText::FromString(tip));
	
}

void UMainUserWidget::DefaultTimer() {
	if (ConfirmMsgs.IsEmpty() == false && IsViewingNotifyConfirm() == false) {
		FConfirmMsg msg;
		bool x = ConfirmMsgs.Dequeue(msg);
		if (x) {
			NotifyConfirm(msg.msg);
		}
	}


	if (IsSetVocCard()) { 
		LV_VocCard->ClearListItems();

		auto vocs = GetVocCardItems();
		TArray<FString>Keys;
		vocs.GetKeys(Keys);
		for (auto& k : Keys) {
			auto& arr = vocs[k];
			for (auto& j : arr) {
				FString OutputString;
				TSharedRef<TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<>::Create(&OutputString);
				FJsonSerializer::Serialize(j.ToSharedRef(), JsonWriter);
				UE_LOG(LogTemp, Warning, TEXT("%s"), *OutputString);
			}

			auto ci = NewObject<UVocCardItem>();
			ci->SetVocs(vocs[k]);
			LV_VocCard->AddItem(ci);
		}
		 
	
		SetWhetherSetVocCard(false);

		LV_EventCard->ClearListItems();
		for (auto& e : EventItems) {
			auto eo = NewObject<UEventCardItem>();
			eo->SetEventCardItem(e);
			LV_EventCard->AddItem(eo);
		}

		this->SwitchWidgetTo(EUIType::VocShow);
	}
}

void UMainUserWidget::SetIsViewingNotifyConfirm(bool x) {
	bIsViewingNotifyConfirm = x;
}

bool UMainUserWidget::IsViewingNotifyConfirm() {
	return bIsViewingNotifyConfirm;
}