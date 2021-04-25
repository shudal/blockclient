// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EventCardUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class BLOCK_API UEventCardUserWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	FString FormatMyTypeValue(const TArray<TSharedPtr<FJsonValue>>* arrp);
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UTextBlock* TB_EType = nullptr;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UTextBlock* TB_uuid = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UTextBlock* TB_etime = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UTextBlock* TB_recordtime = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UTextBlock* TB_tzoff = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UTextBlock* TB_bizstep = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UTextBlock* TB_readpoint = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UTextBlock* TB_bizloc = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UTextBlock* TB_disposition = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UTextBlock* TB_parentid = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UTextBlock* TB_transid = nullptr; 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UTextBlock* TB_action = nullptr;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UUniformGridPanel* UGP_parentid = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UUniformGridPanel* UGP_transid = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UUniformGridPanel* UGP_epclist = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UUniformGridPanel* UGP_quantitylist = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UUniformGridPanel* UGP_inputepcs = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UUniformGridPanel* UGP_outepcs = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UUniformGridPanel* UGP_inquanlist= nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UUniformGridPanel* UGP_outquanlist = nullptr;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UTextBlock* TB_biztrans = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UTextBlock* TB_sourlist = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UTextBlock* TB_destlist = nullptr;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UTextBlock* TB_epclist = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UTextBlock* TB_quantitylist = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UTextBlock* TB_inputepcs = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UTextBlock* TB_outepcs = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UTextBlock* TB_inquanlist = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UTextBlock* TB_outquanlist = nullptr;
public:

	UFUNCTION(BlueprintCallable)
		void SetListItemObject(class UEventCardItem* i);
};
