#include "Asi/RuntimeCommandEngine/CommandWithParams.hpp"

#include "Asi/Wrappers/GTest.hpp"
#include "gmock/gmock.h"
#include <memory>

#include "CallbackTesterWithParams.hpp"
#include <Asi/RuntimeCommandEngine/UnitTests/CallbackTester.hpp>

using asi::runtimecommandengine::CommandWithParams;
using asi::runtimecommandengine::parameter::ParameterAbstract;
using std::vector;
using std::string;
using ::testing::Return;
using ::testing::Values;
using ::testing::Value;

template <class T>
class ConcreteParameterMock : public ParameterAbstract
{
public:
	typedef T ReturnType;

	ConcreteParameterMock()
	    : ParameterAbstract("ConcreteParameterAbstract")
	{
	}

	explicit ConcreteParameterMock(string const &in_name)
	    : ParameterAbstract(in_name)
	{
	}

	ConcreteParameterMock(ConcreteParameterMock const &other)
	    : ParameterAbstract(other.GetName())
	{
	}

	MOCK_CONST_METHOD1_T(GetValue, T(std::string));

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

template <class T>
class ParameterAbstractWrapper : public ParameterAbstract
{
public:
	typedef typename T::ReturnType ReturnType;

	explicit ParameterAbstractWrapper(T *const in_pa)
	    : ParameterAbstract(in_pa->GetName())
	    , pa(in_pa)
	{
	}

	typename T::ReturnType GetValue(std::string token) const { return pa->GetValue(token); }
	inline T *GetPA() { return pa; }

private:
	std::vector<std::string> GetExpectedDomainSetImpl() const override { return pa->GetExpectedDomainSet(); }
	char const *GetTypeNameImpl() const override { return pa->GetTypeName(); }
	bool IsInExpectedDomainImpl(std::string const &raw_value) const override
	{
		return pa->IsInExpectedDomain(raw_value);
	}
	std::string GetExpectedDomainImpl() const override { return pa->GetExpectedDomain(); }

