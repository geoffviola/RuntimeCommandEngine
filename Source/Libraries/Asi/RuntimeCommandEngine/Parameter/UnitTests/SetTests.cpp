#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "Asi/RuntimeCommandEngine/Parameter/StringSet.hpp"

using ::asi::runtimecommandengine::parameter::StringSet;

TEST(SetTests, GetTypeName_Set_TypeNameIsCorrect)
{
	StringSet s("setname", {"a", "b"});

	auto set_typename_result = s.GetTypeName();

	EXPECT_STREQ("StringSet", set_typename_result);
}

TEST(SetTests, GetExpectedDomain_aAndB_ExpectedDomainIsCorrect)
{
	StringSet s("setname", {"a", "b"});

	auto expected_domain_result = s.GetExpectedDomain();

	EXPECT_STREQ("{a, b}", expected_domain_result.c_str());
}

class SetTestsInExpectedDomainTrue : public ::testing::TestWithParam<int>
{
};

TEST_P(SetTestsInExpectedDomainTrue, ReturnTrue)
{
	int set_size = GetParam();
	static std::vector<std::string> set_selection({"a", "b", "c", "d", "e", "f", "g"});
	std::vector<std::string> acceptable_input(set_selection.begin(), set_selection.begin() + set_size);
	StringSet set("name", acceptable_input);

	bool should_be_there = set.IsInExpectedDomain(set_selection[set_size - 1]);

	EXPECT_EQ(true, should_be_there);
}

class SetTestsInExpectedDomainFalse : public ::testing::TestWithParam<int>
{
};

TEST_P(SetTestsInExpectedDomainFalse, ReturnFalse)
{
	int set_size = GetParam();
	static std::vector<std::string> set_selection({"a", "b", "c", "d", "e", "f", "g"});
	std::vector<std::string> acceptable_input(set_selection.begin(), set_selection.begin() + set_size);
	StringSet set("name", acceptable_input);

	bool should_not_be_there = set.IsInExpectedDomain("sally");

	EXPECT_EQ(false, should_not_be_there);
}

INSTANTIATE_TEST_CASE_P(SetTests__IsInExpectedDomain_aAndB, SetTestsInExpectedDomainTrue, ::testing::Values(2));
INSTANTIATE_TEST_CASE_P(SetTests__IsInExpectedDomain_aAndBAndC, SetTestsInExpectedDomainTrue, ::testing::Values(3));
INSTANTIATE_TEST_CASE_P(SetTests__IsInExpectedDomain_aAndBAndCAndD, SetTestsInExpectedDomainTrue, ::testing::Values(4));
INSTANTIATE_TEST_CASE_P(SetTests__IsInExpectedDomain_aAndBAndCAndDAndE, SetTestsInExpectedDomainTrue,
                        ::testing::Values(5));
INSTANTIATE_TEST_CASE_P(SetTests__IsInExpectedDomain_aAndBAndCAndDAndEAndF, SetTestsInExpectedDomainTrue,
                        ::testing::Values(6));
INSTANTIATE_TEST_CASE_P(SetTests__IsInExpectedDomain_aAndBAndCAndDAndEAndFAndG, SetTestsInExpectedDomainTrue,
                        ::testing::Values(7));
INSTANTIATE_TEST_CASE_P(SetTests__IsInExpectedDomain_aAndB, SetTestsInExpectedDomainFalse, ::testing::Values(2));
INSTANTIATE_TEST_CASE_P(SetTests__IsInExpectedDomain_aAndBAndC, SetTestsInExpectedDomainFalse, ::testing::Values(3));
INSTANTIATE_TEST_CASE_P(SetTests__IsInExpectedDomain_aAndBAndCAndD, SetTestsInExpectedDomainFalse,
                        ::testing::Values(4));
INSTANTIATE_TEST_CASE_P(SetTests__IsInExpectedDomain_aAndBAndCAndDAndE, SetTestsInExpectedDomainFalse,
                        ::testing::Values(5));
INSTANTIATE_TEST_CASE_P(SetTests__IsInExpectedDomain_aAndBAndCAndDAndEAndF, SetTestsInExpectedDomainFalse,
                        ::testing::Values(6));
INSTANTIATE_TEST_CASE_P(SetTests__IsInExpectedDomain_aAndBAndCAndDAndEAndFAndG, SetTestsInExpectedDomainFalse,
                        ::testing::Values(7));
