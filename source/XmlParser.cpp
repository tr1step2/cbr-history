#include <exception>
#include <stdexcept>

#include <pugixml/pugixml.hpp>
#include <boost/algorithm/string/replace.hpp>

#include "XmlParser.hpp"
#include "CurrencyDataContainer.hpp"
#include "CurrencyData.hpp"
#include "CurrencyList.hpp"
#include "Currency.hpp"

cbr::CurrencyDataContainerSPtr cbr::XmlParser::parse(const char * file_name)
{
    pugi::xml_document doc;
    auto result = doc.load_file(file_name);

    if (!result)
        throw std::runtime_error(result.description());

    cbr::CurrencyDataContainerSPtr data_container(new cbr::CurrencyDataContainer);

    auto valutes = doc.child("ValCurs");
    for(const auto & val : valutes)
    {
        std::string value(val.child("Value").child_value());
        boost::replace_all(value, ",", ".");

        cbr::CurrencyDataSPtr data(new cbr::CurrencyData(val.attribute("Date").value(),
                                                         val.child("Nominal").child_value(),
                                                         value.c_str()));

        data_container->currency_data.insert(std::make_pair(data->date, data));
    }

    return data_container;
}

cbr::CurrencyListSPtr cbr::XmlParser::parse_currency_list(const char * file_name)
{
    pugi::xml_document doc;
    pugi::xml_parse_result res = doc.load_file(filename);

    if (!res)
        throw std::runtime_error(res.description());

    cbr::CurrencyListSPtr currency_list(new cbr::CurrencyList);

    auto valutes = doc.child("ValCurs");
    for (const auto & v : valutes)
    {
        cbr::CurrencySPtr currency(new cbr::Currency(v.attribute("ID").value(),
                                                     v.child("NumCode").child_value(),
                                                     v.child("CharCode").child_value(),
                                                     v.child("Name").child_value()));

        currency_list.currency_list.insert(std::make_pair(currency->char_code, currency));
    }

    return currency_list;
}
