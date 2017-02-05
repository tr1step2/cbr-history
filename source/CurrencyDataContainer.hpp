#include <memory>
#include <map>

#include "CurrencyData.hpp"

namespace cbr
{

struct CurrencyDataContainer
{
    std::map<std::string, CurrencyDataSPtr> currency_data;
    double min_value;
    double max_value;
};

struct CurrencyList
{
    std::map<std::string, Currency> currency_list;
};

using CurrencyDataContainerSPtr = std::shared_ptr<CurrencyDataContainer>;
using CurrencyListSPtr = std::shared_ptr<CurrencyList>;
} // ns cbr
