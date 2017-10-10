#include "stdafx.h"

#include "CurrencyData.hpp"
 
cbr::CurrencyData::CurrencyData(const char * date_,
                                const char * nominal_,
                                const char * value_)
    : date(boost::gregorian::from_uk_string(date_))
    , nominal(boost::lexical_cast<uint16_t>(nominal_))
{
	try
	{
		value = boost::lexical_cast<double>(value_);
	}
	catch (boost::bad_lexical_cast &)
	{
		std::string valueStr = value_;
		boost::replace_all(valueStr, ",", ".");

		value = boost::lexical_cast<double>(valueStr);
	}
}
