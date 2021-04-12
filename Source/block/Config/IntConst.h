// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class BLOCK_API IntConst
{
public:
	IntConst();
	~IntConst();

	IntConst& Get();

	int32 EVENT_TYPE_DEFAULT = 0;
	int32 EVENT_TYPE_OBJECT = 1;
	int32 EVENT_TYPE_AGGREGATION = 2;
	int32 EVENT_TYPE_TRANSFORMATION = 3;
	int32 EVENT_TYPE_TRANSACTION = 4;
	int32 CALL_METHOD_EVALUATE = 1;
	int32 CALL_METHOD_SUBMIT = 2;
	int32 EVENT_ERROR_DEC_ID_DEFAULT = -1;
	int32 EVENT_BELONGED_ERR_DEC_ID_DEFAULT = -1;
};
