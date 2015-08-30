#include "Asi/Wrappers/GTest.hpp"

#include "Asi/RuntimeCommandEngine/Parameter/Range.hpp"

namespace asi
{
namespace runtimecommandengine
{
namespace parameter
{
class RangePublic : public Range<double>
{
public:
	RangePublic(std::string const &name, double in_min, double in_max)
	    : Range(name, in_min, in_max)
	{
	}
};
} // namespace parameter
} // namespace runtimecommandengine
} // namespace asi

using ::asi::runtimecommandengine::parameter::Range;
using ::asi::runtimecommandengine::parameter::RangePublic;
using ::std::string;

TEST(RangeTests, IsInExpectedDomain_0inn1to1_true)
{
	Range<int32_t> range("", -1, 1);

	auto const result = range.IsInExpectedDomain("0");

	EXPECT_EQ(true, result);
}

TEST(RangeTests, IsInExpectedDomain_SallyInn1to1_false)
{
	Range<int32_t> range("", -1, 1);

	auto const result = range.IsInExpectedDomain("Sally");

	EXPECT_EQ(false, result);
}

TEST(RangeTests, IsInExpectedDomain_20inn1to1_false)
{
	Range<int32_t> range("", -1, 1);

	auto const result = range.IsInExpectedDomain("20");

	EXPECT_EQ(false, result);
}

TEST(RangeTests, GetTypeName_double_RangeDouble)
{
	Range<double> range("range", -1.0, 1.0);

	auto const get_type_name_result = range.GetTypeName();

	EXPECT_STREQ((std::string("Range<") + std::string(typeid(double).name()) + std::string(">")).c_str(),
	             get_type_name_result);
}

TEST(RangeTests, GetValue_0_0)
{
	RangePublic range("name", -1, 1);

	auto const get_min_result = range.GetMin();
	auto const get_max_result = range.GetMax();

	auto value_result = range.GetValue("0");

	EXPECT_EQ(-1, get_min_result);
	EXPECT_EQ(1, get_max_result);
	EXPECT_EQ(0, value_result);
}
