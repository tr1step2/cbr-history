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

extern "C"
{

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
		{
			return 0;
		}

		std::string dateStr = boost::lexical_cast<std::string>(iter->first);
		std::string valueStr = boost::lexical_cast<std::string>(iter->second->value);

		AllocAndCopy(dateStr, date);
		AllocAndCopy(valueStr, value);

		++iter;
	}
	catch (const std::exception & exc)
	{
		MakeError(exc, error);
		return -1;
	}

	return 1;
}

} // extern C

