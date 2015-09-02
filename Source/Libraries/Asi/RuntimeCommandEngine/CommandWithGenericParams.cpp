#include "CommandWithGenericParams.hpp"
#include "StringUtils.hpp"
#include <algorithm>

namespace asi
{
namespace runtimecommandengine
{

CommandWithGenericParams::CommandWithGenericParams(std::vector<std::string> const &signature,
                                                   std::string const &description, CallFunType call_fun,
                                                   parameter::ParameterAbstract const *const *const in_parameters,
                                                   int const num_params)
    : commandWithoutParams(signature, description, call_fun)
{
	genericParameters.reserve(
	    static_cast<std::vector<parameter::ParameterAbstract const *>::size_type>(num_params));
	for (int i = 0; i < num_params; ++i)
	{
		genericParameters.push_back(in_parameters[i]);
	}
}

std::tuple<bool, int32_t, std::string>
CommandWithGenericParams::EvaluateImpl(std::vector<std::string> const &tokens) const
{
	std::tuple<bool, int32_t, std::string> output(false, 0, "");

	// Check method names
	std::vector<std::string> candidate_method_name;
	if (tokens.size() <= commandWithoutParams.GetSignatureLength() || tokens.size() < genericParameters.size())
	{
		candidate_method_name = tokens;
	}
	else
	{
		candidate_method_name = std::vector<std::string>(
		    tokens.begin(), tokens.begin() + static_cast<signed>(commandWithoutParams.GetSignatureLength()));
	}
	auto const cwp_atis = commandWithoutParams.AreTokensInSignature(candidate_method_name);

	// Check parameter domains
	int32_t last_good_index_p1 = std::get<1>(cwp_atis);
	std::get<1>(output) = last_good_index_p1;
	if (true == std::get<0>(cwp_atis))
	{
		bool match = last_good_index_p1 != static_cast<int32_t>(tokens.size());
		uint32_t potential_good_index = static_cast<uint32_t>(last_good_index_p1) + 1U;
		for (; (potential_good_index < tokens.size()) &&
		       (potential_good_index - commandWithoutParams.GetSignatureLength() < genericParameters.size()) &&
		       genericParameters[potential_good_index - commandWithoutParams.GetSignatureLength()]
		           ->IsInExpectedDomain(tokens[potential_good_index]);
		     ++potential_good_index)
		{
		}
		match = potential_good_index == tokens.size();
		match =
		    match && (tokens.size() == commandWithoutParams.GetSignatureLength() + genericParameters.size());
		last_good_index_p1 = static_cast<int32_t>(potential_good_index) - 1;
		std::get<0>(output) = match;
		std::get<1>(output) = last_good_index_p1;
		if (match)
		{
			commandWithoutParams.CallFun(tokens);
			std::get<2>(output) = GetReceivedMessage(tokens);
		}
	}

	return output;
}

std::vector<std::string> CommandWithGenericParams::GetSignatureExpectationImpl(size_t const index) const
{
	std::vector<std::string> output;
	auto const method_name_length = commandWithoutParams.GetSignatureLength();
	if (index < method_name_length)
	{
		output = commandWithoutParams.GetSignatureExpectation(index);
	}
	else
	{
		output = genericParameters[index - method_name_length]->GetExpectedDomainSet();
	}
	return output;
}

size_t CommandWithGenericParams::GetSignatureLengthImpl() const
{
	return commandWithoutParams.GetSignatureLength() + genericParameters.size();
}

void CommandWithGenericParams::PrependSignatureImpl(std::string const &pre_sig)
{
	commandWithoutParams.PrependSignature(pre_sig);
}

std::string CommandWithGenericParams::GetHelpImpl() const
{
	std::string output = commandWithoutParams.GetHelp();
	output += "\n\tParameters:";
	for (auto parameter : genericParameters)
	{
		std::string param_help = parameter->GetHelp();
		param_help = replaceSubstringWithSubstring(param_help, "\n", "\n\t\t");
		output += "\n\t\t" + param_help;
	}
	return output;
}

} // namespace runtimecommandengine
} // namespace asi
