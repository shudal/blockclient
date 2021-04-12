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