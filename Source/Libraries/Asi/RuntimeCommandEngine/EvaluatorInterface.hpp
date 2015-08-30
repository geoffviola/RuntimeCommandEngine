#ifndef _ASI_RUNTIMECOMMANDENGINE_EVALUATORINTERFACE_HPP_
#define _ASI_RUNTIMECOMMANDENGINE_EVALUATORINTERFACE_HPP_

#include <string>
#include <vector>

namespace asi {
namespace runtimecommandengine {

class EvaluatorInterface
{
public:
	virtual bool Evaluate(std::vector<std::string> const& tokens, std::string *data_to_print, bool *exit_received)
	{
		return EvaluateImpl(tokens, data_to_print, exit_received);
	}

protected:
	virtual bool EvaluateImpl(std::vector<std::string> const& tokens, std::string *data_to_print, 
		bool *exit_received) = 0;
};

} // namespace runtimecommandengine
} // namespace asi

#endif //_ASI_RUNTIMECOMMANDENGINE_EVALUATORINTERFACE_HPP_
