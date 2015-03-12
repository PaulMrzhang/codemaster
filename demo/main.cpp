/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
/**
 * @file main.cpp
 * @author shichengyi(com@baidu.com)
 * @date 2014/03/09 14:06:34
 * @brief demo程序
 * @version 1.0
 *  
 **/

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <boost/any.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/smart_ptr.hpp>
#include "dict_processor.h"
#include "function.h"
#include "util.h"

const size_t COLUMN_1 = 0;
const size_t COLUMN_2 = 1;
const size_t COLUMN_3 = 2;
const size_t COLUMN_4 = 3;
const size_t COLUMN_5 = 4;
const size_t COLUMN_6 = 5;

struct Line 
{
    int a;
    char b;
    double c;
};

void str_to_type(const std::string& value, Line* a) 
{
    std::vector<std::string> column_data; 
    cm::Util::separate_string<std::string>(value, ",", &column_data);
    cm::Function<int>::str_to_type(column_data[0], &a->a);
    cm::Function<char>::str_to_type(column_data[1], &a->b);
    cm::Function<double>::str_to_type(column_data[2], &a->c);
}

int main(int argc, char *argv[])
{
    std::string dictname("dict");
  
    char c = '\0';
    while ((c = getopt(argc, argv, "c:f:hv")) != -1) 
    {
        switch (c) 
        {
            case 'f':
                dictname.assign(optarg);
                break;
            case 'h':
                std::cout << "usage: ./codemaster -f dict_file" << std::endl;
            default:
                return -1;
        }
    }
  
    cm::Function<Line>::Type func = boost::bind(&str_to_type, _1, _2);
  
    cm::UserFunction::add_function<Line>(func);
    cm::DictProcessor processor;
  
    std::string line;
    std::ifstream input_file_stream(dictname.c_str());
  
    cm::ErrorCode ret = cm::OK;
    while (std::getline(input_file_stream, line)) 
    {
        processor.process(line);
  
        int int_val;
        ret = processor.get_column_value<int>(COLUMN_1, &int_val);
        std::cout << int_val << " ";
        if (ret != cm::OK)
        {
            continue;
        }
  
        char char_val;
        ret = processor.get_column_value<char>(COLUMN_2, &char_val);
        std::cout << char_val << " ";
        if (ret != cm::OK)
        {
            continue;
        }
  
        double double_val;
        ret = processor.get_column_value<double>(COLUMN_3, &double_val);
        std::cout << double_val << " ";
        if (ret != cm::OK)
        {
            continue;
        }
  
        size_t size = 0;
        boost::shared_ptr<char> pcstring;
        ret = processor.get_column_value<char>(COLUMN_4, &pcstring, &size);
        std::cout << "\"" << pcstring.get() << "\" ";
        if (ret != cm::OK)
        {
            continue;
        }
  
        boost::shared_ptr<int> arr_pointer;
        ret = processor.get_column_value<int>(COLUMN_5, &arr_pointer, &size);
        if (ret != cm::OK)
        {
            continue;
        }
        std::cout << "[";
        int* arr = arr_pointer.get();
        for (size_t i = 0; i < size; ++i) 
        {
            std::cout << arr[i] << ",";
        }
        std::cout << "] ";
  
        Line line;
        ret = processor.get_column_value<Line>(COLUMN_6, &line);
        if (ret != cm::OK)
        {
            continue;
        }
        std::cout << "{";
        std::cout << line.a << ",";
        std::cout << line.b << ",";
        std::cout << line.c << ",";
        std::cout << "}" << std::endl;
    }
  
    return 0;
}
