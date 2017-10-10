#pragma once

#include <string>
#include <memory>
#include <cstdint>
#include <exception>
#include <stdexcept>
#include <map>
#include <vector>
#include <set>
#include <fstream>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/date_time.hpp>
#include <boost/asio.hpp>

using astr = std::string;
using wstr = std::wstring;