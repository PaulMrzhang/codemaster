/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
/**
 * @file function.h
 * @author shichengyi(com@baidu.com)
 * @date 2014/03/09 20:30:56
 * @brief 定义了各种类型的解析函数以及用于保存用户函数的类
 * @version 1.0
 *  
 **/

#ifndef  PSSPIDER_CODEMASTER_FUNCTION_H
#define  PSSPIDER_CODEMASTER_FUNCTION_H

#include <map>
#include <sstream>
#include <vector>
#include <boost/any.hpp>
#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>
#include "common.h"
#include "util.h"

namespace cm 
{

template <typename T>
class ArrayDeleter
{
public:
    void operator() (T* & array) const
    {
        delete[] array;
        array = NULL;
    }
};

template <typename T>
class Function
{
public:
    typedef boost::function<void(const std::string&, T*)> Type;
  
    static void str_to_type(const std::string& str, T* ret);

private:
    DISALLOW_COPY_AND_ASSIGN(Function);
};

/**
 * @author shichengyi(com@baidu.com)
 * @brief str_to_type string 转成 T类型
 *
 * @tparam T 类型参数
 * @param str 
 * @param ret 返回T类型值
 */
template <typename T>
void Function<T>::str_to_type(const std::string& str, T* ret) 
{
    std::stringstream str_stream;
    str_stream << str;
    str_stream >> *ret;
}

template <>
class Function<char*>
{
public:
    typedef boost::function<void(const std::string&, boost::shared_ptr<char>*)> Type;
  
    static void str_to_type(const std::string& str, 
                            boost::shared_ptr<char>* ret, 
                            size_t* size);
private:
    DISALLOW_COPY_AND_ASSIGN(Function);
};

template <typename T>
class Function<T*>
{
public:
    typedef boost::function<void(const std::string&, boost::shared_ptr<T>*)> Type;
  
    static void str_to_type(const std::string& str, boost::shared_ptr<T>* ret, size_t* size); 

private:
    DISALLOW_COPY_AND_ASSIGN(Function);
};

/**
 * @author shichengyi(com@baidu.com)
 * @brief str_to_type 转为 build-in 数组类型
 *
 * @tparam T
 * @param str 待转字符串,使用','分割
 * @param ret 数组指针
 * @param size 数组长度
 */
template <typename T>
void Function<T*>::str_to_type(const std::string& str, boost::shared_ptr<T>* ret, size_t* size) 
{
    std::vector<T> type_t_vector;
    cm::Util::separate_string<T>(str, ",", &type_t_vector);
    *size = type_t_vector.size();
    T* pointer = new T[*size];
    std::copy(type_t_vector.begin(), type_t_vector.end(), pointer);
    ret->reset(pointer, ArrayDeleter<T>());
}

class UserFunction
{
public:
    typedef std::map<const std::string, boost::any> FuncListType;
  
    template <typename T>
    static void add_function(typename Function<T>::Type func);
  
    template <typename T>
    static cm::ErrorCode get_function(const std::string& name, 
                                      typename Function<T>::Type* func);

private:
    static std::map<const std::string, boost::any> _s_functions;

    DISALLOW_COPY_AND_ASSIGN(UserFunction);
};

template <typename T>
void UserFunction::add_function(typename Function<T>::Type func) 
{
    _s_functions[typeid(T).name()] = func;
}

template <typename T>
typename cm::ErrorCode UserFunction::get_function(const std::string& name, 
                                                  typename Function<T>::Type* user_func) 
{
    FuncListType::iterator it = _s_functions.find(name);
    if (it == _s_functions.end())
    {
        return TYPE_NOT_FOUND;
    }
    typedef typename cm::Function<T>::Type StrtoType;
    *user_func = boost::any_cast<StrtoType>(it->second);
    return OK;
}

}

#endif  //PSSPIDER_CODEMASTER_FUNCTION_H
