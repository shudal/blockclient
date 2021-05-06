// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class BLOCK_API SaveGameUtil
{
public:
	SaveGameUtil();
	~SaveGameUtil();

	class USGConf* GetSGConf();
};
