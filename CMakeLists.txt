cmake_minimum_required(VERSION 2.8)

set(project cbr-hist)
project(${project} C CXX)

set(source 	CbrHistory.cpp
                CurrencyDataContainer.cpp
                CurrencyData.cpp
                CurrencyDownloader.cpp
                XmlParser.cpp
)

set (headers   CbrHistory.hpp
                    CurrencyDataContainer.hpp
                    CurrencyData.hpp
                    CurrencyDownloader.hpp
                    XmlParser.hpp
)

add_library(${project} SHARED ${sources} ${headers})

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
target_compile_options(${project} PRIVATE "-std=c++11")

target_link_libraries(${project}   curl 
                                            pugixml
)