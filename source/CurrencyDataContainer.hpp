#pragma once

#include "CurrencyData.hpp"

namespace cbr
{

using CurrencyDataContainer = std::map<boost::gregorian::date, CurrencyDataSPtr>;
using CurrencyDataContainerSPtr = std::shared_ptr<CurrencyDataContainer>;

} // ns cbr
