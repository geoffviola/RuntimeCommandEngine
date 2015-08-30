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
	genericParameters.reserve(num_params);
	for (int i = 0; i < num_params; ++i)
	{
		genericParameters.push_back(in_parameters[i]);
	}
}

std::tuple<bool, uint32_t, std::string>
CommandWithGenericParams::EvaluateImpl(std::vector<std::string> const &tokens) const
{
	std::tuple<bool, uint32_t, std::string> output(false, 0U, "");

	// Check method names
	std::vector<std::string> candidate_method_name;
	if (tokens.size() < commandWithoutParams.GetSignatureLength() || tokens.size() < genericParameters.size())
	{
		candidate_method_name = tokens;
	}
	else
	{
		candidate_method_name = std::vector<std::string>(tokens.begin(), tokens.end() - genericParameters.size());
	}
	auto const cwp_atis = commandWithoutParams.AreTokensInSignature(candidate_method_name);

	// Check parameter domains
	size_t last_good_index_p1 = std::get<1>(cwp_atis);
	if (true == std::get<0>(cwp_atis))
	{
		bool match = last_good_index_p1 != tokens.size();
		for (; last_good_index_p1 < tokens.size() && match; ++last_good_index_p1)
		{
			match = genericParameters[last_good_index_p1 - commandWithoutParams.GetSignatureLength()]
				          ->IsInExpectedDomain(tokens[last_good_index_p1]);
		}
		std::get<0>(output) = match;
		std::get<1>(output) = last_good_index_p1;
		if (match)
		{
			commandWithoutParams.CallFun(tokens);
			std::get<2>(output) = GetReceivedMessage(tokens);
		}
	}
	// size_t i = 0;
	// bool current_match = true;
	// while (i < tokens.size() && current_match && i < methodNameTokens.size() + genericParameters.size())
	//{
	//	current_match = false;
	//	if (i < methodNameTokens.size() + genericParameters.size())
	//	{
	//		if ((i < methodNameTokens.size() && iequals(tokens[i], methodNameTokens[i]) ||
	//		     (i >= methodNameTokens.size() &&
	//		      genericParameters[i - methodNameTokens.size()]->IsInExpectedDomain(tokens[i]))))
	//		{
	//			current_match = true;
	//			++i;
	//		}
	//	}
	//}

	// if (methodNameTokens.size() + genericParameters.size() == i && tokens.size() == i)
	//{
	//	std::get<0>(output) = true;
	//	std::string flattened_tokens;
	//	for (auto token : tokens)
	//	{
	//		if (flattened_tokens.size() > 0)
	//		{
	//			flattened_tokens += " ";
	//		}
	//		flattened_tokens += token;
	//	}
	//	std::get<2>(output) = "received command \"" + flattened_tokens + "\"";
	//	callFun(tokens);
	//}
	// else
	//{
	//	std::get<0>(output) = false;
	//	std::get<1>(output) = i;
	//}

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
	// for (auto method_name_token : methodNameTokens)
	//{
	//	output += method_name_token + " ";
	//}
	// if (methodNameTokens.size() > 0)
	//{
	//	output.pop_back();
	//}
	// output += ":";
	// output += "\n\tDescription: " + description;
	// if (genericParameters.size())
	//{
	//	output += "\n\tParameters:";
	//	for (auto parameter : genericParameters)
	//	{
	//		std::string param_help = parameter->GetHelp();
	//		param_help = replaceSubstringWithSubstring(param_help, "\n", "\n\t\t");
	//		output += "\n\t\t" + param_help;
	//	}
	//}
	return output;
}

} // namespace runtimecommandengine
} // namespace asi
