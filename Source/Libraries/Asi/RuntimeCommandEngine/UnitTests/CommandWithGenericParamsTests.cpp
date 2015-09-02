#include "Asi/RuntimeCommandEngine/CommandWithGenericParams.hpp"

#include "Asi/Wrappers/GTest.hpp"
#include "gmock/gmock.h"
#include <memory>

#include "CallbackTester.hpp"

using asi::runtimecommandengine::CommandWithGenericParams;
using asi::runtimecommandengine::parameter::ParameterAbstract;
using std::vector;
using std::string;
using ::testing::Return;
using ::testing::Values;
using ::testing::Value;

class ConcreteParameterAbstract : public ParameterAbstract
{
public:
	ConcreteParameterAbstract()
	    : ParameterAbstract("ConcreteParameterAbstract")
	{
	}

	explicit ConcreteParameterAbstract(string const &in_name)
	    : ParameterAbstract(in_name)
	{
	}

	ConcreteParameterAbstract(ConcreteParameterAbstract const &other)
	    : ParameterAbstract(other.GetName())
	{
	}

	MOCK_CONST_METHOD0(GetTypeNameMock, char const *(void));
	MOCK_CONST_METHOD1(IsInExpectedDomainMock, bool(string const &));
	MOCK_CONST_METHOD0(GetExpectedDomainMock, string(void));

private:
	char const *GetTypeNameImpl() const override { return GetTypeNameMock(); }
	bool IsInExpectedDomainImpl(string const &raw_value) const override
	{
		return IsInExpectedDomainMock(raw_value);
	}
	string GetExpectedDomainImpl() const override { return GetExpectedDomainMock(); }
};

TEST(CommandWithGenericParamsTests, Evaluate_1ParamNoTokens_FalseUDUD)
{
	CallbackTester cbt;
	ConcreteParameterAbstract param;
	static ParameterAbstract const *const param_arr[] = {&param};
	CommandWithGenericParams cmd({"sig1"}, "description", cbt.GetCallback(), param_arr, sizeof(param_arr));
	vector<string> input_tokens;

	auto const return_val = cmd.Evaluate(input_tokens);

	EXPECT_EQ(false, std::get<0>(return_val));
	EXPECT_EQ(false, cbt.WasCallbackCalled());
}

TEST(CommandWithGenericParamsTests, Evaluate_1ParamWrongToken_FalseUDUD)
{
	CallbackTester cbt;
	ConcreteParameterAbstract param;
	static ParameterAbstract const *const param_arr[] = {&param};
	CommandWithGenericParams cmd({"sig1"}, "description", cbt.GetCallback(), param_arr, sizeof(param_arr));
	vector<string> input_tokens;
	input_tokens.push_back("wrong_token");

	auto const return_val = cmd.Evaluate(input_tokens);

	EXPECT_EQ(false, std::get<0>(return_val));
	EXPECT_EQ(false, cbt.WasCallbackCalled());
}

TEST(CommandWithGenericParamsTests, Evaluate_1ParamRightToken_CallbackCalledTrue1CorrectString)
{
	static string const method_name("sig1");
	static string const param_name("param1");
	CallbackTester cbt;
	ConcreteParameterAbstract param;
	static ParameterAbstract const *const param_arr[] = {&param};
	CommandWithGenericParams cmd({method_name}, "description", cbt.GetCallback(), param_arr, 1);
	vector<string> input_tokens;
	input_tokens.push_back(method_name);
	input_tokens.push_back(param_name);
	CallbackTester ct;

	EXPECT_CALL(param, IsInExpectedDomainMock(param_name)).WillOnce(Return(true));

	auto const return_val = cmd.Evaluate(input_tokens);

	EXPECT_EQ(true, std::get<0>(return_val));
	EXPECT_EQ(1, std::get<1>(return_val));
	EXPECT_STREQ(string("received command \"" + method_name + " " + param_name + "\"").c_str(),
	             std::get<2>(return_val).c_str());
	EXPECT_EQ(true, cbt.WasCallbackCalled());
}

TEST(CommandWithGenericParamsTests, ConstructorWithVector_2Names_SignatureRetrievable)
{
	vector<string> method_names;
	method_names.push_back("a");
	method_names.push_back("b");
	CallbackTester cbt;
	ConcreteParameterAbstract param;
	static ParameterAbstract const *const param_arr[] = {&param};
	CommandWithGenericParams cmd(method_names, "description", cbt.GetCallback(), param_arr, sizeof(param_arr));

	string result0 = cmd.GetSignatureExpectation(0)[0];
	string result1 = cmd.GetSignatureExpectation(1)[0];
	EXPECT_STREQ("a", result0.c_str());
	EXPECT_STREQ("b", result1.c_str());
	EXPECT_EQ(false, cbt.WasCallbackCalled());
}

class CommandWithGenericParamsTestsCheckSignature : public ::testing::TestWithParam<int>
{
protected:
	void SetUp() override {}
	void TearDown() override {}
};

TEST_P(CommandWithGenericParamsTestsCheckSignature, GetSignatureExpectation__imp)
{
	auto const input = GetParam();
	vector<ConcreteParameterAbstract> actual_parameters;
	vector<ParameterAbstract *> parameters;
	vector<string> signature;

	for (auto i = 0; i < input; ++i)
	{
		std::stringstream ss;
		ss << (i + 1);
		ConcreteParameterAbstract new_param(ss.str().c_str());
		actual_parameters.push_back(std::move(new_param));
		signature.push_back(string(1, 'a' + static_cast<char>(i)));
	}
	auto const copy_pointer = [&parameters](ConcreteParameterAbstract &iter)
	{
		EXPECT_CALL(iter, GetExpectedDomainMock()).WillOnce(Return(iter.GetName()));
		parameters.push_back(&iter);
	};
	parameters.reserve(actual_parameters.size());
	std::for_each(actual_parameters.begin(), actual_parameters.end(), copy_pointer);

	CallbackTester cbt;
	CommandWithGenericParams cmd(signature, "", cbt.GetCallback(), &parameters[0],
	                             static_cast<int>(parameters.size()));

	for (int i = 0; i < input * 2; ++i)
	{
		string result = cmd.GetSignatureExpectation(i)[0];
		std::stringstream ss;
		if (i < input)
		{
			ss << static_cast<char>('a' + i);
		}
		else
		{
			ss << i + 1 - input;
		}
		EXPECT_STREQ(ss.str().c_str(), result.c_str());
	}
	EXPECT_EQ(false, cbt.WasCallbackCalled());
}

INSTANTIATE_TEST_CASE_P(CommandWithGenericParamsTests_ConstructorAddParametersGetSignatureExpectation,
                        CommandWithGenericParamsTestsCheckSignature, ::testing::Range(1, 5));
