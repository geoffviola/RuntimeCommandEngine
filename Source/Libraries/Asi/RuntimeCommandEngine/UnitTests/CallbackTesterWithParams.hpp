#ifndef ASI_RUNTIMECOMMANDENGINE_UNITTESTS_CALLBACKTESTERWITHPARAMS_HPP
#define ASI_RUNTIMECOMMANDENGINE_UNITTESTS_CALLBACKTESTERWITHPARAMS_HPP

#include "gmock/gmock.h"
#include <functional>

template<class... T>
class CallbackTesterWithParams
{
public:
	CallbackTesterWithParams()
		: CallbackCalled(false)
	{
	}

	bool WasCallbackCalled() { return CallbackCalled; }
	std::function<void(T...)> GetCallback()
	{
		return std::bind(&CallbackTesterWithParams::Callback, this);
	}

private:
	void Callback() { CallbackCalled = true; }

	bool CallbackCalled;
};

#endif //ASI_RUNTIMECOMMANDENGINE_UNITTESTS_CALLBACKTESTERWITHPARAMS_HPP
