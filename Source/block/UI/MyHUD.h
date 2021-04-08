// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MyHUD.generated.h"

/**
 * 
 */
UCLASS()
class BLOCK_API AMyHUD : public AHUD
{
	GENERATED_BODY()
	

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class UUserWidget> MainUWClass;

	//class UUserWidget* MyWidget;
	class UMainUserWidget* MainUW;
public:

	virtual void BeginPlay() override;
};
