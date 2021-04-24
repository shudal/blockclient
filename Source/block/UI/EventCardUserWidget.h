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

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UTextBlock* TB_EType = nullptr;
	
public:

	UFUNCTION(BlueprintCallable)
		void SetListItemObject(class UEventCardItem* i);
};
