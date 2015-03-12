/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
/**
 * @file function_test.cpp
 * @author shichengyi(com@baidu.com)
 * @date 2014/03/10 00:43:32
 * @brief 测试 function
 * @version 1.0
 *  
 **/

#include <gtest/gtest.h>
#include "function.h"
	
int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
 
/**
 * @brief 
**/
class test_Function_parse_suite : public ::testing::Test
{
protected:
    test_Function_parse_suite(){};
    virtual ~test_Function_parse_suite(){};
    virtual void SetUp() 
    {
        //Called befor every TEST_F(test_Function_parse_suite, *)
    };
    virtual void TearDown() 
    {
        //Called after every TEST_F(test_Function_parse_suite, *)
    };
  
};
 
/**
 * @brief 测试字符串转int
 * @begin_version 
**/
TEST_F(test_Function_parse_suite, case_name1)
{
  int a;
  cm::Function<int>::str_to_type("123", &a);
  ASSERT_EQ(123, a);
}
 
/**
 * @brief 
**/
class test_parse_cstring_suite : public ::testing::Test
{
protected:
    test_parse_cstring_suite(){};
    virtual ~test_parse_cstring_suite(){};
    virtual void SetUp() 
    {
        //Called befor every TEST_F(test_parse_suite, *)
    };
    virtual void TearDown() 
    {
        //Called after every TEST_F(test_parse_suite, *)
    };
};
 
/**
 * @brief 测试字符串转csting
 * @begin_version 
**/
TEST_F(test_parse_cstring_suite, case_name1)
{
    boost::shared_ptr<char> p;
    size_t size;
    cm::Function<char*>::str_to_type("123", &p, &size);
    ASSERT_STREQ("123", p.get());
    ASSERT_EQ(3, size);
}
 
/**
 * @brief 
**/
class test_parse_array_suite : public ::testing::Test
{
protected:
    test_parse_array_suite(){};
    virtual ~test_parse_array_suite(){};
    virtual void SetUp() 
    {
        //Called befor every TEST_F(test_<_parse_suite, *)
    };
    virtual void TearDown() 
    {
        //Called after every TEST_F(test_<_parse_suite, *)
    };
};
 
/**
 * @brief 测试字符串转 build-in 数组
 * @begin_version 
**/
TEST_F(test_parse_array_suite, case_name1)
{
    boost::shared_ptr<int> p;
    size_t size;
    cm::Function<int*>::str_to_type("1,2,3", &p, &size);
    int* arr = p.get();
    ASSERT_EQ(1, *arr);
    ASSERT_EQ(2, *(arr + 1));
    ASSERT_EQ(3, *(arr + 2));
    ASSERT_EQ(3, size);
}
