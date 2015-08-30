#ifndef _ASI_RUNTIMECOMMANDENGINE_STRING_HPP_
#define _ASI_RUNTIMECOMMANDENGINE_STRING_HPP_

#include "ParameterAbstract.hpp"

namespace asi {
namespace runtimecommandengine {
namespace parameter {

class String : public ParameterAbstract
{
public:
	String(std::string const& name);
	~String();
	
protected:
	std::string GetExpectedDomainImpl() const;
	bool IsInExpectedDomainImpl(std::string const& raw_value) const;
	char const* GetTypeNameImpl() const;

};

} // namespace parameter
} // namespace runtimecommandengine
} // namespace asi

#endif //_ASI_RUNTIMECOMMANDENGINE_STRING_HPP_
