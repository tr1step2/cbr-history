#include "stdafx.h"

#include "XmlParser.hpp"
#include "CurrencyDataContainer.hpp"
#include "CurrencyData.hpp"
#include "CurrencyList.hpp"
#include "Currency.hpp"

/* currency xml structure sample
	<ValCurs ID="R01235" DateRange1="01.01.2017" DateRange2="20.09.2017" name="Foreign Currency Market Dynamic">
		<Record Date="10.01.2017" Id="R01235">
			<Nominal>1</Nominal>
			<Value>59,8961</Value>
		</Record>
	</ValCurs>
*/

cbr::CurrencyDataContainerSPtr cbr::XmlParser::parse_currency_history(
	const char * file_name)
{
	boost::property_tree::ptree tree;
	boost::property_tree::read_xml(file_name, tree);

	cbr::CurrencyDataContainerSPtr data_container(new cbr::CurrencyDataContainer);

	for (const auto & record : tree.get_child("ValCurs"))
	{
		std::string str = record.second.data();

		cbr::CurrencyDataSPtr data(new cbr::CurrencyData(record.second.get<std::string>("<xmlattr>.Date").c_str(),
			record.second.get<std::string>("Nominal").c_str(),
			record.second.get<std::string>("Value").c_str()));

		data_container->insert(std::make_pair(data->date, data));
	}

	return data_container;
}

cbr::CurrencyListSPtr cbr::XmlParser::parse_currency_list(const char * file_name)
{
	boost::property_tree::ptree tree;
	boost::property_tree::read_xml(file_name, tree);
	
    cbr::CurrencyListSPtr currency_list(new cbr::CurrencyList);

    for (const auto & rec : tree.get_child("ValCurs"))
    {

        cbr::CurrencySPtr currency(new cbr::Currency(rec.second.get<std::string>("<xmlattr>.ID").c_str(),
                                                     rec.second.get<std::string>("NumCode").c_str(),
													 rec.second.get<std::string>("CharCode").c_str(),
													 rec.second.get<std::string>("Name").c_str()));

        currency_list->insert(std::make_pair(currency->char_code, currency));
    }

    return currency_list;
}
