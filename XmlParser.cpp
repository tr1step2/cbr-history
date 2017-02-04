#include <exception>
#include <stdexcept>

#include <pugixml/pugixml.hpp>
#include <boost/algorithm/string/replace.hpp>

#include "XmlParser.hpp"
#include "CurrencyData.hpp"

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
