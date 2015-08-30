#ifndef ASI_RUNTIMECOMMANDENGINE_STRING_HPP
#define ASI_RUNTIMECOMMANDENGINE_STRING_HPP

#include "ParameterAbstract.hpp"

namespace asi
{
namespace runtimecommandengine
{
namespace parameter
{

class String : public ParameterAbstract
{
public:
	String(std::string const &name);
	~String();

protected:
	std::string GetExpectedDomainImpl() const;
	bool IsInExpectedDomainImpl(std::string const &raw_value) const;
	char const *GetTypeNameImpl() const;
};

} // namespace parameter
} // namespace runtimecommandengine
} // namespace asi

#endif // ASI_RUNTIMECOMMANDENGINE_STRING_HPP
