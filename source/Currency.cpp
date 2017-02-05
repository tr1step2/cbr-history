#include <boost/lexical_cast.hpp>

#include "Currency.hpp"

cbr::Currency::Currency(const char * id, const char * num_code, const char * char_code,
       const char * name)
    : id(id)
    , num_code(boost::lexical_cast<uint16_t>(num_code))
    , char_code(char_code)
    , name(name)
{
}
