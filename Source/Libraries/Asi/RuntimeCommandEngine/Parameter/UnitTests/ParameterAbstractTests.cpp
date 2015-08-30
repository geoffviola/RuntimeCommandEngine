#include "Asi/RuntimeCommandEngine/Parameter/ParameterAbstract.hpp"

#include "Asi/Wrappers/GTest.hpp"
#include "gmock/gmock.h"

namespace asi
{
namespace runtimecommandengine
{
namespace parameter
{
class ParameterAbstractConcrete : public ParameterAbstract
{
public:
	ParameterAbstractConcrete(std::string const &in_name)
	    : ParameterAbstract(in_name)
	{
	}
	~ParameterAbstractConcrete() {}

protected:
	std::string GetExpectedDomainImpl() const override { return ""; }
	bool IsInExpectedDomainImpl(std::string const &) const override { return true; }
	char const *GetTypeNameImpl() const override { return "ParameterAbstractConcrete"; }
};
} // namespace parameter
} // namespace runtimecommandengine
} // namespace asi

using ::asi::runtimecommandengine::parameter::ParameterAbstractConcrete;
using ::std::string;

TEST(ParameterAbstractTests, getName_NameFromConstructor_NameGotten)
{
	ParameterAbstractConcrete pac("name");

	string result = pac.GetName();

	EXPECT_STREQ("name", result.c_str());
}
