// Fill out your copyright notice in the Description page of Project Settings.


#include "StrConst.h"

StrConst::StrConst()
{
}

StrConst::~StrConst()
{
}

StrConst& StrConst::Get() {
	static StrConst sc;
	return sc;
}

void StrConst::UpdateText() { 
	uri_add_event = uri_host + "event/add";
	uri_add_voc = uri_host + "voc/add/voc";
	uri_query_voc = uri_host + "event/query/epc";
}