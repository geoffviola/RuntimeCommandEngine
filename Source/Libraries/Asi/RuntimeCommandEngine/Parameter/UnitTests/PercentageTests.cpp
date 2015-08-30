#include "gtest/gtest.h"
#include "gmock/gmock.h"
    
#include "Asi/RuntimeCommandEngine/Parameter/Percentage.hpp"

using asi::runtimecommandengine::parameter::Range;
using asi::runtimecommandengine::parameter::Percentage;
using std::string;

TEST(PercentageTests, PercentageTests__getTypeName_Percentage)
{
	Percentage percentage("name");

	auto type_name = percentage.GetTypeName();

	EXPECT_STREQ("Percentage", type_name);
}

TEST(PercentageTests, PercentageTests__GetExpectedDomain_0To100)
{
	Percentage percentage("name");

	auto domain_name = percentage.GetExpectedDomain();

	EXPECT_STREQ("[0.0, 100.0]", domain_name.c_str());
}
