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

    const char * char_code_ptr = env->GetStringUTFChars(j_char_code, 0);
    const char * start_date_ptr = env->GetStringUTFChars(j_start_date, 0);
    const char * end_date_ptr = env->GetStringUTFChars(j_end_date, 0);
    const char * file_out_ptr = env->GetStringUTFChars(j_file_out, 0);

    cbr::CurrencyDataContainerSPtr result = manager.get_history(char_code_ptr,
                                                                start_date_ptr,
                                                                end_date_ptr,
                                                                file_out_ptr);
    for(const auto & cur : *result)
        std::cout << cur.first << " " << cur.second->value << std::endl;

    env->ReleaseStringUTFChars(j_char_code, char_code_ptr);
    env->ReleaseStringUTFChars(j_start_date, start_date_ptr);
    env->ReleaseStringUTFChars(j_end_date, end_date_ptr);
    env->ReleaseStringUTFChars(j_file_out, file_out_ptr);
}