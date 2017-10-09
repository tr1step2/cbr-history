#include "stdafx.h"

#include "CurrencyData.hpp"

cbr::CurrencyData::CurrencyData(const char * date,
                                const char * nominal,
                                const char * value)
    : date(boost::gregorian::from_uk_string(date))
    , nominal(boost::lexical_cast<uint16_t>(nominal))
    , value(boost::lexical_cast<double>(value))
{
}
