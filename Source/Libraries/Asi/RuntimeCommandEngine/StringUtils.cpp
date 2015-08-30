#include "StringUtils.hpp"
#define _USE_MATH_DEFINES
#include <math.h>
#include <sstream>

namespace asi
{
namespace runtimecommandengine
{

bool iequals(std::string const &s1, std::string const &s2)
{
	return (s1.size() == s2.size()) && equal(s1.begin(), s1.end(), s2.begin(), [](char const x, char const y)
	                                         {
		                                         return tolower(x) == tolower(y);
		                                 });
}

std::string replaceSubstringWithSubstring(std::string const &base, std::string const &replacee,
                                          std::string const &replacer)
{
	std::string output(base);

	size_t index = 0;
	for (;;)
	{
		/* Locate the substring to replace. */
		index = output.find(replacee, index);
		if (index == std::string::npos)
		{
			break;
		}

		/* Make the replacement. */
		output.replace(index, replacee.size(), replacer);

		/* Advance index forward so the next iteration
		doesn't pick it up as well. */
		index += replacer.size();
	}

	return output;
}

std::string prettyPrint(double const value)
{
	std::stringstream ss;
	ss.precision(1);
	if ((0.00001 < value || -0.00001 > value) && std::fmod(4 * (abs(value) / M_PI), 1.0) < 0.00000001)
	{
		ss << std::fixed;
		if (abs(abs(value) - M_PI) > 0.00000001)
		{
			ss << (value) / M_PI << "*";
		}
		else if (value < 0)
		{
			ss << "-";
		}
		ss << "pi";
	}
	else if (abs(value) >= 1000 || std::numeric_limits<double>::min() == value)
	{
		ss << std::scientific;
		ss << value;
	}
	else
	{
		ss << std::fixed;
		ss << value;
	}
	return ss.str();
}

bool isInteger(std::string const &s)
{
	bool output = true;
	for (auto c : s)
	{
		if (!(c >= '0' && c <= '9') && c != '-')
		{
			output = false;
		}
	}
	return output;
}

bool isDouble(std::string const &s)
{
	bool output = true;
	for (auto c : s)
	{
		if (!(c >= '0' && c <= '9') && c != '.' && c != '-')
		{
			output = false;
		}
	}
	return output;
}

} // namespace runtimecommandengine
} // namespace asi
