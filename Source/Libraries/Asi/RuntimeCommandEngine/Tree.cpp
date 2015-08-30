#include "Tree.hpp"
#include <algorithm>
#include <functional>
#include "StringUtils.hpp"

namespace asi
{
namespace runtimecommandengine
{

Tree::Tree(std::vector<CommandInterface*> const &in_commands)
    : commands(in_commands)
{
}

Tree::~Tree() {}

void Tree::AddCommands(Tree const &other_tree)
{
	for (auto command : other_tree.commands)
	{
		this->commands.push_back(command);
	}
}

void Tree::Clear() { commands.clear(); }

void Tree::PrependAllCommandSignatures(std::string const &signature)
{
	auto prepend_fun = [&signature](CommandInterface *command)
	{
		command->PrependSignature(signature);
	};
	std::for_each(commands.begin(), commands.end(), prepend_fun);
}

void Tree::PrependCmdSign(std::vector<std::string> const &signature, std::string const &prepend)
{
	auto cmd_sig_eq = [&signature](CommandInterface const *command)
	{
		return command->GetMethodName() == signature;
	};
	auto cmd_it = std::find_if(commands.begin(), commands.end(), cmd_sig_eq);
	(*cmd_it)->PrependSignature(prepend);
}

std::tuple<bool, std::string> Tree::Evaluate(std::vector<std::string> const &tokens) const
{
	std::tuple<bool, std::string> output(false, "");
	std::vector<CommandInterface*> closest_commands;
	int32_t highest_index = 0;
	for (uint32_t i = 0; i < commands.size(); i++)
	{
		std::tuple<bool, uint32_t, std::string> command_return = commands[i]->Evaluate(tokens);
		if (std::get<0>(command_return))
		{
			std::get<0>(output) = true;
		}
		else
		{
			int32_t const command_index = std::get<1>(command_return);
			if (command_index > highest_index)
			{
				closest_commands.clear();
				highest_index = command_index;
			}
			if (command_index == highest_index)
			{
				closest_commands.push_back(commands[i]);
			}
		}
	}

	if (false == std::get<0>(output))
	{
		std::get<1>(output) = HandleErrors(tokens, closest_commands, highest_index);
	}

	return output;
}

std::string Tree::GetHelp() const
{
	std::string output;
	output += "Commands (" + std::to_string(commands.size()) + "):";
	std::string command_string;
	for (auto command : commands)
	{
		command_string += "\n" + command->GetHelp();
	}
	output += replaceSubstringWithSubstring(command_string, "\n", "\n\t");
	output += "\nFormat: signature_0 signature_1... signature_n [parameter_0 parameter_1.. parameter_n]";
	return output;
}

std::string Tree::HandleErrors(std::vector<std::string> const &tokens, std::vector<CommandInterface*> const &closest_commands,
                               int32_t const highest_index) const
{
	std::vector<std::string> item_names;
	std::string item_names_serialized;
	for (uint32_t i = 0; i < closest_commands.size() && closest_commands.size(); ++i)
	{
		if (static_cast<size_t>(highest_index) < closest_commands[i]->GetSignatureLength())
		{
			std::vector<std::string> expectedTokens =
			    closest_commands[i]->GetSignatureExpectation(highest_index);
			for (auto expectedToken : expectedTokens)
			{
				bool string_is_new =
				    !std::any_of(item_names.begin(), item_names.end(),
				                 std::bind(&iequals, expectedToken, std::placeholders::_1));
				if (string_is_new)
				{
					if (item_names.size() > 0)
					{
						item_names_serialized += ", ";
					}
					item_names_serialized += expectedToken;
					item_names.push_back(expectedToken);
				}
			}
		}
	}

	return GetErrorDescription(tokens, closest_commands, highest_index, item_names_serialized);
}

std::string Tree::GetErrorDescription(std::vector<std::string> const &tokens,
                                      std::vector<CommandInterface*> const &closest_commands, int32_t const highest_index,
                                      std::string const &item_names_serialized) const
{
	std::string output;
	if (0 == closest_commands.size())
	{
		if (0 == tokens.size())
		{
			output = "No tokens received. Interpreter is empty";
		}
		else
		{
			output = "Unknown token \"" + tokens[highest_index] + "\". Interpreter is empty";
		}
	}
	else if (0 == tokens.size())
	{
		output = "No tokens received";
	}
	else if (tokens.size() > closest_commands[0]->GetSignatureLength())
	{
		output = "Unknown extra token \"" + tokens[closest_commands[0]->GetSignatureLength()] + "\"";
	}
	else if (tokens.size() != static_cast<size_t>(highest_index))
	{
		output = "Unknown token \"" + tokens[highest_index] + "\". expected: " + item_names_serialized;
	}
	else
	{
		output = std::string("Expected") + ((tokens.size() != 0) ? " next token" : "") + ": " +
		         item_names_serialized;
	}
	return output;
}

} // namespace runtimecommandengine
} // namespace asi
