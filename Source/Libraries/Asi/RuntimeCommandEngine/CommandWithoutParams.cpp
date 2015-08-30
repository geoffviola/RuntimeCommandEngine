#include "CommandWithoutParams.hpp"
#include "StringUtils.hpp"
#include <algorithm>

namespace asi
{
namespace runtimecommandengine
{

CommandWithoutParams::CommandWithoutParams(std::vector<std::string> const &in_signature,
                                           std::string const &in_description, CallFunType call_fun)
    : methodNameTokens(in_signature)
    , description(in_description)
    , callFun(call_fun)
{
	SelfCheck();
}

std::tuple<bool, uint32_t> CommandWithoutParams::AreTokensInSignature(std::vector<std::string> tokens) const
{
	size_t i = 0;
	for (; i < tokens.size() && i < methodNameTokens.size() && iequals(tokens[i], methodNameTokens[i]); ++i)
	{
	}
	return std::tuple <bool, uint32_t>(methodNameTokens.size() == i && tokens.size() == i, i);
}


std::tuple<bool, uint32_t, std::string> CommandWithoutParams::EvaluateImpl(std::vector<std::string> const &tokens) const
{
	std::tuple<bool, uint32_t, std::string> output;

	auto const are_tokens_in_sig(AreTokensInSignature(tokens));

	std::get<0>(output) = std::get<0>(are_tokens_in_sig);
	std::get<1>(output) = std::get<1>(are_tokens_in_sig);
	if (std::get<0>(are_tokens_in_sig))
	{
		std::get<2>(output) = GetReceivedMessage(tokens);
		callFun(tokens);
	}

	return output;
}

std::vector<std::string> CommandWithoutParams::GetSignatureExpectationImpl(size_t const index) const
{
	std::vector<std::string> output;
	if (index < methodNameTokens.size())
	{
		output.push_back(methodNameTokens[index]);
	}
	return output;
}

void CommandWithoutParams::PrependSignatureImpl(std::string const &pre_sig)
{
	methodNameTokens.insert(methodNameTokens.begin(), pre_sig);
}

std::string CommandWithoutParams::GetHelpImpl() const
{
	std::string output;
	for (auto method_name_token : methodNameTokens)
	{
		output += method_name_token + " ";
	}
	if (methodNameTokens.size() > 0)
	{
		output.pop_back();
	}
	output += ":";
	output += "\n\tDescription: " + description;
	return output;
}

void CommandWithoutParams::SelfCheck()
{
	for (auto const method_name : methodNameTokens)
	{
		assert(method_name.size() > 0);
	}
}

} // namespace runtimecommandengine
} // namespace asi
