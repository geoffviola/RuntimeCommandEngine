#ifndef _ASI_RUNTIMECOMMANDENGINE_UNION_HPP_
#define _ASI_RUNTIMECOMMANDENGINE_UNION_HPP_

#include "ParameterAbstract.hpp"
#include <memory>

namespace asi
{
namespace runtimecommandengine
{
namespace parameter
{

class Union : public ParameterAbstract
{
public:
	Union(std::string const &name, ParameterAbstract *pm1, ParameterAbstract *pm2);
	~Union();

	bool isInExpectedDomain(std::string const &raw_value) const;
	char const *getTypeName() const;

private:
	std::string GetExpectedDomainImpl() const override;
	std::vector<std::string> GetExpectedDomainSetImpl() const override;
	std::string generateTypeName() const;

	std::vector<std::shared_ptr<ParameterAbstract> > unionizedParameters;
};

} // namespace parameter
} // namespace runtimecommandengine
} // namespace asi

#endif //_ROBOSIM_RUNTIMECOMMAND_UNION_HPP_
