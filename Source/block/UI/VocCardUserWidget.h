// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h" 
#include "Blueprint/UserWidget.h"
#include "VocCardUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class BLOCK_API UVocCardUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
private: 
	TArray<TSharedPtr<FJsonObject>> Vocs;
	void SetVocs(TArray<TSharedPtr<FJsonObject>> arr);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UTextBlock* TB_CardTitle = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UListView* LV_vocitems = nullptr;
	
public:

	UFUNCTION(BlueprintCallable)
	void SetListItemObject(class UVocCardItem* ci);
};
