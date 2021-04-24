// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class BLOCK_API StrConst
{
public:
	StrConst();
	~StrConst();

	static StrConst& Get();

	// must same as conserver
	FString RECORD_TIME = "recordTime";
	FString EVENT_TIME = "eventTime";
	FString EVENT_TIME_ZONE_OFFSET = "eventTimeZoneOffset";
	FString EVENT_TYPE = "eventType";
	FString OBJECT_EVENT = "objectEvent";
	FString ACTION = "action";
	FString EPC_LIST = "epcList";
	FString QUANTITY_LIST = "quantityList";
	FString BIZ_STEP = "bizStep";
	FString DISPOSITION = "disposition";
	FString READ_POINT = "readPoint";
	FString BIZ_LOCATION = "bizLocation";
	FString BIZ_TRANSACTION_LIST = "bizTransactionList";
	FString SOURCE_LIST = "sourceList";
	FString DESTINATION_LIST = "destinationList";
	FString ANY = "any";
	FString EPC_CLASS = "epcClass";
	FString QUANTITY = "quantity";
	FString UOM = "uom";
	FString ILMDS = "ilmds";
	FString UUID = "uuid";
	FString EXTENSION = "extension";
	FString ERROR_DECLARATION = "errorDeclaration";
	FString PARENT_ID = "parentId";
	FString CHILD_EPCS = "childEPCs";
	FString CHILD_QUANTITY_LIST = "childQuantityList";
	FString TRANSFORMATION_ID = "transformationId";
	FString INPUT_LIST = "inputList";
	FString OUTPUT_LIST = "outputList";
	FString INPUT_QUANTITY_LIST = "inputQuantityList";
	FString OUTPUT_QUANTITY_LIST = "outputQuantityList";
	FString CONTRACT_METHOD_ADD = "addEvent";
	FString CONTRACT_METHOD_GET = "getEvent";
	FString CONTRACT_RES = "contract_res";
	FString CONTRACT_RES_BAD = "contract_res_bad";
	
	// typevalue, same as conserver
	FString TYPEVALUE_TYPE = "type";
	FString TYPEVALUE_VALUE = "value";

	FString uri_host = "http://95.179.176.135:8023/";
	FString uri_add_event = uri_host + "event/add";
	FString uri_add_voc = uri_host + "voc/add/voc";
	FString uri_query_voc = uri_host + "event/query/epc";

	FString VOC_DES = "voc_des";
};
