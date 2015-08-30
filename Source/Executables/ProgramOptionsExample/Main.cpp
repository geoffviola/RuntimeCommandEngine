#include <stdlib.h>
#include <vector>
#include <string>

#include "Asi/RuntimeCommandEngine/Tree.hpp"
#include "Asi/RuntimeCommandEngine/MakeCommand.hpp"
#include "Asi/RuntimeCommandEngine/Parameter/Range.hpp"

using asi::runtimecommandengine::parameter::Range;
using asi::runtimecommandengine::MakeCommand;
using asi::runtimecommandengine::CommandInterface;
using asi::runtimecommandengine::Tree;

void add(int32_t const a, int32_t const b) { printf("%d + %d = %d\n", a, b, a + b); }
void increment(int32_t const a) { printf("%d + 1 = %d\n", a, a + 1); }
void help(Tree const* const tree) { printf("%s", tree->GetHelp().c_str()); }

int main(int argc, char *args[])
{
	Range<int32_t> add_left_value("left value", -100, 100);
	Range<int32_t> add_right_value("right value", -100, 100);
	std::vector<std::string> const add_sig{ "add" };
	auto add_cmd(MakeCommand(add_sig, "add two numbers", &add, add_left_value, add_right_value));

	Range<int32_t> inc_value("value", -100, 100);
	std::vector<std::string> const inc_sig{ "increment" };
	auto inc_cmd(MakeCommand(inc_sig, "increment a number by one", &increment, inc_value));

	std::vector<std::string> const help_sig{ "help" };
	Tree* tree_ptr = nullptr;
	auto help_cmd(MakeCommand(help_sig, "print help information", std::bind(&help, std::ref(tree_ptr))));

	std::vector<CommandInterface *> cmds{ &add_cmd, &inc_cmd, &help_cmd };
	Tree tree(cmds);
	tree_ptr = &tree;

	// Load tokens
	std::vector<std::string> tokens;
	tokens.reserve(argc);
	for (int i = 1; i < argc; ++i)
	{
		tokens.push_back(args[i]);
	}

	tree.Evaluate(tokens);

	return EXIT_SUCCESS;
}
