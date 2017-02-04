cmake_minimum_required(VERSION 2.8)

set(project cbr-history)

set(source 	CbrHistory.cpp
				CurrencyDataContainer.cpp
				CurrencyData.cpp
				CurrencyDownloader.cpp
				XmlParser.cpp
)

set (headers 	CbrHistory.hpp
					CurrencyDataContainer.hpp
					CurrencyData.hpp
					CurrencyDownloader.hpp
					XmlParser.hpp
)

target_compile_options(${project} "-std=c++11")

add_library(${project} SHARED ${sources} ${headers})

target_link_libraries(${project} curl pugixml)