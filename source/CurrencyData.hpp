#pragma once

#include <string>
#include <memory>
#include <cstdint>

#include <boost/date_time.hpp>

namespace cbr
{

struct CurrencyData
{
    CurrencyData(const char * date, const char * nominal, const char * value);

public:
    boost::gregorian::date date;
    uint16_t nominal;
    double value;
};

using CurrencyDataSPtr = std::shared_ptr<CurrencyData>;

} //ns cbr
