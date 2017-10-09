#include "stdafx.h"

#include "CurrencyDownloader.hpp"

using io_tcp = boost::asio::ip::tcp;


cbr::CurrencyDownloader::CurrencyDownloader( const char * host )
	: m_host(host)
	, m_socket( m_io_service )
{
	create_connection();
}

void cbr::CurrencyDownloader::create_connection()
{
	io_tcp::resolver resolver( m_io_service );
	io_tcp::resolver::query query( m_host, "http" );
	io_tcp::resolver::iterator endpoint_iterator = resolver.resolve( query );

	boost::asio::connect( m_socket, endpoint_iterator );
}

void cbr::CurrencyDownloader::download_file(const char * url_path, const char * out_file_name)
{
	//create request
	boost::asio::streambuf request;
	std::ostream request_stream(&request);
	make_request( request_stream, url_path );

	//send request
	boost::asio::write(m_socket, request);

	//read response status and headers
	boost::asio::streambuf response;
	boost::asio::read_until( m_socket, response, "\r\n\r\n" );
	std::istream response_stream(&response);

	check_response_status(response);

	//wrute response data to file
	std::ofstream file(out_file_name, std::ios_base::out | std::ios_base::ate);
	if (!file)
		throw std::runtime_error(std::string("Can't open file ") + out_file_name + " for Write.");

	boost::system::error_code error;
	while (boost::asio::read(m_socket, response, boost::asio::transfer_at_least(1), error))
		file << &response;

	if (error != boost::asio::error::eof)
		throw boost::system::system_error(error);
}

void cbr::CurrencyDownloader::make_request( std::ostream & request_stream, const char * url_path )
{
	request_stream << "GET " << url_path << " HTTP/1.0\r\n";
	request_stream << "Host: " << m_host << "\r\n";
	request_stream << "Accept: */*\r\n";
	request_stream << "Connection: close\r\n\r\n";
}

void cbr::CurrencyDownloader::check_response_status(boost::asio::streambuf & response)
{
	std::istream response_stream(&response);

	std::string http_version;
	response_stream >> http_version;

	size_t code;
	response_stream >> code;

	std::string message;
	response_stream >> message;

	if (code != 200)
	{
		throw std::runtime_error(std::string("Error occured while http request. Code ")
			+ std::to_string(code) + ". Message: " + message);
	}
}

void cbr::CurrencyDownloader::DEBUG_FILE( io_tcp::socket & socket, boost::asio::streambuf & response )
{
	std::ofstream file( "debug_file.txt", std::ios_base::out | std::ios_base::ate );
	if ( !file )
		throw std::runtime_error( "Can't open file debug_file.txt for Write." );

	//write result to file
	boost::system::error_code error;
	while ( boost::asio::read( socket, response, boost::asio::transfer_at_least( 1 ), error ) )
		file << &response;

	throw std::runtime_error( "DEBUG FUNCTION USED" );
}