#ifndef _ASI_RUNTIMECOMMANDENGINE_PARAMETER_PERCENTAGE_HPP_
#define _ASI_RUNTIMECOMMANDENGINE_PARAMETER_PERCENTAGE_HPP_

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

#endif //_ASI_RUNTIMECOMMANDENGINE_PARAMETER_PERCENTAGE_HPP_
