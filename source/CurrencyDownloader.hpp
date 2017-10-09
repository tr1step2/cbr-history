#pragma once

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
    void download_file(const char * host, const char * url_path, const char * out_file_name);

private:
	void DEBUG_FILE(boost::asio::ip::tcp::socket & socket, boost::asio::streambuf & response);
	void check_response_status(boost::asio::streambuf & response);
};

} // ns cbr
