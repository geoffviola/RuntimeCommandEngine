/**
        More complex example to illustrate use at runtime and the ability to compose commands
*/

#include <stdlib.h>
#include <vector>
#include <string>

#include "Asi/RuntimeCommandEngine/Tree.hpp"
#include "Asi/RuntimeCommandEngine/MakeCommand.hpp"
#include "Asi/RuntimeCommandEngine/Parameter/Range.hpp"
#include "Asi/SimpleMathCmdTree/Tree.hpp"

using asi::runtimecommandengine::parameter::Range;
using asi::runtimecommandengine::MakeCommand;
using asi::runtimecommandengine::CommandInterface;
using asi::runtimecommandengine::Tree;
using std::string;

void exit_program(bool *exit);
void help(Tree const *const tree);

void exit_program(bool *const exit) { *exit = true; }
void help(Tree const *const tree) { printf("%s\n", tree->GetHelp().c_str()); }

int main(int argc, char *args[])
{
	auto simple_math_cmd_tree = asi::simplemathcmdtree::GetTree();
	simple_math_cmd_tree.PrependAllCommandSignatures("math");

	std::vector<std::string> const help_sig{"help"};
	Tree *tree_ptr = nullptr;
	auto help_cmd(MakeCommand(help_sig, "print help information", std::bind(&help, std::ref(tree_ptr))));
	bool exit_received = false;
	std::vector<std::string> const exit_sig{ "exit" };
	auto exit_cmd(MakeCommand(exit_sig, "exit the program", std::bind(&exit_program, &exit_received)));

	std::vector<CommandInterface *> cmds{&help_cmd, &exit_cmd};
	Tree tree(cmds);
	tree.AddCommands(simple_math_cmd_tree);
	tree_ptr = &tree;

	while (!exit_received)
	{
		string raw_input;
		std::getline(std::cin, raw_input);
		std::istringstream iss(raw_input);
		std::vector<string> tokens{ std::istream_iterator<string>{iss},
			std::istream_iterator<string>{} };
		auto const eval_result = tree.Evaluate(tokens);
		if (!std::get<0>(eval_result))
		{
			printf("%s\n", std::get<1>(eval_result).c_str());
		}
	}

	return EXIT_SUCCESS;
}
