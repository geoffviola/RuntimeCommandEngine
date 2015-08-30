#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "Asi/RuntimeCommandEngine/Tree.hpp"

class TreeTests : public testing::Test
{
	void SetUp() override {}
	void TearDown() override {}
};

using std::vector;
using std::string;
using asi::runtimecommandengine::CallbackMetadata;
using asi::runtimecommandengine::Tree;
using testing::Return;

class CommandMock : public asi::runtimecommandengine::CommandInterface
{
public:
	MOCK_CONST_METHOD1(EvaluateImpl, std::tuple<bool, uint32_t, std::string>(std::vector<std::string> const &));
	MOCK_CONST_METHOD0(GetMethodNameImpl, std::vector<std::string>(void));
	MOCK_CONST_METHOD0(GetHelpImpl, std::string(void));
	MOCK_CONST_METHOD0(GetSignatureLengthImpl, size_t(void));
	MOCK_METHOD1(PrependSignatureImpl, void(std::string const &));
	MOCK_CONST_METHOD1(GetSignatureExpectationImpl, std::vector<std::string>(size_t));
};

TEST_F(TreeTests, Evaluate_NoCommandsNoTokens_ReturnFalse)
{
	static std::vector<asi::runtimecommandengine::CommandInterface *> const empty_cmds;
	Tree t(empty_cmds);
	vector<string> tokens;

	auto const result = t.Evaluate(tokens);

	EXPECT_EQ(false, std::get<0>(result));
	EXPECT_STREQ("No tokens received. Interpreter is empty", std::get<1>(result).c_str());
}

TEST_F(TreeTests, Evaluate_NoCommandsOneToken_ReturnFalse)
{
	static std::vector<asi::runtimecommandengine::CommandInterface *> const empty_cmds;
	Tree t(empty_cmds);
	vector<string> tokens;
	tokens.push_back("one");

	auto const result = t.Evaluate(tokens);

	EXPECT_EQ(false, std::get<0>(result));
	EXPECT_STREQ("Unknown token \"one\". Interpreter is empty", std::get<1>(result).c_str());
}

TEST_F(TreeTests, Evaluate_OneCommandNoTokens_ReturnFalse)
{
	static vector<string> const tokens;
	CommandMock cmd;
	Tree t({&cmd});

	static std::tuple<bool, uint32_t, std::string> const cmd_return_val(false, 0, "");
	EXPECT_CALL(cmd, EvaluateImpl(tokens)).WillOnce(testing::Return(cmd_return_val));
	EXPECT_CALL(cmd, GetSignatureLengthImpl()).WillRepeatedly(testing::Return(0));

	auto const result = t.Evaluate(tokens);

	EXPECT_EQ(false, std::get<0>(result));
	EXPECT_STREQ("No tokens received", std::get<1>(result).c_str());
}

TEST_F(TreeTests, Evaluate_OneCommandOneNonMatchingToken_ReturnFalse)
{
	vector<string> tokens;
	tokens.push_back("one");
	CommandMock cmd;
	Tree t({&cmd});

	static std::tuple<bool, uint32_t, std::string> const cmd_return_val(false, 0, "");
	EXPECT_CALL(cmd, EvaluateImpl(tokens)).WillOnce(testing::Return(cmd_return_val));
	EXPECT_CALL(cmd, GetSignatureLengthImpl()).WillRepeatedly(testing::Return(1));
	static std::vector<std::string> const cmd_sig_exp{"a"};
	EXPECT_CALL(cmd, GetSignatureExpectationImpl(std::get<1>(cmd_return_val)))
	    .WillOnce(testing::Return(cmd_sig_exp));

	auto const result = t.Evaluate(tokens);

	EXPECT_EQ(false, std::get<0>(result));
	EXPECT_STREQ("Unknown token \"one\". expected: a", std::get<1>(result).c_str());
}

TEST_F(TreeTests, Evaluate_OneCommandOneMatchingToken_ReturnTrue)
{
	vector<string> tokens;
	static string const token("one");
	tokens.push_back(token);
	CommandMock cmd;
	Tree t({&cmd});

	static std::tuple<bool, uint32_t, std::string> const cmd_return_val(true, 0, "");
	EXPECT_CALL(cmd, EvaluateImpl(tokens)).WillOnce(testing::Return(cmd_return_val));

	auto const result = t.Evaluate(tokens);

	EXPECT_EQ(true, std::get<0>(result));
}

TEST_F(TreeTests, Evaluate_OneCommandOneMatchingTokenButNeedsTwo_ReturnFalse)
{
	vector<string> tokens;
	tokens.push_back("one");
	CommandMock cmd;
	Tree t({&cmd});

	static std::tuple<bool, uint32_t, std::string> const cmd_return_val(false, 1, "");
	EXPECT_CALL(cmd, EvaluateImpl(tokens)).WillOnce(testing::Return(cmd_return_val));
	EXPECT_CALL(cmd, GetSignatureLengthImpl()).WillRepeatedly(testing::Return(2));
	static std::vector<std::string> const cmd_sig_exp{"two"};
	EXPECT_CALL(cmd, GetSignatureExpectationImpl(std::get<1>(cmd_return_val)))
	    .WillOnce(testing::Return(cmd_sig_exp));

	auto const result = t.Evaluate(tokens);

	EXPECT_EQ(false, std::get<0>(result));
	EXPECT_STREQ("Expected next token: two", std::get<1>(result).c_str());
}

TEST_F(TreeTests, Evaluate_OneCommandOneMatchingTokenOneExtraToken_ReturnFalse)
{
	vector<string> tokens;
	tokens.push_back("one");
	tokens.push_back("two");
	CommandMock cmd;
	Tree t({&cmd});

	static std::tuple<bool, uint32_t, std::string> const cmd_return_val(false, 0, "");
	EXPECT_CALL(cmd, EvaluateImpl(tokens)).WillOnce(testing::Return(cmd_return_val));
	EXPECT_CALL(cmd, GetSignatureLengthImpl()).WillRepeatedly(testing::Return(1));
	static std::vector<std::string> const cmd_sig_exp{"one"};
	EXPECT_CALL(cmd, GetSignatureExpectationImpl(std::get<1>(cmd_return_val)))
	    .WillOnce(testing::Return(cmd_sig_exp));

	auto const result = t.Evaluate(tokens);

	EXPECT_EQ(false, std::get<0>(result));
	EXPECT_STREQ("Unknown extra token \"two\"", std::get<1>(result).c_str());
}

TEST_F(TreeTests, Evaluate_TwoCommandsOneMatchingToken_ReturnTrue)
{
	vector<string> tokens;
	tokens.push_back("one");
	CommandMock cmd1;
	CommandMock cmd2;
	Tree t({&cmd1, &cmd2});

	static std::tuple<bool, uint32_t, std::string> const cmd1_return_val(true, 0, "");
	EXPECT_CALL(cmd1, EvaluateImpl(tokens)).WillOnce(testing::Return(cmd1_return_val));
	static std::tuple<bool, uint32_t, std::string> const cmd2_return_val(false, 0, "");
	EXPECT_CALL(cmd2, EvaluateImpl(tokens)).WillOnce(testing::Return(cmd2_return_val));

	auto const result = t.Evaluate(tokens);

	EXPECT_EQ(true, std::get<0>(result));
}
