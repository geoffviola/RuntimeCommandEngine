#include "Asi/RuntimeCommandEngine/CommandWithoutParams.hpp"

#include "Asi/Wrappers/GTest.hpp"
#include "gmock/gmock.h"
#include <memory>

#include "CallbackTester.hpp"

using asi::runtimecommandengine::CommandWithoutParams;
using std::vector;
using std::string;
using ::testing::Return;
using ::testing::Values;
using ::testing::Value;

TEST(CommandWithoutParamsTests, Evaluate_NoParamsNoTokens_FalseUDUD)
{
	CallbackTester cbt;
	CommandWithoutParams cmd({"sig1"}, "description", cbt.GetCallback());
	vector<string> input_tokens;

	auto const return_val = cmd.Evaluate(input_tokens);

	EXPECT_EQ(false, std::get<0>(return_val));
	EXPECT_EQ(false, cbt.WasCallbackCalled());
}

TEST(CommandWithoutParamsTests, Evaluate_NoParamsWrongToken_FalseUDUD)
{
	CallbackTester cbt;
	CommandWithoutParams cmd({"sig1"}, "description", cbt.GetCallback());
	vector<string> input_tokens;
	input_tokens.push_back("wrong_token");

	auto const return_val = cmd.Evaluate(input_tokens);

	EXPECT_EQ(false, std::get<0>(return_val));
	EXPECT_EQ(false, cbt.WasCallbackCalled());
}

TEST(CommandWithoutParamsTests, Evaluate_NoParamsRightToken_CallbackCalledTrue0CorrectString)
{
	static string const method_name("sig1");
	CallbackTester cbt;
	CommandWithoutParams cmd({method_name}, "description", cbt.GetCallback());
	vector<string> input_tokens;
	input_tokens.push_back(method_name);
	CallbackTester ct;

	auto const return_val = cmd.Evaluate(input_tokens);

	EXPECT_EQ(true, std::get<0>(return_val));
	EXPECT_EQ(0, std::get<1>(return_val));
	EXPECT_STREQ(string("received command \"" + method_name + "\"").c_str(), std::get<2>(return_val).c_str());
	EXPECT_EQ(true, cbt.WasCallbackCalled());
}

TEST(CommandWithoutParamsTests, ConstructorWithVector_2Names_SignatureRetrievable)
{
	vector<string> method_names;
	method_names.push_back("a");
	method_names.push_back("b");
	CallbackTester cbt;
	CommandWithoutParams cmd(method_names, "description", cbt.GetCallback());

	string result0 = cmd.GetSignatureExpectation(0)[0];
	string result1 = cmd.GetSignatureExpectation(1)[0];
	EXPECT_STREQ("a", result0.c_str());
	EXPECT_STREQ("b", result1.c_str());
	EXPECT_EQ(false, cbt.WasCallbackCalled());
}
