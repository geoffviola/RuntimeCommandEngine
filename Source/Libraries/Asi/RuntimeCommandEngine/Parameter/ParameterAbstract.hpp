#ifndef ASI_RUNTIMECOMMANDENGINE_PARAMETERASTRACT_HPP
#define ASI_RUNTIMECOMMANDENGINE_PARAMETERASTRACT_HPP

#include <string>
#include <vector>
#include "Asi/RuntimeCommandEngine/StringUtils.hpp"

namespace asi
{
namespace runtimecommandengine
{
namespace parameter
{

/// Handles verification that a string is of its type.
class ParameterAbstract
{
public:
	explicit ParameterAbstract(std::string const &in_name)
	    : name(in_name)
	{
	}
	virtual ~ParameterAbstract() {}

	/// Get a string describing the expected input string value
	std::string GetExpectedDomain() const { return GetExpectedDomainImpl(); }
	/// Get a vector of strings describing the expected input string value
	std::vector<std::string> GetExpectedDomainSet() const { return GetExpectedDomainSetImpl(); }
	/// Determine if the string is a valid parameter of this type
	bool IsInExpectedDomain(std::string const &raw_value) const { return IsInExpectedDomainImpl(raw_value); }
	/// Get a textual representation of the subclass type name
	char const *GetTypeName() const { return GetTypeNameImpl(); }
	std::string GetName() const { return name; }

	/// Get serialized data formatted as yaml
	std::string GetHelp() const
	{
		std::string output;
		output += GetName() + ":";
		output += "\n\tDomain: " + GetExpectedDomain();
		output += "\n\tType: " + std::string(GetTypeName());
		return output;
	}

protected:
	virtual std::vector<std::string> GetExpectedDomainSetImpl() const
	{
		std::vector<std::string> output;
		output.push_back(GetExpectedDomain());
		return output;
	}
	virtual char const *GetTypeNameImpl() const = 0;
	virtual bool IsInExpectedDomainImpl(std::string const &raw_value) const = 0;
	virtual std::string GetExpectedDomainImpl() const = 0;

private:
	std::string const name;
};

} // namespace parameter
} // namespace runtimecommandengine
} // namespace asi

#endif //ASI_RUNTIMECOMMANDENGINE_PARAMETERASTRACT_HPP
