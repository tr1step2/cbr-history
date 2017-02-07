cmake_minimum_required(VERSION 2.8)

set(project NativeCaller)
project(${project} C CXX)

set(JAVA_HOME $ENV{JAVA_HOME})

FILE(GLOB SOURCES NativeCaller.cpp NativeCaller.hpp)


include_directories(${CMAKE_SOURCE_DIR}/../include/
                    ${JAVA_HOME}/include/
                    ${JAVA_HOME}/include/linux/
)

link_directories(${CMAKE_SOURCE_DIR}/../lib/
                 ${JAVA_HOME}/lib/amd64/
)


add_library(${project} SHARED ${SOURCES})

set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
target_compile_options(${project} PRIVATE "-std=c++11")


target_link_libraries(${project} 
                                 histmgr)
