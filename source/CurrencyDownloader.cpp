#include "stdafx.h"

#include "CurrencyDownloader.hpp"

using io_tcp = boost::asio::ip::tcp;

void cbr::CurrencyDownloader::download_file(const char * host, const char * url_path, const char * out_file_name)
{
	boost::asio::io_service io_service;

	io_tcp::resolver resolver(io_service);
	io_tcp::resolver::query query(host, "http");
	io_tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

	io_tcp::socket socket(io_service);
	boost::asio::connect(socket, endpoint_iterator);

	boost::asio::streambuf request;
	std::ostream request_stream(&request);

	boost::asio::write(socket, request);

	boost::asio::streambuf response;
	boost::system::error_code error;

	boost::asio::read_until(socket, response, "\r\n\r\n");
	std::istream response_stream(&response);

	DEBUG_FILE(socket, response);

	check_response_status(response);

	std::ofstream file(out_file_name, std::ios_base::out | std::ios_base::ate);
	if (!file)
		throw std::runtime_error(std::string("Can't open file ") + out_file_name + " for Write.");

	//write result to file
	while (boost::asio::read(socket, response, boost::asio::transfer_at_least(1), error))
		file << &response;

	if (error != boost::asio::error::eof)
		throw boost::system::system_error(error);
}

void cbr::CurrencyDownloader::DEBUG_FILE(io_tcp::socket & socket, boost::asio::streambuf & response)
{
	std::ofstream file("debug_file.txt", std::ios_base::out | std::ios_base::ate);
	if (!file)
		throw std::runtime_error("Can't open file debug_file.txt for Write.");

	//write result to file
	boost::system::error_code error;
	while (boost::asio::read(socket, response, boost::asio::transfer_at_least(1), error))
		file << &response;

	throw std::runtime_error("DEBUG FUNCTION USED");
}

void make_request(boost::asio::streambuf & request, const char * host, const char * url_path)
{
	std::ostream request_stream(&request);

	request_stream << "GET " << url_path << " HTTP/1.0\r\n";
	request_stream << "Host: " << host << "\r\n";
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
