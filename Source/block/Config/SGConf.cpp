// Fill out your copyright notice in the Description page of Project Settings.


#include "SGConf.h"
#include "StrConst.h"
#include "IntConst.h"

USGConf::USGConf() {
	uri_host = "http://95.179.176.135:8023/";

	slot_name = StrConst::Get().SLOT_NAME_CONF;
	user_idx = IntConst::Get().SGCONF_USER_IDX;
}
void USGConf::SetUriHost(FString s) {
	uri_host = s;
}
FString USGConf::GetSlotName() {
	return slot_name;
}
uint32 USGConf::GetUserIndex() {
	return user_idx;
}