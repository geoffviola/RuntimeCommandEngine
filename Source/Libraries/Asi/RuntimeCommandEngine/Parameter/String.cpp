#include "String.hpp"

namespace asi
{
namespace runtimecommandengine
{
namespace parameter
{

String::String(std::string const &name)
    : ParameterAbstract(name)
{
}

String::~String() {}

std::string String::GetExpectedDomainImpl() const { return std::string("AnyString"); }

bool String::IsInExpectedDomainImpl(std::string const &raw_value) const
{
	bool output = raw_value.length() > 0 ? true : false;
	return output;
}

char const *String::GetTypeNameImpl() const { return "String"; }

} // namespace parameter
} // namespace runtimecommandengine
} // namespace asi
