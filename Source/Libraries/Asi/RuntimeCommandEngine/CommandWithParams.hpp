#ifndef ASI_RUNTIMECOMMANDENGINE_COMMANDWITHPARAMS_HPP
#define ASI_RUNTIMECOMMANDENGINE_COMMANDWITHPARAMS_HPP

#include "CommandWithGenericParams.hpp"
#include <iostream>
#include <array>

namespace asi
{
namespace runtimecommandengine
{

template <class... ParamTypes>
class CommandWithParams : public CommandInterface
{
public:
	typedef std::function<void(typename ParamTypes::ReturnType...)> CallFunType;

	CommandWithParams(std::vector<std::string> const &in_signature, std::string const &in_description,
	                  CallFunType const &callback, ParamTypes const &... typed_parameter)
	    : callbackFunction(callback)
	    , typedParameters(typed_parameter...)
	    , genericParameters(
	          TupleToPointerArray(&typedParameters, std::make_index_sequence<sizeof...(ParamTypes)>{}))
	    , cmdGenericParams(in_signature, in_description,
	                       std::bind(&CommandWithParams<ParamTypes...>::CallFunction, this, std::placeholders::_1),
	                       &genericParameters[0], sizeof...(ParamTypes))
	{
	}

private:
	template <std::size_t... Indices>
	static auto TupleToPointerArray(std::tuple<ParamTypes...> *const t, std::index_sequence<Indices...> indices)
	{
		return std::array<parameter::ParameterAbstract *, sizeof...(ParamTypes)>{
		    {static_cast<parameter::ParameterAbstract *>(&std::get<Indices>(*t))...}};
	}

	inline std::tuple<bool, uint32_t, std::string>
	EvaluateImpl(std::vector<std::string> const &tokens) const override
	{
		return cmdGenericParams.Evaluate(tokens);
	}
	inline std::vector<std::string> GetMethodNameImpl() const override { return cmdGenericParams.GetMethodName(); }
	inline std::string GetHelpImpl() const override { return cmdGenericParams.GetHelp(); }
	inline size_t GetSignatureLengthImpl() const override { return cmdGenericParams.GetSignatureLength(); }
	inline void PrependSignatureImpl(std::string const &pre_sig) override
	{
		cmdGenericParams.PrependSignature(pre_sig);
	}
	inline std::vector<std::string> GetSignatureExpectationImpl(size_t const index) const override
	{
		return cmdGenericParams.GetSignatureExpectation(index);
	}

	template <std::size_t... I>
	inline void CallFunctionHelper(std::vector<std::string> tokens, std::index_sequence<I...> args) const
	{
		callbackFunction(std::get<I>(typedParameters).GetValue(tokens[I])...);
	}

	inline void CallFunction(std::vector<std::string> const &tokens) const
	{
		std::vector<std::string> param_only_tokens(
		    tokens.begin() + static_cast<signed>(cmdGenericParams.GetMethodName().size()), tokens.end());
		auto const param_indices = std::make_index_sequence<sizeof...(ParamTypes)>{};
		CallFunctionHelper(param_only_tokens, param_indices);
	}

	CallFunType const callbackFunction;
	std::tuple<ParamTypes...> typedParameters;
	std::array<parameter::ParameterAbstract *, sizeof...(ParamTypes)> const genericParameters;
	CommandWithGenericParams cmdGenericParams;
};

} // namespace runtimecommandengine
} // namespace asi

#endif // ASI_RUNTIMECOMMANDENGINE_COMMANDWITHPARAMS_HPP
