#include "Union.hpp"
#include <functional>
#include <algorithm>
#include <Asi/RuntimeCommandEngine/StringUtils.hpp>

namespace asi
{
namespace runtimecommandengine
{
namespace parameter
{

Union::Union(std::string const &name, ParameterAbstract *pm1, ParameterAbstract *pm2)
    : ParameterAbstract(name)
{
	unionizedParameters.push_back(std::shared_ptr<ParameterAbstract>(pm1));
	unionizedParameters.push_back(std::shared_ptr<ParameterAbstract>(pm2));
}

Union::~Union() {}

std::string Union::GetExpectedDomainImpl() const
{
	std::string output = std::string("{");
	for (auto unionizedParameter : unionizedParameters)
	{
		if (output.length() > 1)
		{
			output += ", ";
		}
		output += unionizedParameter->GetExpectedDomain();
	}
	output += std::string("}");
	return output;
}

std::vector<std::string> Union::GetExpectedDomainSetImpl() const
{
	std::vector<std::string> output;
	std::vector<std::string> raw_set;
	for (auto unionizedParameter : unionizedParameters)
	{
		for (auto item_in_parameter : unionizedParameter->GetExpectedDomainSet())
		{
			raw_set.push_back(item_in_parameter);
		}
	}
	for (auto new_item : raw_set)
	{
		bool string_is_new =
		    !std::any_of(output.begin(), output.end(), std::bind(&iequals, new_item, std::placeholders::_1));
		if (string_is_new)
		{
			output.push_back(new_item);
		}
	}
	return output;
}

bool Union::isInExpectedDomain(std::string const &raw_value) const
{
	bool output = false;

	for (auto unionizedParameter : unionizedParameters)
	{
		if (unionizedParameter->IsInExpectedDomain(raw_value))
		{
			if (false == output)
			{
				output = true;
			}
			else
			{
				// return false if in multiple domains
				output = false;
				break;
			}
		}
	}

	return output;
}

std::string Union::generateTypeName() const
{
	std::string output = "Union(";
	for (auto unionizedParameter : unionizedParameters)
	{
		if (output.length() > 6)
		{
			output += ", ";
		}
		output += unionizedParameter->GetTypeName();
	}
	output += ")";
	return output;
}

char const *Union::getTypeName() const
{
	static std::string const output = generateTypeName();
	return output.c_str();
}

} // namespace parameter
} // namespace runtimecommandengine
} // namespace asi
