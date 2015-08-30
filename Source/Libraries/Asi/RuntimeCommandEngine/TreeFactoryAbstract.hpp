#ifndef _ASI_RUNTIMECOMMANDENGINE_TREEFACTORYABSTRACT_HPP_
#define _ASI_RUNTIMECOMMANDENGINE_TREEFACTORYABSTRACT_HPP_

#include <vector>
#include "Command.hpp"
#include <cstdint>
#include "Tree.hpp"

namespace asi {
namespace runtimecommandengine {

/**
	Extend this class to build a custom tree.
	The InterpreterCallbackerClass is meant to be defined in the user's implementation.
*/
template<class InterpreterCallbackerClass>
class TreeFactoryAbstract
{
public:
	virtual ~TreeFactoryAbstract() {}
	
	template<class T1>
	static void CallbackAdapter(InterpreterCallbackerClass* interpreter_interface,
		std::function<void(InterpreterCallbackerClass*, T1)> callback_function,
		ParameterAbstract* pa)
	{
		callback_function(interpreter_interface, pa->GetValueAs<T1>());
	}
	
	template<class T1, class T2>
	static void CallbackAdapter(InterpreterCallbackerClass* interpreter_interface,
		std::function<void(InterpreterCallbackerClass*, T1, T2)> callback_function,
		ParameterAbstract* pa1, ParameterAbstract* pa2)
	{
		callback_function(interpreter_interface, pa1->GetValueAs<T1>(), pa2->GetValueAs<T2>());
	}
	
	template<class T1, class T2, class T3>
	static void CallbackAdapter(InterpreterCallbackerClass* interpreter_interface,
		std::function<void(InterpreterCallbackerClass*, T1, T2, T3)> callback_function,
		ParameterAbstract* pa1, ParameterAbstract* pa2, ParameterAbstract* pa3)
	{
		callback_function(interpreter_interface, pa1->GetValueAs<T1>(), pa2->GetValueAs<T2>(), pa3->GetValueAs<T3>());
	}
	
	template<class T1, class T2, class T3, class T4>
	static void CallbackAdapter(InterpreterCallbackerClass* interpreter_interface,
		std::function<void(InterpreterCallbackerClass*, T1, T2, T3, T4)> callback_function,
		ParameterAbstract* pa1, ParameterAbstract* pa2, ParameterAbstract* pa3,
		ParameterAbstract* pa4)
	{
		callback_function(interpreter_interface, pa1->GetValueAs<T1>(), pa2->GetValueAs<T2>(), pa3->GetValueAs<T3>(),
			pa4->GetValueAs<T4>());
	}
	
	Tree* GetTree(InterpreterCallbackerClass* interpreter)
	{
		static Tree tree = GetTreeImpl(interpreter);
		return &tree;
	}

protected:
	TreeFactoryAbstract() {}

	virtual Tree GetTreeImpl(InterpreterCallbackerClass *interpreter) = 0;
};

} // namespace runtimecommandengine
} // namespace asi

#endif //_ASI_RUNTIMECOMMANDENGINE_TREEFACTORYABSTRACT_HPP_
