#include <memory>
#include <map>

#include "Currency.hpp"

namespace cbr
{

struct CurrencyList
{
    std::map<std::string, CurrencySPtr> currency;
};

} //ns cbr

using CurrencyListSPtr = std::shared_ptr<CurrencyList>;
