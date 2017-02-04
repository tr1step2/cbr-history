
extern "C"
{
namespace cbr
{
struct CurrencyDataContainer;

using CurrencyDataContainerSPtr = std::shared_ptr<CurrencyDataContainer>;

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
    std::string prepare_currency_url(const char * char_code,
                                     const char * start_date,
                                     const char * end_date);

private:
    CurrencyDataContainerSPtr m_last_data;



};

} //ns cbr

} //extern c
