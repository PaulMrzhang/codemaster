/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
/**
 * @file common.h
 * @author shichengyi(com@baidu.com)
 * @date 2014/03/10 18:50:48
 * @brief 公共头文件 定义一些常量
 * @version 1.0
 *  
 **/

#ifndef PSSPIDER_CODEMASTER_COMMON_H
#define PSSPIDER_CODEMASTER_COMMON_H

#define DISALLOW_COPY_AND_ASSIGN(TypeName) TypeName(const TypeName&); TypeName& operator=(const TypeName&)

namespace cm 
{

enum ErrorCode 
{
    OK,
    TYPE_NOT_FOUND,
    OUT_OF_BOUNDS,
    NULL_POINTER,
    UNKNOWN
};

}

#endif  //PSSPIDER_CODEMASTER_COMMON_H
