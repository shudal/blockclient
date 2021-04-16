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
UENUM(BlueprintType)
enum class ETypeValueType : uint8 {
	// must same as IntConst
	ShouldNotExist = 0,
	BizTransaction = 1,
	SourceList = 2,
	DestList = 3
};
UENUM(BlueprintType)
enum class EEpcType : uint8 {
	// must same as IntConst
	ShouldNotExist = 0,
	Epclist = 1,  
	InEpclist = 2, 
	OutEpclist = 3, 
};
UENUM(BlueprintType)
enum class EQuantityType : uint8 {
	// must same as IntConst
	ShouldNotExist = 0, 
	Quantitylist = 1, 
	InQuantitylist = 2, 
	OutQuantitylist = 3,
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
	TArray<TSharedPtr<FJsonValue>> biztrans;
	TArray<TSharedPtr<FJsonValue>> sourlist;
	TArray<TSharedPtr<FJsonValue>> destlist;
	TArray<TSharedPtr<FJsonValue>>* now_add_typevalue = nullptr;


	TArray<TSharedPtr<FJsonValue>> epclist;
	TArray<TSharedPtr<FJsonValue>> quantitylist;

	TArray<TSharedPtr<FJsonValue>> inepclist;
	TArray<TSharedPtr<FJsonValue>> inquantitylist;
	TArray<TSharedPtr<FJsonValue>> outepclist;
	TArray<TSharedPtr<FJsonValue>> outquantitylist;
	TArray<TSharedPtr<FJsonValue>>* now_add_epc = nullptr;
	TArray<TSharedPtr<FJsonValue>>* now_add_quantity = nullptr;
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UOverlay* OL_Typevalue = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UTextBlock* TB_typevaluetip = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UEditableTextBox* ET_typevalue_type = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UEditableTextBox* ET_typevlaue_value = nullptr;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UOverlay* OL_EpcList = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UTextBlock* TB_epctip = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UEditableTextBox* ET_epc = nullptr;
	 
		
private:
	void SetAllUGPState(ESlateVisibility v);
protected:

	UFUNCTION(BlueprintCallable)
		void SwitchWidgetTo(int32 i);
	 
	UFUNCTION(BlueprintCallable)
		void SetFormLayoutFromEventType(FString ets);


	UFUNCTION(BlueprintCallable)
		void SubmitEvent();


	UFUNCTION(BlueprintCallable)
		void InputTypeValue(ETypeValueType tvt);

	UFUNCTION(BlueprintCallable)
		void InputEpc(EEpcType et);

	UFUNCTION(BlueprintCallable)
		void SubmitTypeValue();
	UFUNCTION(BlueprintCallable)
		void SubmitEpc();

	UFUNCTION(BlueprintCallable)
		void CollapseTypeValueInput();
	UFUNCTION(BlueprintCallable)
		void CollapseEpcInput();

public:

	virtual bool Initialize() override;
};
