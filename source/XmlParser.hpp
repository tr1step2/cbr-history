#include "CurrencyDataContainer.hpp"
#include "CurrencyList.hpp"

namespace cbr
{

struct XmlParser
{
    CurrencyDataContainerSPtr parse_currency_history(const char * file_name);
    CurrencyListSPtr parse_currency_list(const char * file_name);
};

} //ns cbr
