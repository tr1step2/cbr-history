#include <boost/algorithm/string/replace.hpp>

#include "CbrHistory.hpp"
#include "CurrencyDataContainer.hpp"
#include "CurrencyDownloader.hpp"
#include "XmlParser.hpp"

cbr::CurrencyDataContainerSPtr cbr::HistoryManager::get_history(const char * char_code,
                                                                const char * start_date,
                                                                const char * end_date,
                                                                const char * out_file_name)
{
    cbr::CurrencyDownloader downloader;

    std::string url = prepare_currency_url(char_code, start_date, end_date);
    downloader.download_file(url.c_str(), out_file_name);

    cbr::XmlParser parser;
    cbr::CurrencyDataContainerSPtr data_container = parser.parse(out_file_name);

    m_last_data = data_container;
    return data_container;
}

cbr::CurrencyDataContainerSPtr cbr::HistoryManager::get_last_request_data()
{
    return m_last_data;
}

std::string cbr::HistoryManager::prepare_currency_url(const char *char_code, const char *start_date, const char *end_date)
{
    //prepare request for getting data for specified period and valute
    std::string request = get_valute_request;
    boost::replace_first(request, "{{start_date}}", start_date);
    boost::replace_first(request, "{{end_date}}", end_date);
    boost::replace_first(request, "{{valute_id}}", valute->second.id);

    return request;
}
