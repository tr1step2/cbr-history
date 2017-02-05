#include <boost/algorithm/string/replace.hpp>

#include "HistoryManager.hpp"
#include "CurrencyDataContainer.hpp"
#include "CurrencyList.hpp"
#include "CurrencyDownloader.hpp"
#include "XmlParser.hpp"

cbr::CurrencyDataContainerSPtr cbr::HistoryManager::get_history(const char * char_code,
                                                                const char * start_date,
                                                                const char * end_date,
                                                                const char * out_file_name)
{
    std::string currency_id = get_currency_id(char_code);
    return get_history_impl(currency_id.c_str(), start_date, end_date, out_file_name);
}

std::string cbr::HistoryManager::get_currency_id(const char * char_code)
{
    cbr::CurrencyListSPtr currency_list = download_currency_list();

    const auto iter = currency_list->find(char_code);
    if (iter == currency_list->cend())
        throw std::runtime_error("There is no currency with specified id");

    return iter->second->id;
}

cbr::CurrencyDataContainerSPtr cbr::HistoryManager::get_last_request_data()
{
    return m_last_data;
}

std::string cbr::HistoryManager::prepare_currency_url(const char * currency_id,
                                                      const char * start_date,
                                                      const char * end_date)
{
    //prepare request for getting data for specified period and valute
    std::string request = currency_request_template;
    boost::replace_first(request, "{{start_date}}", start_date);
    boost::replace_first(request, "{{end_date}}", end_date);
    boost::replace_first(request, "{{valute_id}}", currency_id);

    return request;
}

std::string cbr::HistoryManager::prepare_graph_url(const char * currency_id,
                                                   const char * start_date,
                                                   const char * end_date)
{
    //prepare request for getting data for specified period and valute
    std::string request = graph_request_template;
    boost::replace_first(request, "{{start_date}}", start_date);
    boost::replace_first(request, "{{end_date}}", end_date);
    boost::replace_first(request, "{{valute_id}}", currency_id);

    return request;
}

cbr::CurrencyDataContainerSPtr cbr::HistoryManager::get_history_impl(const char * char_code,
    const char * start_date, const char * end_date, const char * out_file_name)
{
    cbr::CurrencyDownloader downloader;

    std::string url = prepare_currency_url(char_code, start_date, end_date);
    downloader.download_file(url.c_str(), out_file_name);

    cbr::XmlParser parser;
    cbr::CurrencyDataContainerSPtr data_container =
            parser.parse_currency_history(out_file_name);

    m_last_data = data_container;
    return data_container;
}

cbr::CurrencyListSPtr cbr::HistoryManager::download_currency_list()
{
    const char * list_file_name = "currency_list.xml";
    cbr::CurrencyDownloader downloader;

    downloader.download_file(currency_list_request_template, list_file_name);

    cbr::XmlParser parser;
    cbr::CurrencyListSPtr currency_list = parser.parse_currency_list(list_file_name);

    return currency_list;
}