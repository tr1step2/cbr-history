#pragma once

#include <memory>

#include "CurrencyDataContainer.hpp"
#include "CurrencyList.hpp"

extern "C"
{
namespace cbr
{

/**
 * @brief The HistoryManager struct
 */
struct HistoryManager
{
    /**
     * @brief get_history
     * @param char_code
     * @param start_date
     * @param end_date
     * @param out_file_name
     * @return
     */
    CurrencyDataContainerSPtr get_history(const char * char_code,
                                          const char * start_date,
                                          const char * end_date,
                                          const char * out_file_name);
    /**
     * @brief get_last_request_data
     * @return
     */
    CurrencyDataContainerSPtr get_last_request_data();

private:
    std::string get_currency_id(const char * char_code);

    CurrencyDataContainerSPtr get_history_impl(const char * char_code,
                                               const char * start_date,
                                               const char * end_date,
                                               const char * out_file_name);

    std::string prepare_currency_url(const char * currency_id,
                                     const char * start_date,
                                     const char * end_date);

    std::string prepare_graph_url(const char * currency_id,
                                  const char * start_date,
                                  const char * end_date);
    CurrencyListSPtr download_currency_list();

private:

    const char * currency_request_template = "http://cbr.ru/scripts/XML_dynamic.asp?"
            "date_req1={{start_date}}&date_req2={{end_date}}&VAL_NM_RQ={{valute_id}}";
    const char * graph_request_template = "http://www.cbr.ru/currency_base/GrafGen.aspx?"
            "date_req1={{start_date}}&date_req2={{end_date}}&VAL_NM_RQ={{valute_id}}";
    const char * currency_list_request_template = "http://cbr.ru/scripts/XML_daily.asp";

private:
    CurrencyDataContainerSPtr m_last_data;

};

} //ns cbr

} //extern c
