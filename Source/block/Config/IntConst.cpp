// Fill out your copyright notice in the Description page of Project Settings.


#include "IntConst.h"

IntConst::IntConst()
{
}

IntConst::~IntConst()
{
}

IntConst& IntConst::Get() {
	static IntConst ic;
	return ic;
}