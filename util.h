/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
/**
 * @file util.h
 * @author shichengyi(com@baidu.com)
 * @date 2014/03/07 11:04:15
 * @brief 工具类，分割字符串到vector
 * @version 1.0
 *  
 **/

#ifndef  PSSPIDER_CODMASTER_UTIL_H
#define  PSSPIDER_CODMASTER_UTIL_H

#include <sstream>
#include <string>
#include <vector>

namespace cm 
{

class Util 
{
public:
    template <typename T>
    static void separate_string(const std::string& str, 
                                const std::string& separator,
                                std::vector<T>* result_vector);
};

template <typename T>
void Util::separate_string(const std::string& str, 
                           const std::string& separator,
                           std::vector<T>* result_vector)
{
    if (result_vector == NULL)
    {
        return;
    }

    std::string::size_type pos_cur = 0;
    std::string::size_type pos_sep = 0;
  
    while (true) 
    {
        std::string s;
        pos_sep = str.find_first_of(separator, pos_cur);
        if (pos_sep == std::string::npos) 
        {
            if (pos_cur + 1 <= str.length()) 
            {
                s = str.substr(pos_cur);
            }
        } 
        else if (pos_sep == pos_cur) 
        {
            s = "";
        } 
        else 
        {
            s = str.substr(pos_cur, pos_sep - pos_cur);
            pos_cur = pos_sep;
        }
  
        if (!s.empty()) 
        {
            T tmp;
            std::stringstream str_stream(s);
            str_stream >> tmp;
            result_vector->push_back(tmp);
        }
  
        if (pos_sep == std::string::npos) 
        {
            break;
        }
        pos_cur++;
    }
}

}
#endif  //PSSPIDER_CODMASTER_UTIL_H
