#include "Tree.hpp"
#include "Asi/SimpleMath/SimpleMath.hpp"
#include "Asi/RuntimeCommandEngine/Parameter/Range.hpp"
#include "Asi/RuntimeCommandEngine/MakeCommand.hpp"

using asi::runtimecommandengine::parameter::Range;
using asi::runtimecommandengine::MakeCommand;
using std::placeholders::_1;
using std::placeholders::_2;
using std::bind;

namespace asi
{
namespace simplemathcmdtree
{

asi::runtimecommandengine::Tree GetTree()
{
	Range<double> add_left_value("left value", -100.0, 100.0);
	Range<double> add_right_value("right value", -100.0, 100.0);
	std::vector<std::string> const add_sig{"add"};
	static auto add_cmd(MakeCommand(add_sig, "add the left to the right",
	                                bind(&printf, "%f\n", bind(&simplemath::Add, _1, _2)), add_left_value,
	                                add_right_value));

	Range<double> sub_left_value("left value", -100.0, 100.0);
	Range<double> sub_right_value("right value", -100.0, 100.0);
	std::vector<std::string> const sub_sig{"subtract"};
	static auto sub_cmd(MakeCommand(sub_sig, "subtract the left form the right",
	                                bind(&printf, "%f\n", bind(&simplemath::Subtract, _1, _2)), sub_left_value,
	                                sub_right_value));

	Range<double> mult_left_value("left value", -100.0, 100.0);
	Range<double> mult_right_value("right value", -100.0, 100.0);
	std::vector<std::string> const mult_sig{"multiply"};
	static auto mult_cmd(MakeCommand(mult_sig, "multiply the left and the right",
	                                 bind(&printf, "%f\n", bind(&simplemath::Multiply, _1, _2)), mult_left_value,
	                                 mult_right_value));

	Range<double> div_left_value("left value", -100.0, 100.0);
	Range<double> div_right_value("right value", 0.001, 100.0);
	std::vector<std::string> const div_sig{"divide"};
	static auto div_cmd(MakeCommand(div_sig, "divide the left from the right",
	                                bind(&printf, "%f\n", bind(&simplemath::Divide, _1, _2)), div_left_value,
	                                div_right_value));

	std::vector<asi::runtimecommandengine::CommandInterface *> cmds{&add_cmd, &sub_cmd, &mult_cmd, &div_cmd};
	asi::runtimecommandengine::Tree output(cmds);
	return output;
}

} // namespace simplemathcmdtree
} // namespace asi
