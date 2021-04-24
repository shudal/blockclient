// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "VocItemUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class BLOCK_API UVocItemUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected: 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UTextBlock* TB_name = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UTextBlock* TB_value = nullptr;
public:
	UFUNCTION(BlueprintCallable)
		void SetListItemObject(class UVocItem* vi);
};
