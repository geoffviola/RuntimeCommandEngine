#include "Percentage.hpp"

namespace asi
{
namespace runtimecommandengine
{
namespace parameter
{

Percentage::Percentage(std::string const &name)
    : Range<double>(name, 0.0, 100.0)
{
}

Percentage::~Percentage() {}

std::string Percentage::GetExpectedDomainImpl() const
{
	std::string output = "[0.0, 100.0]";
	return output;
}

} // namespace parameter
} // namespace runtimecommandengine
} // namespace asi
