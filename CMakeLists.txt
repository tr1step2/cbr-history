cmake_minimum_required(VERSION 2.8)

set(project cbr-hist)
project(${project} C CXX)

FILE(GLOB SOURCES source/*.cpp source/*.hpp)

add_library(${project} SHARED ${SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
target_compile_options(${project} PRIVATE "-std=c++11")

target_link_libraries(${project}   curl 
                                            pugixml
)