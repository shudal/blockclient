// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHUD.h"
#include "MainUserWidget.h"
void AMyHUD::BeginPlay() {
	Super::BeginPlay();

	if (MainUWClass != nullptr) {
		auto MyWidget = CreateWidget<UUserWidget>(this->GetOwningPlayerController(), MainUWClass);
		if (MyWidget) {
			MainUW = Cast<UMainUserWidget>(MyWidget);
			if (MainUW) {
				MainUW->AddToViewport();
			}
		}
	}
}