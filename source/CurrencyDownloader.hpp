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

private:
    void callback_bin_data(char * ptr, size_t size, size_t nmemb, const void * filename);
};

} // ns cbr
