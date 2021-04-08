// Fill out your copyright notice in the Description page of Project Settings.


#include "MainUserWidget.h"

#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/UniformGridPanel.h"	
#include "Components/EditableTextBox.h"
bool UMainUserWidget::Initialize() {
	if (!Super::Initialize()) {
		return false;
	}  

	this->SetFormLayoutFromEventType(FString("Object"));
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

}