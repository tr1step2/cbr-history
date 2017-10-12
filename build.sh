#!/bin/bash

BOOST_ROOT=/mnt/d/develop/Backup/Main/Libs/boost_1_57_0/

$BOOST_ROOT/bjam -sBOOST_ROOT=$BOOST_ROOT -j4 debug link=static threading=multi toolset=gcc cxxflags=-std=c++11 
