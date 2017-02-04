#include "CurrencyDataContainer.hpp"

namespace cbr
{

struct XmlParser
{
    CurrencyDataContainerSPtr parse(const char * file_name);
};

} //ns cbr
