// Fill out your copyright notice in the Description page of Project Settings.


#include "VocCardItem.h"


void UVocCardItem::SetVocs(TArray<TSharedPtr<FJsonObject>>& arr) { 
	Vocs = arr;
}

TArray<TSharedPtr<FJsonObject>> UVocCardItem::GetVocs() {
	return Vocs;
}