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
UENUM(BlueprintType)
enum class EUIType : uint8 {
	// must same as IntConst
	EventAdd = 0,
	VocAdd = 1,
	VocQuery = 2,
	Settings = 3,
	VocShow =4
};


USTRUCT(BlueprintType)
struct FConfirmMsg
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString msg;

	FConfirmMsg() = default;
	FConfirmMsg(FString x) {
		msg = x;
	}
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

	TArray<TSharedPtr<FJsonValue>> vocattrs;
	TArray<TSharedPtr<FJsonValue>> vocchilds;

	bool bIsViewingNotifyConfirm = false; 
	bool bEverLoadConfFromFile = false;
	bool bEverPlayerVideo = false;
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


	// epc list
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UOverlay* OL_EpcList = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UTextBlock* TB_epctip = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UEditableTextBox* ET_epc = nullptr;

	// epc quantity list

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UOverlay* OL_QuantityList = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UTextBlock* TB_quantip = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UEditableTextBox* ET_quanuuid = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UEditableTextBox* ET_quantity = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UEditableTextBox* ET_uom = nullptr;

	// voc
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UEditableTextBox* ET_vocuuid = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UEditableTextBox* ET_voctype = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UEditableTextBox* ET_vocuri = nullptr; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UOverlay* OL_vocattr = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UEditableTextBox* ET_vocattrname = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UEditableTextBox* ET_vocattrvalue = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UTextBlock* TB_inputvocattrtip = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UEditableTextBox* ET_childvocuuid = nullptr;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UOverlay* OL_vocchild = nullptr;   
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UTextBlock* TB_vocchildtip = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UEditableTextBox* ET_queryvocuri = nullptr;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UOverlay* OL_oknotify = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UTextBlock* TB_oknotify = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UListView* LV_VocCard = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UListView* LV_EventCard = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UEditableTextBox* ET_uri_host = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UMediaPlayer* mplayer = nullptr;
public: 

		TQueue<FConfirmMsg> ConfirmMsgs;
private:
	void SetAllUGPState(ESlateVisibility v);
	void SetIsViewingNotifyConfirm(bool x);
	bool IsViewingNotifyConfirm();

	TArray<TSharedPtr<FJsonObject>> EventItems;
	FORCEINLINE void SetEventItems(TArray<TSharedPtr<FJsonObject>> arr) { this->EventItems = arr; }
	TMap < FString, TArray<TSharedPtr<FJsonObject>>> VocCardItems;
	FORCEINLINE void SetVocCardItems(TMap < FString, TArray<TSharedPtr<FJsonObject>>> arr) { VocCardItems = arr; }
	FORCEINLINE TMap < FString, TArray<TSharedPtr<FJsonObject>>>& GetVocCardItems() { return VocCardItems; }
	bool bWhetherSetVocCard = false;
	FORCEINLINE bool IsSetVocCard() { return bWhetherSetVocCard; }
	FORCEINLINE void SetWhetherSetVocCard(bool x) { bWhetherSetVocCard = x; }
	
	void SetDefaultEventAddField();
protected:

	UFUNCTION(BlueprintCallable)
		void SwitchWidgetTo(EUIType t);
	 
	UFUNCTION(BlueprintCallable)
		void SetFormLayoutFromEventType(FString ets);


	UFUNCTION(BlueprintCallable)
		void SubmitEvent();


	UFUNCTION(BlueprintCallable)
		void InputTypeValue(ETypeValueType tvt);

	UFUNCTION(BlueprintCallable)
		void InputEpc(EEpcType et);
	UFUNCTION(BlueprintCallable)
		void InputQuantity(EQuantityType qt);
	UFUNCTION(BlueprintCallable)
		void InputVocattr();
	UFUNCTION(BlueprintCallable)
		void InputVocchild();

	UFUNCTION(BlueprintCallable)
		void SubmitTypeValue();
	UFUNCTION(BlueprintCallable)
		void SubmitEpc();
	UFUNCTION(BlueprintCallable)
		void SubmitQuantity();
	UFUNCTION(BlueprintCallable)
		void SubmitVoc();
	UFUNCTION(BlueprintCallable)
		void SubmitVocAttr();
	UFUNCTION(BlueprintCallable)
		void SubmitVocchild();

	UFUNCTION(BlueprintCallable)
		void CollapseTypeValueInput();
	UFUNCTION(BlueprintCallable)
		void CollapseEpcInput();
	UFUNCTION(BlueprintCallable)
		void CollapseQuantityInput();
	UFUNCTION(BlueprintCallable)
		void CollapseVocattr();
	UFUNCTION(BlueprintCallable)
		void CollapseVocchild();
	UFUNCTION(BlueprintCallable)
		void CollapseOknotify();


	UFUNCTION(BlueprintCallable)
		void SubmitQueryVoc();


	UFUNCTION(BlueprintCallable)
		FString GetHostUri();
	UFUNCTION(BlueprintCallable)
		void NotifyConfirm(FString tip);

	UFUNCTION(BlueprintCallable)
		void SetUriHostFromET();

	
public:

	virtual bool Initialize() override;
	FTimerHandle TimerHandle_DefaultTimer;
	void DefaultTimer();


	UFUNCTION(BlueprintCallable)
	void MediaPlayerOnOpened(FString url);
	UFUNCTION(BlueprintCallable)
	void MediaPlayerOnOpenFailed(FString url);

	UFUNCTION(BlueprintImplementableEvent)
		FString GetMyVideoCaptureDeviceUrl();
};
