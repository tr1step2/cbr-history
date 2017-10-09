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

	//read response. 
	// [0] status string
	// [1] headers
	// [2] bosy
	std::vector<std::string> response = readAllData();
	if ( response.size() != 3 )
		throw std::runtime_error("Error in response structure.");

	check_response_status(response[0]);

	//write response data to file
	std::ofstream file(out_file_name, std::ios_base::out | std::ios_base::ate);
	if (!file)
		throw std::runtime_error(std::string("Can't open file ") + out_file_name + " for Write.");

	file << response[2];
}

std::vector<std::string> cbr::CurrencyDownloader::readAllData()
{
	boost::asio::streambuf resp;
	boost::system::error_code err;

	boost::asio::read(m_socket, resp, err);
	if ( err != boost::asio::error::eof )
		throw boost::system::system_error( err );

	std::stringstream ss;
	ss << &resp;
	std::string str = ss.str();	

	auto statusEnd = str.find("\r\n");
	if ( std::string::npos == statusEnd )
		throw std::runtime_error( "Wrong answer structure. Can't find status line end." );

	std::vector<std::string> result;
	result.push_back( str.substr( 0, statusEnd ) );

	auto headersEnd = str.find("\r\n\r\n");
	if ( std::string::npos == headersEnd )
		throw std::runtime_error( "Wrong answer structure. Can't find headers end." );

	result.push_back( str.substr( statusEnd + 2, headersEnd ) );

	auto bodyEnd = str.find_last_of( "\r\n\r\n" );
	if ( std::string::npos == bodyEnd )
		throw std::runtime_error( "Wrong answer structure. Can't find headers end." );

	result.push_back( str.substr(headersEnd + 4, bodyEnd) );

	return result;
}

void cbr::CurrencyDownloader::make_request( std::ostream & request_stream, const char * url_path )
{
	request_stream << "GET " << url_path << " HTTP/1.0\r\n";
	request_stream << "Host: " << m_host << "\r\n";
	request_stream << "Accept: */*\r\n";
	request_stream << "Connection: close\r\n\r\n";
}

void cbr::CurrencyDownloader::check_response_status(const std::string & response)
{	
	std::stringstream response_stream( response );

	std::string http_version;
	response_stream >> http_version;	

	size_t code;
	response_stream >> code;

	std::string message;
	std::getline( response_stream, message );

	if (code != 200)
	{
		throw std::runtime_error(std::string("Error occured while http request. Code ")
			+ std::to_string(code) + ". Message: " + message);
	}
}