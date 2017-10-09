#pragma once

namespace cbr
{
/**
 * @brief The CurrencyDownloader struct
 */
struct CurrencyDownloader
{
	CurrencyDownloader( const char * host );

    /**
     * @brief download_file
     * @param url
     * @param out_file_name
     */
    void download_file(const char * url_path, const char * out_file_name);

private:
	void create_connection();
	void check_response_status(boost::asio::streambuf & response);
	void make_request( std::ostream & request_stream, const char * url_path );


	void DEBUG_FILE( boost::asio::ip::tcp::socket & socket, boost::asio::streambuf & response );
private:
	std::string m_host;
	boost::asio::io_service m_io_service;
	boost::asio::ip::tcp::socket m_socket;
};

} // ns cbr