	T *const pa;
};

TEST(CommandTests, Evaluate_1ParamRightTokens_CallbackCalledTrue1CorrectString)
{
	static string const method_name("sig1");
	static string const parameter_name("param1");
	CallbackTesterWithParams<int32_t> cbt;
	ConcreteParameterMock<int32_t> pa1(parameter_name);
	ParameterAbstractWrapper<ConcreteParameterMock<int32_t> > paw(&pa1);
	CommandWithParams<ParameterAbstractWrapper<ConcreteParameterMock<int32_t> > > cmd({method_name}, "description",
	                                                                                  cbt.GetCallback(), paw);
	vector<string> input_tokens;
	input_tokens.push_back(method_name);
	input_tokens.push_back(parameter_name);
	CallbackTester ct;

	EXPECT_CALL(pa1, IsInExpectedDomainMock(parameter_name)).WillOnce(Return(true));
	EXPECT_CALL(pa1, GetValue(parameter_name)).WillOnce(Return(32));

	auto const return_val = cmd.Evaluate(input_tokens);

	EXPECT_EQ(true, std::get<0>(return_val));
	EXPECT_EQ(1, std::get<1>(return_val));
	EXPECT_STREQ("received command \"sig1 param1\"", std::get<2>(return_val).c_str());
	EXPECT_EQ(true, cbt.WasCallbackCalled());
}

TEST(CommandTests, Evaluate_1ParamOnSigTokens_CallbackCalledFalse0CorrectString)
{
	static string const method_name("sig1");
	static string const parameter_name("param1");
	CallbackTesterWithParams<int32_t> cbt;
	ConcreteParameterMock<int32_t> pa1(parameter_name);
	ParameterAbstractWrapper<ConcreteParameterMock<int32_t> > paw(&pa1);
	CommandWithParams<ParameterAbstractWrapper<ConcreteParameterMock<int32_t> > > cmd({method_name}, "description",
	                                                                                  cbt.GetCallback(), paw);
	vector<string> input_tokens;
	input_tokens.push_back(method_name);
	CallbackTester ct;

	auto const return_val = cmd.Evaluate(input_tokens);

	EXPECT_EQ(false, std::get<0>(return_val));
	EXPECT_EQ(0, std::get<1>(return_val));
	EXPECT_STREQ("", std::get<2>(return_val).c_str());
	EXPECT_EQ(false, cbt.WasCallbackCalled());
}

TEST(CommandTests, Evaluate_1ParamWrongParamToken_CallbackCalledFalse0CorrectString)
{
	static string const method_name("sig1");
	static string const parameter_name("param1");
	static string const not_parameter_name("notparam1");
	CallbackTesterWithParams<int32_t> cbt;
	ConcreteParameterMock<int32_t> pa1(parameter_name);
	ParameterAbstractWrapper<ConcreteParameterMock<int32_t> > paw(&pa1);
	CommandWithParams<ParameterAbstractWrapper<ConcreteParameterMock<int32_t> > > cmd({method_name}, "description",
	                                                                                  cbt.GetCallback(), paw);
	vector<string> input_tokens;
	input_tokens.push_back(method_name);
	input_tokens.push_back(not_parameter_name);
	CallbackTester ct;

	EXPECT_CALL(pa1, IsInExpectedDomainMock(not_parameter_name)).WillOnce(Return(false));

	auto const return_val = cmd.Evaluate(input_tokens);

	EXPECT_EQ(false, std::get<0>(return_val));
	EXPECT_EQ(0, std::get<1>(return_val));
	EXPECT_STREQ("", std::get<2>(return_val).c_str());
	EXPECT_EQ(false, cbt.WasCallbackCalled());
}

TEST(CommandTests, Evaluate_2ParamRightSig1WrongParamToken_CallbackCalledFalse0CorrectString)
{
	static string const method_name("sig1");
	static string const parameter_name_1("param_1");
	static string const parameter_name_2("param_2");
	static string const not_parameter_name_1("not_param_1");
	CallbackTesterWithParams<int32_t, int32_t> cbt;
	ConcreteParameterMock<int32_t> pa_1(parameter_name_1);
	ConcreteParameterMock<int32_t> pa_2(parameter_name_2);
	ParameterAbstractWrapper<ConcreteParameterMock<int32_t> > paw_1(&pa_1);
	ParameterAbstractWrapper<ConcreteParameterMock<int32_t> > paw_2(&pa_2);
	CommandWithParams<ParameterAbstractWrapper<ConcreteParameterMock<int32_t> >,
	                  ParameterAbstractWrapper<ConcreteParameterMock<int32_t> > > cmd({method_name}, "description",
	                                                                                  cbt.GetCallback(), paw_1,
	                                                                                  paw_2);
	vector<string> input_tokens;
	input_tokens.push_back(method_name);
	input_tokens.push_back(not_parameter_name_1);
	CallbackTester ct;

	EXPECT_CALL(pa_1, IsInExpectedDomainMock(not_parameter_name_1)).WillOnce(Return(false));

	auto const return_val = cmd.Evaluate(input_tokens);

	EXPECT_EQ(false, std::get<0>(return_val));
	EXPECT_EQ(0, std::get<1>(return_val));
	EXPECT_STREQ("", std::get<2>(return_val).c_str());
	EXPECT_EQ(false, cbt.WasCallbackCalled());
}

TEST(CommandTests, Evaluate_2ParamRightSig1RightParamToken_CallbackCalledFalse1CorrectString)
{
	static string const method_name("sig1");
	static string const parameter_name_1("param_1");
	static string const parameter_name_2("param_2");
	CallbackTesterWithParams<int32_t, int32_t> cbt;
	ConcreteParameterMock<int32_t> pa_1(parameter_name_1);
	ConcreteParameterMock<int32_t> pa_2(parameter_name_2);
	ParameterAbstractWrapper<ConcreteParameterMock<int32_t> > paw_1(&pa_1);
	ParameterAbstractWrapper<ConcreteParameterMock<int32_t> > paw_2(&pa_2);
	CommandWithParams<ParameterAbstractWrapper<ConcreteParameterMock<int32_t> >,
		ParameterAbstractWrapper<ConcreteParameterMock<int32_t> > > cmd({ method_name }, "description",
			cbt.GetCallback(), paw_1,
			paw_2);
	vector<string> input_tokens;
	input_tokens.push_back(method_name);
	input_tokens.push_back(parameter_name_1);
	CallbackTester ct;

	EXPECT_CALL(pa_1, IsInExpectedDomainMock(parameter_name_1)).WillOnce(Return(true));

	auto const return_val = cmd.Evaluate(input_tokens);

	EXPECT_EQ(false, std::get<0>(return_val));
	EXPECT_EQ(1, std::get<1>(return_val));
	EXPECT_STREQ("", std::get<2>(return_val).c_str());
	EXPECT_EQ(false, cbt.WasCallbackCalled());
}

TEST(CommandTests, Evaluate_2Param1RightToken1WrongToken_CallbackCalledFalse1CorrectString)
{
	static string const method_name("sig1");
	static string const parameter_name_1("param_1");
	static string const parameter_name_2("param_2");
	CallbackTesterWithParams<int32_t, int32_t> cbt;
	ConcreteParameterMock<int32_t> pa_1(parameter_name_1);
	ConcreteParameterMock<int32_t> pa_2(parameter_name_2);
	ParameterAbstractWrapper<ConcreteParameterMock<int32_t> > paw_1(&pa_1);
	ParameterAbstractWrapper<ConcreteParameterMock<int32_t> > paw_2(&pa_2);
	CommandWithParams<ParameterAbstractWrapper<ConcreteParameterMock<int32_t> >,
		ParameterAbstractWrapper<ConcreteParameterMock<int32_t> > > cmd({ method_name }, "description",
			cbt.GetCallback(), paw_1,
			paw_2);
	vector<string> input_tokens;
	input_tokens.push_back(method_name);
	input_tokens.push_back(parameter_name_1);
	input_tokens.push_back(parameter_name_2);
	CallbackTester ct;

	EXPECT_CALL(pa_1, IsInExpectedDomainMock(parameter_name_1)).WillOnce(Return(true));
	EXPECT_CALL(pa_2, IsInExpectedDomainMock(parameter_name_2)).WillOnce(Return(false));

	auto const return_val = cmd.Evaluate(input_tokens);

	EXPECT_EQ(false, std::get<0>(return_val));
	EXPECT_EQ(1, std::get<1>(return_val));
	EXPECT_STREQ("", std::get<2>(return_val).c_str());
	EXPECT_EQ(false, cbt.WasCallbackCalled());
}

TEST(CommandTests, Evaluate_2Param2RightTokens1ExtraToken_CallbackCalledFalse3CorrectString)
{
	static string const method_name("sig1");
	static string const parameter_name_1("param_1");
	static string const parameter_name_2("param_2");
	CallbackTesterWithParams<int32_t, int32_t> cbt;
	ConcreteParameterMock<int32_t> pa_1(parameter_name_1);
	ConcreteParameterMock<int32_t> pa_2(parameter_name_2);
	ParameterAbstractWrapper<ConcreteParameterMock<int32_t> > paw_1(&pa_1);
	ParameterAbstractWrapper<ConcreteParameterMock<int32_t> > paw_2(&pa_2);
	CommandWithParams<ParameterAbstractWrapper<ConcreteParameterMock<int32_t> >,
		ParameterAbstractWrapper<ConcreteParameterMock<int32_t> > > cmd({ method_name }, "description",
			cbt.GetCallback(), paw_1,
			paw_2);
	vector<string> input_tokens;
	input_tokens.push_back(method_name);
	input_tokens.push_back(parameter_name_1);
	input_tokens.push_back(parameter_name_2);
	input_tokens.push_back("extra_token");
	CallbackTester ct;

	EXPECT_CALL(pa_1, IsInExpectedDomainMock(parameter_name_1)).WillOnce(Return(true));
	EXPECT_CALL(pa_2, IsInExpectedDomainMock(parameter_name_2)).WillOnce(Return(true));

	auto const return_val = cmd.Evaluate(input_tokens);

	EXPECT_EQ(false, std::get<0>(return_val));
	EXPECT_EQ(2, std::get<1>(return_val));
	EXPECT_STREQ("", std::get<2>(return_val).c_str());
	EXPECT_EQ(false, cbt.WasCallbackCalled());
}

TEST(CommandTests, Evaluate_2ParamRightTokens_CallbackCalledTrue2CorrectString)
{
	static string const method_name("sig1");
	static string const parameter_name_1("param_1");
	static string const parameter_name_2("param_2");
	CallbackTesterWithParams<int32_t, int32_t> cbt;
	ConcreteParameterMock<int32_t> pa_1(parameter_name_1);
	ConcreteParameterMock<int32_t> pa_2(parameter_name_2);
	ParameterAbstractWrapper<ConcreteParameterMock<int32_t> > paw_1(&pa_1);
	ParameterAbstractWrapper<ConcreteParameterMock<int32_t> > paw_2(&pa_2);
	CommandWithParams<ParameterAbstractWrapper<ConcreteParameterMock<int32_t> >,
	                  ParameterAbstractWrapper<ConcreteParameterMock<int32_t> > > cmd({method_name}, "description",
	                                                                                  cbt.GetCallback(), paw_1,
	                                                                                  paw_2);
	vector<string> input_tokens;
	input_tokens.push_back(method_name);
	input_tokens.push_back(parameter_name_1);
	input_tokens.push_back(parameter_name_2);
	CallbackTester ct;

	EXPECT_CALL(pa_1, IsInExpectedDomainMock(parameter_name_1)).WillOnce(Return(true));
	EXPECT_CALL(pa_1, GetValue(parameter_name_1)).WillOnce(Return(32));
	EXPECT_CALL(pa_2, IsInExpectedDomainMock(parameter_name_2)).WillOnce(Return(true));
	EXPECT_CALL(pa_2, GetValue(parameter_name_2)).WillOnce(Return(32));

	auto const return_val = cmd.Evaluate(input_tokens);

	EXPECT_EQ(true, std::get<0>(return_val));
	EXPECT_EQ(2, std::get<1>(return_val));
	EXPECT_STREQ("received command \"sig1 param_1 param_2\"", std::get<2>(return_val).c_str());
	EXPECT_EQ(true, cbt.WasCallbackCalled());
}
