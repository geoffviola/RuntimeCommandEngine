#include "StringUtils.hpp"
#include <sstream>
#include <cmath>
#include <limits>

using std::fmod;
using std::fabs;

namespace asi
{
namespace runtimecommandengine
{

static const double pi = 3.14159265358979323846;

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

	for (size_t index = output.find(replacee, 0U); std::string::npos != index;)
	{
		/* Make the replacement. */
		output.replace(index, replacee.size(), replacer);

		/* Locate the substring to replace. */
		index += replacer.size();
		index = output.find(replacee, index);
	}

	return output;
}

std::string prettyPrint(double const value)
{
	std::stringstream ss;
	ss.precision(1);
	if ((0.00001 < value || -0.00001 > value) && fmod(4 * (fabs(value) / pi), 1.0) < 0.00000001)
	{
		ss << std::fixed;
		if (fabs(fabs(value) - pi) > 0.00000001)
		{
			ss << (value) / pi << "*";
		}
		else if (value < 0)
		{
			ss << "-";
		}
		ss << "pi";
	}
	else if (fabs(value) >= 1000.0)
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
