#include "stdafx.h"
#include "HistoryManager.hpp"

void parse_arguments(int argc, char **argv, std::string & char_code, std::string & start_date, std::string & end_date)
{
	char_code = argv[1];
	start_date = argv[2];
	end_date = argv[3];
}

int main(int argc, char ** argv)
{
	const char * daily = "daily.xml";
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
