#ifndef _ASI_RUNTIMECOMMANDENGINE_COMMANDWITHOUTPARAMS_HPP_
#define _ASI_RUNTIMECOMMANDENGINE_COMMANDWITHOUTPARAMS_HPP_

#include <functional>
#include <string>
#include <vector>
#include "CommandInterface.hpp"

namespace asi
{
namespace runtimecommandengine
{

class CommandWithoutParams : public CommandInterface
{
public:
	typedef std::function<void(std::vector<std::string> const &)> CallFunType;

	CommandWithoutParams(std::vector<std::string> const &in_signature, std::string const &in_description,
	               CallFunType call_fun);
	
	/**
		@return bool are the tokens in the signature
		        uint32_t the index that was matched to
	*/
	std::tuple<bool, uint32_t> AreTokensInSignature(std::vector<std::string> tokens) const;
	inline void CallFun(std::vector<std::string> const &tokens) const { callFun(tokens); }

private:
	std::tuple<bool, uint32_t, std::string> EvaluateImpl(std::vector<std::string> const &tokens) const override;
	std::vector<std::string> GetSignatureExpectationImpl(size_t const index) const override;
	size_t GetSignatureLengthImpl() const override { return methodNameTokens.size(); }
	std::vector<std::string> GetMethodNameImpl() const override { return methodNameTokens; }
	void PrependSignatureImpl(std::string const &pre_sig) override;
	std::string GetHelpImpl() const override;

	void SelfCheck();

	std::vector<std::string> methodNameTokens;
	std::string const description;
	CallFunType const callFun;
};

} // namespace runtimecommandengine
} // namespace asi

#endif //_ASI_RUNTIMECOMMANDENGINE_COMMANDWITHOUTPARAMS_HPP_
