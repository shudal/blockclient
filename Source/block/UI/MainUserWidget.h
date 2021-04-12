// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainUserWidget.generated.h"


UENUM(BlueprintType)
enum class EEventType : uint8 {
	// must same as IntConst
	ShouldNotExist=0,
	Object=1,
	Aggregation=2,
	Transformation=3,
	Transaction=4
};
/**
 * 
 */
UCLASS()
class BLOCK_API UMainUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
private:
	EEventType now_et = EEventType::Object;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UWidgetSwitcher* MyWS = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UButton* BTN_EventAdd = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UButton* BTN_EventQuery = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UButton* BTN_VocAdd = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UButton* BTN_Settings = nullptr;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UUniformGridPanel* UGP_Action = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UUniformGridPanel* UGP_EpcList = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UUniformGridPanel* UGP_QuantityList = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UUniformGridPanel* UGP_ChildEpcs = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UUniformGridPanel* UGP_ChildQuantityList = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UUniformGridPanel* UGP_InputEpcs = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UUniformGridPanel* UGP_OutputEpcs = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UUniformGridPanel* UGP_InputQuantityList = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UUniformGridPanel* UGP_OutputQuantityList = nullptr; 


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UComboBoxString* CB_etype; 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UComboBoxString* CB_action;

	// common must
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UEditableTextBox* ET_uuid = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UEditableTextBox* ET_eventtime = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UEditableTextBox* ET_recordtime = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UEditableTextBox* ET_timezoneoff = nullptr;
	// common may
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UEditableTextBox* ET_bizstep = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UEditableTextBox* ET_readpoint = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UEditableTextBox* ET_bizloc = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UEditableTextBox* ET_disposition = nullptr;
	// special
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UEditableTextBox* ET_parentid = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UEditableTextBox* ET_transid = nullptr;
private:
	void SetAllUGPState(ESlateVisibility v);
protected:

	UFUNCTION(BlueprintCallable)
		void SwitchWidgetTo(int32 i);
	 
	UFUNCTION(BlueprintCallable)
		void SetFormLayoutFromEventType(FString ets);


	UFUNCTION(BlueprintCallable)
		void SubmitEvent();
public:

	virtual bool Initialize() override;
};
