/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
/**
 * @file function.cpp
 * @author shichengyi(com@baidu.com)
 * @date 2014/03/10 00:43:32
 * @brief 仅用于定义
 * @version 1.0
 *  
 **/

#include "function.h"

namespace cm 
{

std::map<const std::string, boost::any> UserFunction::_s_functions;

void Function<char*>::str_to_type(const std::string& str, 
                                  boost::shared_ptr<char>* ret,
                                  size_t* size)
{
    char* p  = new char[sizeof(char) * (str.length() + 1)];
    memcpy(p, str.c_str(), str.length());
    *(p + str.length()) = '\0';
    ret->reset(p, ArrayDeleter<char>());
    *size = str.length();
}

}
