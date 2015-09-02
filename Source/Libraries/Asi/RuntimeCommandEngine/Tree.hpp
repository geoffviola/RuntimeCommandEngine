#ifndef ASI_RUNTIMECOMMANDENGINE_TREE_HPP
#define ASI_RUNTIMECOMMANDENGINE_TREE_HPP

#include <vector>
#include "CommandInterface.hpp"
#include <cstdint>

namespace asi
{
namespace runtimecommandengine
{

class CallbackMetadata;

/// A Collection of commands
class Tree
{
public:
	explicit Tree(std::vector<CommandInterface *> const &in_commands);
	virtual ~Tree();

	void AddCommands(Tree const &other_tree);
	void Clear();
	void PrependAllCommandSignatures(std::string const &signature);
	/**
	        Prepend a command identified with its signature with another string.
	        Fails when the element is not found.
	*/
	void PrependCmdSign(std::vector<std::string> const &signature, std::string const &prepend);
	/**
	        @return bool evaluation success
	                string error description
	*/
	std::tuple<bool, std::string> Evaluate(std::vector<std::string> const &tokens) const;
	std::string GetHelp() const;

private:
	/// @return Error description
	std::string HandleErrors(std::vector<std::string> const &tokens,
	                         std::vector<CommandInterface *> const &closest_commands,
	                         int32_t const highest_index) const;
	std::string GetErrorDescription(std::vector<std::string> const &tokens,
	                                std::vector<CommandInterface *> const &closest_commands,
	                                size_t const next_index, std::string const &item_names_serialized) const;

	std::vector<CommandInterface *> commands;
};

} // namespace runtimecommandengine
} // namespace asi

#endif // ASI_RUNTIMECOMMANDENGINE_TREE_HPP
