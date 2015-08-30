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
	CommandWithoutParams cmd({ "sig1" }, "description", cbt.GetCallback());
	vector<string> input_tokens;

	auto const return_val = cmd.Evaluate(input_tokens);

	EXPECT_EQ(false, std::get<0>(return_val));
	EXPECT_EQ(false, cbt.WasCallbackCalled());
}

TEST(CommandWithoutParamsTests, Evaluate_NoParamsWrongToken_FalseUDUD)
{
	CallbackTester cbt;
	CommandWithoutParams cmd({ "sig1" }, "description", cbt.GetCallback());
	vector<string> input_tokens;
	input_tokens.push_back("wrong_token");

	auto const return_val = cmd.Evaluate(input_tokens);

	EXPECT_EQ(false, std::get<0>(return_val));
	EXPECT_EQ(false, cbt.WasCallbackCalled());
}

TEST(CommandWithoutParamsTests, Evaluate_NoParamsRightToken_CallbackCalledTrue1UCorrectString)
{
	static string const method_name("sig1");
	CallbackTester cbt;
	CommandWithoutParams cmd({ method_name }, "description", cbt.GetCallback());
	vector<string> input_tokens;
	input_tokens.push_back(method_name);
	CallbackTester ct;

	auto const return_val = cmd.Evaluate(input_tokens);

	EXPECT_EQ(true, std::get<0>(return_val));
	EXPECT_EQ(1U, std::get<1>(return_val));
	EXPECT_STREQ(string("received command \"" + method_name + "\"").c_str(), std::get<2>(return_val).c_str());
	EXPECT_EQ(true, cbt.WasCallbackCalled());
}

//TEST(CommandWithoutParamsTests, Evaluate_1ParamRightTokens_CallbackCalledTrue0UCorrectString)
//{
//	static string const method_name("sig1");
//	static string const parameter_name("param1");
//	CallbackTester cbt;
//	ConcreteParameterAbstract pa1(parameter_name);
//	Command cmd(cbt.GetCallback(), { method_name }, { &pa1 });
//	vector<string> input_tokens;
//	input_tokens.push_back(method_name);
//	input_tokens.push_back(parameter_name);
//	CallbackTester ct;
//	EXPECT_CALL(pa1, IsInExpectedDomainMock(parameter_name)).WillOnce(Return(true));
//
//	auto const return_val = cmd.Evaluate(input_tokens);
//
//	EXPECT_EQ(true, std::get<0>(return_val));
//	EXPECT_EQ(0U, std::get<1>(return_val));
//	EXPECT_STREQ("received command \"sig1 param1\"", std::get<2>(return_val).c_str());
//	EXPECT_EQ(true, cbt.WasCallbackCalled());
//}

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

//class CommandWithoutParamsTestsCheckSignature : public ::testing::TestWithParam<int>
//{
//protected:
//	void SetUp() override {}
//	void TearDown() override {}
//};
//
//TEST_P(CommandWithoutParamsTestsCheckSignature, GetSignatureExpectation__imp)
//{
//	auto const input = GetParam();
//	vector<ConcreteParameterAbstract> actual_parameters;
//	vector<ParameterAbstract *> parameters;
//	vector<string> signature;
//
//	for (auto i = 0; i < input; ++i)
//	{
//		std::stringstream ss;
//		ss << (i + 1);
//		ConcreteParameterAbstract new_param(ss.str().c_str());
//		actual_parameters.push_back(std::move(new_param));
//		signature.push_back(string(1, 'a' + static_cast<char>(i)));
//	}
//	auto const copy_pointer = [&parameters](ConcreteParameterAbstract &iter)
//	{
//		EXPECT_CALL(iter, GetExpectedDomainMock())
//			.WillOnce(Return(iter.GetName()));
//		parameters.push_back(&iter);
//	};
//	parameters.reserve(actual_parameters.size());
//	std::for_each(actual_parameters.begin(), actual_parameters.end(), copy_pointer);
//
//	CallbackTester cbt;
//	Command cmd(cbt.GetCallback(), signature, parameters);
//
//	for (int i = 0; i < input * 2; ++i)
//	{
//		string result = cmd.GetSignatureExpectation(i)[0];
//		std::stringstream ss;
//		if (i < input)
//		{
//			ss << static_cast<char>('a' + i);
//		}
//		else
//		{
//			ss << i + 1 - input;
//		}
//		EXPECT_STREQ(ss.str().c_str(), result.c_str());
//	}
//	EXPECT_EQ(false, cbt.WasCallbackCalled());
//}
//
//INSTANTIATE_TEST_CASE_P(CommandWithoutParamsTests_ConstructorAddParametersGetSignatureExpectation, CommandWithoutParamsTestsCheckSignature,
//                        ::testing::Range(1, 5));
