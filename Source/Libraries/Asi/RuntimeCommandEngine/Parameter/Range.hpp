#ifndef _ASI_RUNTIMECOMMANDENGINE_PARAMETER_RANGE_HPP_
#define _ASI_RUNTIMECOMMANDENGINE_PARAMETER_RANGE_HPP_

#include "ParameterAbstract.hpp"
#include <string>
#include <sstream>
#include "Asi/RuntimeCommandEngine/StringUtils.hpp"
#include <typeinfo>

namespace asi
{
namespace runtimecommandengine
{
namespace parameter
{

/**
        Defines a range with exclusive parameter ranges
*/
template <class T> class Range : public ParameterAbstract
{
public:
	typedef T ReturnType;

	Range(std::string const &name, T const in_min, T const in_max)
	    : ParameterAbstract(name)
	    , min(in_min)
	    , max(in_max)
	{
	}

	T GetValue(std::string const& raw_value) const { return getStringAs<T>(raw_value); }

	T GetMin() const { return min; }
	T GetMax() const { return max; }

protected:
	virtual char const *GetTypeNameImpl() const override
	{
		static std::string output = std::string("Range<") + std::string(typeid(T).name()) + std::string(">");
		return output.c_str();
	}
	bool IsInExpectedDomainImpl(std::string const &raw_value) const override
	{
		bool output = isStringOfType<T>(raw_value);
		if (output)
		{
			double double_value = getStringAs<T>(raw_value);
			if (double_value < min || double_value > max)
			{
				output = false;
			}
		}
		return output;
	}
	std::string GetExpectedDomainImpl() const override
	{
		std::string output;
		std::stringstream ss;
		ss << "[";
		ss << prettyPrint(min);
		ss << ", ";
		ss << prettyPrint(max);
		ss << "]";
		output = ss.str();
		return output;
	}

private:
	Range &operator=(Range const &tmp);

	T const min;
	T const max;
};

} // namespace parameter
} // namespace runtimecommandengine
} // namespace asi

#endif //_ASI_RUNTIMECOMMANDENGINE_PARAMETER_RANGE_HPP_
