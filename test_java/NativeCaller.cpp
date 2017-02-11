#include "NativeCaller.h"

#include <string>
#include <memory>
#include <iostream>
#include <boost/date_time.hpp>

#include "HistoryManager.hpp"

inline void println(const char *msg)
{
    std::cout << msg << std::endl;
}

JNIEXPORT jobject JNICALL Java_NativeCaller_callHistory
  (JNIEnv *env, jobject obj, jstring j_char_code, jstring j_start_date, 
    jstring j_end_date, jstring j_file_out)
{
    cbr::HistoryManager manager;

    const char * char_code_ptr = env->GetStringUTFChars(j_char_code, 0);
    const char * start_date_ptr = env->GetStringUTFChars(j_start_date, 0);
    const char * end_date_ptr = env->GetStringUTFChars(j_end_date, 0);
    const char * file_out_ptr = env->GetStringUTFChars(j_file_out, 0);

    cbr::CurrencyDataContainerSPtr result = manager.get_history(char_code_ptr,
                                                                start_date_ptr,
                                                                end_date_ptr,
                                                                file_out_ptr);

    std::cout << "HISTORY LOADED" << std::endl;

    //Creating Currency Data Container and call constructor
    jclass container_data_class = env->FindClass("CurrencyDataContainer");

    jmethodID container_data_init_id = env->GetMethodID(container_data_class, 
        "<init>", "()V");  

    jobject j_data_container = env->NewObject(container_data_class, container_data_init_id);

    //get add data method id
    jmethodID container_data_add_id = env->GetMethodID(container_data_class, "add",
        "(LCurrencyData;)V");

    jclass data_class = env->FindClass("CurrencyData");
    jmethodID data_init_id = env->GetMethodID(data_class, "<init>", 
        "(Ljava/lang/String;SD)V");

    for (const auto & cur : *result)
    {
        std::string tmp_date_str = boost::gregorian::to_simple_string(cur.second->date);
        jstring j_date = env->NewStringUTF(tmp_date_str.c_str());

        jshort j_nominal = cur.second->nominal;
        jdouble j_value = cur.second->value;

        if (j_date == 0 || j_nominal == 0 || j_value == 0)
            println("Some value is empty");

        jobject j_currency_data = env->NewObject(data_class, data_init_id,
            j_date, j_nominal, j_value);

        env->CallVoidMethod(j_data_container, container_data_add_id, j_currency_data);
    }

    env->ReleaseStringUTFChars(j_char_code, char_code_ptr);
    env->ReleaseStringUTFChars(j_start_date, start_date_ptr);
    env->ReleaseStringUTFChars(j_end_date, end_date_ptr);
    env->ReleaseStringUTFChars(j_file_out, file_out_ptr);
}
