#ifndef ASI_RUNTIMECOMMANDENGINE_MAKECOMMAND_HPP
#define ASI_RUNTIMECOMMANDENGINE_MAKECOMMAND_HPP

#include "CommandWithoutParams.hpp"
#include "CommandWithParams.hpp"

/**
        file use these functions to more easily make commands
*/

namespace asi
{
namespace runtimecommandengine
{

static inline CommandWithoutParams MakeCommand(std::vector<std::string> const &in_signature,
                                               std::string const &in_description,
                                               CommandWithGenericParams::CallFunType call_fun)
{
	return CommandWithoutParams(in_signature, in_description, call_fun);
}

template <class... ParamTypes>
static inline CommandWithParams<ParamTypes...>
MakeCommand(std::vector<std::string> const &in_signature, std::string const &in_description,
            typename CommandWithParams<ParamTypes...>::CallFunType const &callback,
            ParamTypes const &... typed_parameter)
{
	return CommandWithParams<ParamTypes...>(in_signature, in_description, callback, typed_parameter...);
}

} // namespace runtimecommandengine
} // namespace asi

#endif // ASI_RUNTIMECOMMANDENGINE_MAKECOMMAND_HPP
