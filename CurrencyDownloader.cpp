#include <ofstream>
#include <curl/curl.h>

#include "CurrencyDownloader.hpp"

void cbr::CurrencyDownloader::download_file(const char * url, const char * out_file_name)
{
    CURL *chandle = curl_easy_init();
    if (!chandle)
        throw std::runtime_error("Can't init curl instance");

    curl_easy_setopt(chandle, CURLOPT_URL, url);
    curl_easy_setopt(chandle, CURLOPT_WRITEFUNCTION, callback_bin_data);
    curl_easy_setopt(chandle, CURLOPT_WRITEDATA, filename);

    CURLcode res = curl_easy_perform(chandle);
    if (CURLE_OK != res)
        throw std::runtime_error("Some errors caught due http request.");

    curl_easy_cleanup(chandle);
}

void cbr::CurrencyDownloader::callback_bin_data(char * ptr, size_t size,
                                                size_t nmemb, const void * filename)
{
    //check is it first call of callback for this file
    static thread_local std::set<const char *> first_time_files;
    auto iter = first_time_files.find((const char *)filename);
    bool first_time = first_time_files.end() == iter;

    //truncate old file if first time
    //append to old file if not
    auto open_mode = first_time ? std::ofstream::trunc : std::ofstream::app;
    open_mode |= std::ofstream::bin;

    first_time_files.insert((const char *)filename);

    std::ofstream file_out(static_cast<const char *>(filename), open_mode);
    if (file_out)
        file_out.write(ptr, nmemb * size);

    return size * nmemb;
}
