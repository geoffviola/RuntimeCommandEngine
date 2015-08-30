#ifndef ASI_RUNTIMECOMMANDENGINE_STRINGUTILS_HPP
#define ASI_RUNTIMECOMMANDENGINE_STRINGUTILS_HPP

#include <string>
#include <cassert>
#include <sstream>
#include <cstdint>

namespace asi
{
namespace runtimecommandengine
{

/// @return true if the two strings are equal regardless of case
bool iequals(std::string const &s1, std::string const &s2);

/// @return a string with the exact substring replaced with another
std::string replaceSubstringWithSubstring(std::string const &base, std::string const &replacee,
                                          std::string const &replacer);

/// @return string with fewer decimal points or multiples of pi
std::string prettyPrint(double value);

/// @return the best conversion std::stringstream can do
template <class T> inline T getStringAs(std::string const &input)
{
	T output;
	std::stringstream ss(input);
	assert(!ss.eof() && "getStringAs: bad type conversion");
	ss >> output;
	return output;
}

bool isInteger(std::string const &s);

bool isDouble(std::string const &s);

template <class T> inline bool isStringOfType(std::string const &)
{
	throw "isStringIsOfType: unimplemented";
}
template <> inline bool isStringOfType<std::string>(std::string const &) { return true; }
template <> inline bool isStringOfType<uint16_t>(std::string const &input)
{
	bool output = isInteger(input);
	if (output)
	{
		if (input.length() > 5)
		{
			output = false;
		}
		else
		{
			if (getStringAs<uint32_t>(input) > 0xFFFFU)
			{
				output = false;
			}
		}
	}
	return output;
}
template <> inline bool isStringOfType<int32_t>(std::string const &input)
{
	bool output = isInteger(input);
	if (output)
	{
		if (input.length() > 12)
		{
			output = false;
		}
		else
		{
			int64_t input_as_value = getStringAs<int64_t>(input);
			if (input_as_value > 0x7FFFFFFFU || input_as_value < -static_cast<int64_t>(0x80000000U))
			{
				output = false;
			}
		}
	}
	return output;
}

template <> inline bool isStringOfType<double>(std::string const &input) { return isDouble(input); }

} // namespace runtimecommandengine
} // namespace asi

#endif //ASI_RUNTIMECOMMANDENGINE_STRINGUTILS_HPP
