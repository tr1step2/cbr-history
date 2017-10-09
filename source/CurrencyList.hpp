#pragma once

#include "Currency.hpp"

namespace cbr
{

using CurrencyList = std::map<std::string, CurrencySPtr>;
using CurrencyListSPtr = std::shared_ptr<CurrencyList>;

} //ns cbr


