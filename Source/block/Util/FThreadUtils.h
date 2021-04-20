// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HAL/Runnable.h"
#include "HAL/RunnableThread.h"

namespace EThreadStatus
{
	enum Type
	{
		InActive,

		Busy,

		Canceling,

		Canceled,

		Completed
	};

}
class FThread : public FRunnable
{
public:
	using FCallback = TFunction<void()>;
	explicit FThread(const TCHAR* InThreadName, const FCallback& InRunFunc)
		:mThreadName(InThreadName), mRunFunc(InRunFunc), mThreadStatus(EThreadStatus::InActive)
	{}

	virtual void Execute()
	{
		if (GetThreadStatus() == EThreadStatus::InActive)
		{
			mThread = FRunnableThread::Create(this, *mThreadName);
			if (mThread)
			{
				mThreadStatus = EThreadStatus::Busy;
			}
		}
	}
	virtual void Join()
	{
		mThread->WaitForCompletion();
	}

	virtual uint32 Run()override
	{
		mRunFunc();

		return 0;
	}
	virtual void Stop()override
	{
		Cancel();
	}
	virtual void Cancel()
	{
		mThreadStatus = EThreadStatus::Canceled;
	}
	virtual void Exit()override
	{
		mThreadStatus = EThreadStatus::Completed;
	}

	virtual EThreadStatus::Type GetThreadStatus()const
	{
		return mThreadStatus;
	}
public: 
protected:
	FString mThreadName;
	FCallback mRunFunc;
	FRunnableThread* mThread;
	volatile EThreadStatus::Type mThreadStatus;

private:
	FThread(const FThread&) = delete;
	FThread& operator=(const FThread&) = delete;

};

/**
 * 
 */
class BLOCK_API FThreadUtils
{
public:
	FThreadUtils();
	~FThreadUtils();
};
