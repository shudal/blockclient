// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveGameUtil.h"
#include "../Config/SGConf.h"
#include "Kismet/GameplayStatics.h"
#include "../Config/StrConst.h"
#include "../Config/IntConst.h"

SaveGameUtil::SaveGameUtil()
{
}

SaveGameUtil::~SaveGameUtil()
{
}

USGConf* SaveGameUtil::GetSGConf() { 
	auto x = UGameplayStatics::DoesSaveGameExist(StrConst::Get().SLOT_NAME_CONF,IntConst::Get().SGCONF_USER_IDX);
	if (x) {
		USGConf* sg = Cast<USGConf>(UGameplayStatics::LoadGameFromSlot(StrConst::Get().SLOT_NAME_CONF, IntConst::Get().SGCONF_USER_IDX));
		if (sg) {
			return sg;
		}
	}


	USGConf* sg = Cast<USGConf>(UGameplayStatics::CreateSaveGameObject(USGConf::StaticClass()));
	verifyf(sg != nullptr, TEXT("save game util, create save game object but get null object"));
	return sg;
}

void SaveGameUtil::HotLoadConf() {
	auto sg = GetSGConf(); 
	StrConst::Get().uri_host = sg->GetUriHost();
	StrConst::Get().UpdateText();
}