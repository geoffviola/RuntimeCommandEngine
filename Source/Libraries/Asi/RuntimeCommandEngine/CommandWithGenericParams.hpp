#ifndef ASI_RUNTIMECOMMANDENGINE_COMMANDWITHGENERICPARAMS_HPP
#define ASI_RUNTIMECOMMANDENGINE_COMMANDWITHGENERICPARAMS_HPP

#include <functional>
#include <string>
#include <vector>
#include "Parameter/ParameterAbstract.hpp"
#include "CommandInterface.hpp"
#include "CommandWithoutParams.hpp"

namespace asi
{
namespace runtimecommandengine
{

class CommandWithGenericParams : public CommandInterface
{
public:
	typedef std::function<void(std::vector<std::string> const &)> CallFunType;

	CommandWithGenericParams(std::vector<std::string> const &signature, std::string const &description,
	                         CallFunType call_fun, parameter::ParameterAbstract const *const *in_parameters,
	                         int num_params);

private:
	std::tuple<bool, uint32_t, std::string> EvaluateImpl(std::vector<std::string> const &tokens) const override;
	std::vector<std::string> GetSignatureExpectationImpl(size_t const index) const override;
	size_t GetSignatureLengthImpl() const override;
	std::vector<std::string> GetMethodNameImpl() const override { return commandWithoutParams.GetMethodName(); }
	void PrependSignatureImpl(std::string const &pre_sig) override;
	std::string GetHelpImpl() const override;

	CommandWithoutParams commandWithoutParams;
	std::vector<parameter::ParameterAbstract const *> genericParameters;
};

} // namespace runtimecommandengine
} // namespace asi

#endif // ASI_RUNTIMECOMMANDENGINE_COMMANDWITHGENERICPARAMS_HPP
