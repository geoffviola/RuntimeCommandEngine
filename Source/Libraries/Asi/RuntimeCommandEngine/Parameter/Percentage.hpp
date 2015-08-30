#ifndef ASI_RUNTIMECOMMANDENGINE_PARAMETER_PERCENTAGE_HPP
#define ASI_RUNTIMECOMMANDENGINE_PARAMETER_PERCENTAGE_HPP

#include "Range.hpp"
#include <string>

namespace asi
{
namespace runtimecommandengine
{
namespace parameter
{

/**
    Defines a range with exclusive parameter ranges
*/
class Percentage : public Range<double>
{
public:
	Percentage(std::string const &name);
	~Percentage();

protected:
	virtual std::string GetExpectedDomainImpl() const;
	virtual char const *GetTypeNameImpl() const { return "Percentage"; }
};

} // namespace parameter
} // namespace runtimecommandengine
} // namespace asi

#endif //ASI_RUNTIMECOMMANDENGINE_PARAMETER_PERCENTAGE_HPP
