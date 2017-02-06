#include "NativeCaller.h"

#include <string>
#include <memory>
#include <iostream>

#include "HistoryManager.hpp"

JNIEXPORT void JNICALL Java_NativeCaller_callHistory
  (JNIEnv *env, jobject obj, jstring j_char_code, jstring j_start_date, 
    jstring j_end_date, jstring j_file_out)
{
    cbr::HistoryManager manager;

    std::string char_code = "USD";
    std::string start_date = "01.01.2016";
    std::string end_date = "01.01.2017";
    std::string file_name = "java_forex_out.xml";

    cbr::CurrencyDataContainerSPtr result = manager.get_history(char_code.c_str(),
                                                                start_date.c_str(),
                                                                end_date.c_str(),
                                                                file_name.c_str());

    for(const auto & cur : *result)
    {
        std::cout << cur.first << " " << cur.second->value << std::endl;
    }
}

