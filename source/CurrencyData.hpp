#pragma once

#include <string>
#include <memory>

namespace cbr
{

struct CurrencyData
{
    CurrencyData(const char * date, const char * nominal, const char * value);

public:
    std::string date;
    uint16_t nominal;
    double value;
};

using CurrencyDataSPtr = std::shared_ptr<CurrencyData>;

} //ns cbr
