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

using CurrencyDataContainerSPtr = std::shared_ptr<CurrencyDataContainer>;
} // ns cbr
