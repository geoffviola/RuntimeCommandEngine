#ifndef ASI_RUNTIMECOMMANDENGINE_COMMANDINTERFACE_HPP
#define ASI_RUNTIMECOMMANDENGINE_COMMANDINTERFACE_HPP

#include <cstdint>
#include <string>
#include <vector>
#include <tuple>

namespace asi
{
namespace runtimecommandengine
{

class CommandInterface
{
public:
	CommandInterface(CommandInterface const &) = default;
	virtual ~CommandInterface() {}

	/**
	@return the bool can be used to determine if any token was properly evaluated
	if any token evaluated, the uint32_t is the last good parameter
	the std::string is for printing
	*/
	inline std::tuple<bool, int32_t, std::string> Evaluate(std::vector<std::string> const &tokens) const
	{
		return this->EvaluateImpl(tokens);
	}
	inline std::vector<std::string> GetMethodName() const { return this->GetMethodNameImpl(); }
	inline std::string GetHelp() const { return this->GetHelpImpl(); }
	inline size_t GetSignatureLength() const { return this->GetSignatureLengthImpl(); }
	inline void PrependSignature(std::string const &pre_sig) { this->PrependSignatureImpl(pre_sig); }
	/// Get the method name or parameter name based on a common index
	inline std::vector<std::string> GetSignatureExpectation(size_t const index) const
	{
		return this->GetSignatureExpectationImpl(index);
	}

protected:
	CommandInterface() {}

	virtual std::tuple<bool, int32_t, std::string> EvaluateImpl(std::vector<std::string> const &tokens) const = 0;
	virtual std::vector<std::string> GetMethodNameImpl() const = 0;
	virtual std::string GetHelpImpl() const = 0;
	virtual size_t GetSignatureLengthImpl() const = 0;
	virtual void PrependSignatureImpl(std::string const &pre_sig) = 0;
	virtual std::vector<std::string> GetSignatureExpectationImpl(size_t const index) const = 0;

	static inline std::string GetReceivedMessage(std::vector<std::string> tokens)
	{
		std::string output;
		for (auto token : tokens)
		{
			if (output.size() > 0)
			{
				output += " ";
			}
			output += token;
		}
		output = "received command \"" + output + "\"";
		return output;
	}
};

} // namespace runtimecommandengine
} // namespace asi

#endif // ASI_RUNTIMECOMMANDENGINE_COMMANDINTERFACE_HPP
