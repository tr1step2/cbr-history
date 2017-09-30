#pragma once

#include <fstream>

namespace cbr
{
/**
 * @brief The CurrencyDownloader struct
 */
struct CurrencyDownloader
{
    /**
     * @brief download_file
     * @param url
     * @param out_file_name
     */
    void download_file(const char * url, const char * out_file_name);

    ~CurrencyDownloader();

private:
    static size_t callback_bin_data(char * ptr, size_t size, size_t nmemb,
                                    const void * out_file_name);
};

} // ns cbr
