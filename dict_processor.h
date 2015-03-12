/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
/**
 * @file dict_processor.h
 * @author shichengyi(com@baidu.com)
 * @date 2014/03/09 14:06:34
 * @brief 处理每一行的数据，返回用户需要的类型
 * @version 1.0
 *  
 **/

#ifndef  PSSPIDER_CODEMASTER_DICT_PROCESSOR_H
#define  PSSPIDER_CODEMASTER_DICT_PROCESSOR_H

#include <sstream>
#include <boost/shared_ptr.hpp>
#include "common.h"
#include "function.h"

namespace cm 
{

class DictProcessor
{
public:

    DictProcessor();
  
    ~DictProcessor();
    
    void process(const std::string& line);
  
    template <typename T>
    cm::ErrorCode get_column_value(const size_t column, T* value); 
  
    template <typename T>
    cm::ErrorCode get_column_value(const size_t column, 
                                   boost::shared_ptr<T>* value, 
                                   size_t* size);
    
    const std::vector<std::string>& get_columns()
    {
        return _columns;
    }

private:
    std::vector<std::string> _columns;

    DISALLOW_COPY_AND_ASSIGN(DictProcessor);
};

namespace type
{

template <typename D>
class UserType
{
public:
    /**
     * @author shichengyi(com@baidu.com)
     * @brief operator() 解析用户自定义类型
     * @param processor 处理器
     * @param column 所在列
     * @param t 返回值
     *
     * @return ErrorCode
     */
    cm::ErrorCode operator()(cm::DictProcessor* processor, const size_t column, D* t) const
    {
        if (processor == NULL || t == NULL)
        {
            return NULL_POINTER;
        }
        const std::vector<std::string>& column_vector = processor->get_columns();
        if (column >= column_vector.size()) 
        {
            return OUT_OF_BOUNDS;
        }
        const std::string& data = column_vector[column];
        typedef typename cm::Function<D>::Type StrtoType;
        StrtoType user_function;
        cm::ErrorCode ret = cm::UserFunction::get_function<D>(typeid(D).name(), &user_function);
        user_function(data, t);
        return ret;
    }
};

template <typename D>
class BaseType
{
public:
    /**
     * @author shichengyi(com@baidu.com)
     * @brief operator() 解析 build-in 类型 
     *
     * @param processor 处理器
     * @param column 所在列
     * @param t 返回值
     
     * @return ErrorCode
     */
    cm::ErrorCode operator()(cm::DictProcessor* processor, const size_t column, D* t) const
    {
        if (processor == NULL || t == NULL)
        {
            return NULL_POINTER;
        }
        const std::vector<std::string>& column_vector = processor->get_columns();
        if (column >= column_vector.size())
        {
            return OUT_OF_BOUNDS;
        }
        const std::string& data = column_vector[column];
        cm::Function<D>::str_to_type(data, t);
        return OK;
    }
};

}

/**
 * @author shichengyi(com@baidu.com)
 * @brief get build-in 类型 或者 用户自定义类型
 *
 * @tparam T 类型
 * @param column 所在列
 * @param val 返回值
 *
 * @return ErrorCode 返回值
 */
template <typename T>
cm::ErrorCode DictProcessor::get_column_value(const size_t column, T* value)
{
    typedef typename boost::mpl::if_<
        typename boost::is_class<T>::type,
                 type::UserType<T>,
                 type::BaseType<T> >::type GetType;

    return GetType()(this, column, value);
}

/**
 * @author shichengyi(com@baidu.com)
 * @brief get build-in 类型数组
 *
 * @tparam T 数组类型
 * @param column 所在列
 * @param value 返回值
 * @param size 数组长度
 *
 * @return ErrorCoe 数组指针 数组长度
 */
template <typename T>
cm::ErrorCode DictProcessor::get_column_value(const size_t column, 
                                              boost::shared_ptr<T>* value, 
                                              size_t* size)
{
    if (size == NULL)
    {
        return NULL_POINTER;
    }
    const std::vector<std::string>& column_vector = get_columns();
    if (column >= column_vector.size()) 
    {
        return OUT_OF_BOUNDS;
    }
    const std::string& data = column_vector[column];
    cm::Function<T*>::str_to_type(data, value, size);
    return OK;
}

}

#endif  //PSSPIDER_CODEMASTER_DICT_PROCESSOR_H
