#include <boost/lexical_cast.hpp>

#include "CurrencyData.hpp"

cbr::CurrencyData::CurrencyData(const char * date,
                                const char * nominal,
                                const char * value)
    : date(date)
    , nominal(boost::lexical_cast<uint16_t>(nominal))
    , value(boost::lexical_cast<double>(value))
{
}
