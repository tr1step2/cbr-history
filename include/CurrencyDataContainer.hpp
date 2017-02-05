#pragma once

#include <memory>
#include <map>

#include "CurrencyData.hpp"

namespace cbr
{

using CurrencyDataContainer = std::map<std::string, CurrencyDataSPtr>;
using CurrencyDataContainerSPtr = std::shared_ptr<CurrencyDataContainer>;

} // ns cbr
