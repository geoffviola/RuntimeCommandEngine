#include "StringSet.hpp"
#include <Asi/RuntimeCommandEngine/StringUtils.hpp>

namespace asi
{
namespace runtimecommandengine
{
namespace parameter
{

StringSet::StringSet(std::string const &name, std::vector<std::string> const &acceptable_inputs)
    : ParameterAbstract(name)
    , acceptableInputs(acceptable_inputs)
{
}

StringSet::~StringSet() {}

std::vector<std::string> StringSet::GetExpectedDomainSetImpl() const { return acceptableInputs; }

std::string StringSet::GetExpectedDomainImpl() const
{
	std::string output;
	for (auto acceptableInput : acceptableInputs)
	{
		if (output.length() > 0)
		{
			output += ", ";
		}
		else
		{
			output = "{";
		}
		output += acceptableInput;
	}
	output += "}";
	return output;
}

bool StringSet::IsInExpectedDomainImpl(std::string const &raw_value) const
{
	bool output = false;
	for (auto acceptableInput : acceptableInputs)
	{
		if (iequals(acceptableInput, raw_value))
		{
			output = true;
		}
	}
	return output;
}

} // namespace parameter
} // namespace runtimecommandengine
} // namespace asi
