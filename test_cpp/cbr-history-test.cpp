#ifdef _WIN32
#include <Windows.h>
#else

#endif

#include <iostream>
#include <stdexcept>
#include <exception>

using LoadDataFuncType = int(*)(const char *, const char *, const char *, char **);
using GetNextFuncType = int(*)(char **, char **, char **);

LoadDataFuncType load_data;
GetNextFuncType get_next;

void register_library()
{
#ifdef _WIN32
	HINSTANCE libhandle = ::LoadLibrary("cbr-history.dll");
	if (!libhandle)
		throw std::runtime_error("Can't load library.");

	load_data = (LoadDataFuncType)::GetProcAddress(libhandle, "load_data");
	get_next = (GetNextFuncType)::GetProcAddress(libhandle, "get_next");

#else
	//dlsym
#endif // _WIN32
}

void parse_arguments(int argc, char **argv, std::string & char_code, std::string & start_date, std::string & end_date)
{
	if (argc != 4)
		throw std::runtime_error("using: <char_code> <start_date> <end_date>\nFor example: EUR 01.01.2000 01.01.2001");

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

		//load library and symbols
		register_library();

		char *error = NULL;
		if (0 != load_data(char_code.c_str(), start_date.c_str(), end_date.c_str(), &error))
			throw std::runtime_error(error);

		int res = 1;
		while(res > 0)
		{
			char *date = NULL;
			char *value = NULL;

			res = get_next(&date, &value, &error);
			if (-1 == res)
				throw std::runtime_error(error);
			else if (res == 0)
				break;

			std::cout << date << " " << value << std::endl;
		}
    }
    catch(const std::exception & e)
    {
        std::cout << e.what() << std::endl;
    }
}
