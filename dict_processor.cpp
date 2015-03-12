/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/

/**
 * @file dict_processor.cpp
 * @author shichengyi(com@baidu.com)
 * @date 2014/03/09 14:09:56
 * @brief 实现类
 * @version 1.0
 *  
 **/

#include <string>
#include <boost/array.hpp>
#include "dict_processor.h"
#include "util.h"

namespace cm 
{

DictProcessor::DictProcessor() : _columns()
{ }

DictProcessor::~DictProcessor() 
{ }

void DictProcessor::process(const std::string& line)
{
    _columns.clear();
    cm::Util::separate_string<std::string>(line, "\t", &_columns);
}

}
