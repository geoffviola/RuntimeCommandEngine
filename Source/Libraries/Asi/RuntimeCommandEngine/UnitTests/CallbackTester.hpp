#ifndef _ASI_RUNTIMECOMMANDENGINE_UNITTESTS_CALLBACKTESTER_HPP_
#define _ASI_RUNTIMECOMMANDENGINE_UNITTESTS_CALLBACKTESTER_HPP_

#include "gmock/gmock.h"
#include <functional>

class CallbackTester
{
public:
	CallbackTester()
		: CallbackCalled(false)
	{
	}

	bool WasCallbackCalled() { return CallbackCalled; }
	std::function<void(std::vector<std::string>)> GetCallback()
	{
		return std::bind(&CallbackTester::Callback, this);
	}

private:
	void Callback() { CallbackCalled = true; }

	bool CallbackCalled;
};

#endif // _ASI_RUNTIMECOMMANDENGINE_UNITTESTS_CALLBACKTESTER_HPP_
