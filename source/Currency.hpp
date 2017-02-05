#include <string>
#include <memory>

namespace cbr
{

struct Currency
{
    Currency(const char * id, const char * num_code, const char * char_code,
           const char * name);

    std::string id;
    uint16_t num_code;
    std::string char_code;
    std::string name;
};

using CurrencySPtr = std::shared_ptr<Currency>;

} //ns cbr
