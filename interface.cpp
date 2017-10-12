#include "stdafx.h"
#include "HistoryManager.hpp"

#define CBRHISTAPI __declspec(dllexport)

cbr::HistoryManager manager;
cbr::CurrencyDataContainerSPtr result;

void AllocAndCopy(std::string data, char ** out)
{
	if (!out)
		return;

	*out = new char[data.length() + 1];
	std::strcpy(*out, data.c_str());
}

void MakeError(const std::exception & exc, char ** error)
{
	if (!error)
		return;

	AllocAndCopy(exc.what(), error);
}

CBRHISTAPI int load_data(const char * char_code, const char * start_date, const char * end_date, char ** error)
{
	try
	{
		const char * name = "forex.xml";
		result = manager.get_history(char_code, start_date, end_date, name);
	}
	catch (const std::exception & exc)
	{
		MakeError(exc, error);
		return -1;
	}

	return 0;
}

CBRHISTAPI int get_next(char ** date, char ** value, char ** error)
{
	if (!result)
	{
		*error = "Data not loaded";
		return -1;
	}

	static cbr::CurrencyDataContainer::const_iterator iter = result->cbegin();
	static cbr::CurrencyDataContainer::const_iterator end = result->cend();

	try
	{
		if (iter == end)
			throw std::runtime_error("Last value reached");

		std::string dateStr = boost::lexical_cast<std::string>(iter->first);
		std::string valueStr = boost::lexical_cast<std::string>(iter->second->value);

		AllocAndCopy(dateStr, date);
		AllocAndCopy(dateStr, value);
	}
	catch (const std::exception & exc)
	{
		MakeError(exc, error);
		return -1;
	}

	return 0;
}

void parse_arguments(int argc, char **argv, std::string & char_code, std::string & start_date, std::string & end_date)
{
	char_code = argv[1];
	start_date = argv[2];
	end_date = argv[3];
}

int main(int argc, char ** argv)
{
	const char * forex = "forex.xml";

	std::string char_code;
	std::string start_date;
	std::string end_date;

	try
	{
		//get parameters
		parse_arguments(argc, argv, char_code, start_date, end_date);

		cbr::HistoryManager manager;
		cbr::CurrencyDataContainerSPtr result = manager.get_history(char_code.c_str(),
			start_date.c_str(),
			end_date.c_str(),
			forex);

		for (const auto & cur : *result)
		{
			std::cout << cur.first << " " << cur.second->value << std::endl;
		}
	}
	catch (const std::exception & e)
	{
		std::cout << e.what() << std::endl;
	}
}
