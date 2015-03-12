/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
/**
 * @file util_test.cpp
 * @author shichengyi(com@baidu.com)
 * @date 2014/03/10 00:43:32
 * @brief 测试 util 工具类
 * @version 1.0
 *  
 **/

#include <gtest/gtest.h>
#include "util.h"
	
int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS();
}

/**
 * @brief 
**/
class test_Util_sepstr_suite : public ::testing::Test
{
protected:
    test_Util_sepstr_suite(){};
    virtual ~test_Util_sepstr_suite(){};
    virtual void SetUp() 
    {
        //Called befor every TEST_F(test_Util_sepstr_suite, *)
    };
    virtual void TearDown() 
    {
        //Called after every TEST_F(test_Util_sepstr_suite, *)
    };
};
 
/**
 * @brief 测试字符串分割至int vector
 * @begin_version 
**/
TEST_F(test_Util_sepstr_suite, case_name1)
{
    std::vector<int> int_vector;
    cm::Util::separate_string<int>("1,2,3", ",", &int_vector);
    ASSERT_EQ(1, int_vector[0]);
}
 
/**
 * @brief 测试字符串分割至char vector
 * @begin_version 
**/
TEST_F(test_Util_sepstr_suite, case_name2)
{
    std::vector<char> char_vector;
    cm::Util::separate_string<char>("1t2t3", "t", &char_vector);
    ASSERT_EQ('1', char_vector[0]);
}
 
