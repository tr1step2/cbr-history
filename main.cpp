#include <iostream>
#include <sstream>
#include <fstream>

#include <exception>
#include <stdexcept>

#include <map>
#include <set>

#include <utility>

#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string/replace.hpp>

#include <curl/curl.h>
#include <pugixml/pugixml.hpp>

size_t callback_impl(char * ptr, size_t size, size_t nmemb, const void * filename, std::ios_base::openmode mode = std::ios_base::out)
{
    static thread_local std::set<const char *> first_time_files;
    bool first_time = first_time_files.find((const char *)filename) == first_time_files.end();

    auto open_mode = first_time ? std::ofstream::trunc : std::ofstream::app;
    open_mode |= mode;

    first_time_files.insert((const char *)filename);

    std::ofstream file_out(static_cast<const char *>(filename), open_mode);
    if (file_out)
        file_out.write(ptr, nmemb * size);

    return size * nmemb;
}

size_t callback_data(char * ptr, size_t size, size_t nmemb, const void * filename)
{
    return callback_impl(ptr, size, nmemb, filename);
}

size_t binary_callback_data(char * ptr, size_t size, size_t nmemb, const void * filename)
{
    return callback_impl(ptr, size, nmemb, filename, std::ofstream::binary);
}

void get_file_impl(const char * url, const char * filename, size_t(*pf)(char * ptr, size_t, size_t, const void *))
{
    CURL *chandle = curl_easy_init();
    if (!chandle)
        throw std::runtime_error("Can't init curl instance");

    curl_easy_setopt(chandle, CURLOPT_URL, url);
    curl_easy_setopt(chandle, CURLOPT_WRITEFUNCTION, pf);
    curl_easy_setopt(chandle, CURLOPT_WRITEDATA, filename);

    CURLcode res = curl_easy_perform(chandle);
    if (CURLE_OK != res)
        throw std::runtime_error("Some errors caught due http request.");

    curl_easy_cleanup(chandle);
}

void get_xml_file(const char * url, const char * filename)
{
    get_file_impl(url, filename, callback_data);
}

void get_binary_file(const char * url, const char * filename)
{
    get_file_impl(url, filename, binary_callback_data);
}

struct ValuteList
{
    struct Valute
    {
        Valute(const char * id, const char * num_code, const char * char_code,
               const char * name)
            : id(id)
            , num_code(boost::lexical_cast<uint16_t>(num_code))
            , char_code(char_code)
            , name(name)
        {
        }

        std::string id;
        uint16_t num_code;
        std::string char_code;
        std::string name;
    };

    std::map<std::string, Valute> valutes;
};

ValuteList get_valute_list(const char * filename)
{
    pugi::xml_document doc;
    pugi::xml_parse_result res = doc.load_file(filename);

    if (!res)
        throw std::runtime_error(res.description());

    ValuteList forex;

    auto valutes = doc.child("ValCurs");
    for (const auto & v : valutes)
    {
        ValuteList::Valute valute(v.attribute("ID").value(),
                                 v.child("NumCode").child_value(),
                                 v.child("CharCode").child_value(),
                                 v.child("Name").child_value());

        forex.valutes.insert(std::make_pair(valute.char_code, valute));
    }

    return forex;
}

struct ForexData
{
    struct ForexValue
    {
        ForexValue(const char * date, const char * nominal, const char * value)
            : date(date)
            , nominal(boost::lexical_cast<uint16_t>(nominal))
            , value(boost::lexical_cast<double>(value))
        {
        }

        std::string date;
        uint16_t nominal;
        double value;
    };

    std::map<std::string, ForexValue> forex_values;
};

ForexData get_forex_data(const char * filename)
{
    pugi::xml_document doc;
    auto result = doc.load_file(filename);

    if (!result)
        throw std::runtime_error(result.description());

    ForexData forex_data;

    auto valutes = doc.child("ValCurs");
    for(const auto & val : valutes)
    {
        std::string value(val.child("Value").child_value());
        boost::replace_all(value, ",", ".");

        ForexData::ForexValue forex(val.attribute("Date").value(),
                                    val.child("Nominal").child_value(),
                                    value.c_str());

        forex_data.forex_values.insert(std::make_pair(forex.date, forex));
    }

    return forex_data;
}

void parse_arguments(int argc, char **argv, std::string & char_code, std::string & start_date, std::string & end_date)
{
    if (argc < 4)
        throw std::runtime_error("Wrong arguments amount. Format: \n"
                                 "./a.out char_code start_date end_date");

    char_code = argv[1];
    start_date= argv[2];
    end_date = argv[3];
}

/*
 * All:
 * http://cbr.ru/scripts/XML_daily.asp
 *
 * By date:
 * www.cbr.ru/scripts/XML_dynamic.asp?date_req1=02/03/2001&date_req2=14/03/2001&VAL_NM_RQ=R01235
 *
 * Graf
 * http://www.cbr.ru/currency_base/GrafGen.aspx?date_req1=21.01.2012&date_req2=28.01.2016&VAL_NM_RQ=R01235
 */

void get_valute(const char * char_code, const char * start_date, const char * end_date, const char * list_path, const char * forex_path)
{
    const char * get_valute_request = "http://cbr.ru/scripts/XML_dynamic.asp?date_req1={{start_date}}&date_req2={{end_date}}&VAL_NM_RQ={{valute_id}}";
    const char * get_graf_request = "http://www.cbr.ru/currency_base/GrafGen.aspx?date_req1={{start_date}}&date_req2={{end_date}}&VAL_NM_RQ={{valute_id}}";

    //get valute list
    get_xml_file("http://cbr.ru/scripts/XML_daily.asp", list_path);
    ValuteList list = get_valute_list(list_path);

    //find valute ID by char code
    const auto valute = list.valutes.find(char_code);
    if (valute == list.valutes.end())
        throw std::runtime_error("Can't find valute with specifiend char code");

    //prepare request for getting data for specified period and valute
    std::string request = get_valute_request;
    boost::replace_first(request, "{{start_date}}", start_date);
    boost::replace_first(request, "{{end_date}}", end_date);
    boost::replace_first(request, "{{valute_id}}", valute->second.id);

    //get data
    get_xml_file(request.c_str(), forex_path);
    ForexData data = get_forex_data(forex_path);

    for(const auto & val : data.forex_values)
        std::cout << val.first << " " << val.second.value << std::endl;

    //get graphic for it
    std::string request_graf = get_graf_request;
    boost::replace_first(request_graf, "{{start_date}}", start_date);
    boost::replace_first(request_graf, "{{end_date}}", end_date);
    boost::replace_first(request_graf, "{{valute_id}}", valute->second.id);

    get_binary_file(request_graf.c_str(), "graf.png");
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
        get_valute(char_code.c_str(), start_date.c_str(), end_date.c_str(), daily, forex);
    }
    catch(const std::exception & e)
    {
        std::cout << e.what() << std::endl;
    }
}
