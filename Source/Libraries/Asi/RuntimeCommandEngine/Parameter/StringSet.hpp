#ifndef ASI_RUNTIMECOMMANDENGINE_STRINGSET_HPP
#define ASI_RUNTIMECOMMANDENGINE_STRINGSET_HPP

#include "ParameterAbstract.hpp"
#include <string>
#include <vector>

namespace asi
{
namespace runtimecommandengine
{
namespace parameter
{

class StringSet : public ParameterAbstract
{
public:
	StringSet(std::string const &name, std::vector<std::string> const &acceptable_inputs);
	virtual ~StringSet();

protected:
	virtual std::string GetExpectedDomainImpl() const override;
	virtual bool IsInExpectedDomainImpl(std::string const &raw_value) const override;
	virtual char const *GetTypeNameImpl() const override { return "StringSet"; }

private:
	virtual std::vector<std::string> GetExpectedDomainSetImpl() const override;

	std::vector<std::string> acceptableInputs;
};

} // namespace parameter
} // namespace runtimecommandengine
} // namespace asi

#endif //ASI_RUNTIMECOMMANDENGINE_STRINGSET_HPP
