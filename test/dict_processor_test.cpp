/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
/**
 * @file dict_processor_test.cpp
 * @author shichengyi(com@baidu.com)
 * @date 2014/03/10 00:43:32
 * @brief 测试 processor
 * @version 1.0
 *  
 **/
#include <vector>
#include <boost/shared_ptr.hpp>
#include <gtest/gtest.h>
#include "common.h"
#include "dict_processor.h"
	
int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
 
/**
 * @brief 
**/
class test_DictProcessor_process_suite : public ::testing::Test
{
protected:
    test_DictProcessor_process_suite(){};
    virtual ~test_DictProcessor_process_suite(){};
    virtual void SetUp() 
    {
        //Called befor every TEST_F(test_DictProcessor_process_suite, *)
        testProcessor = new cm::DictProcessor;
    };
    virtual void TearDown() 
    {
        //Called after every TEST_F(test_DictProcessor_process_suite, *)
        delete testProcessor;
    };
    cm::DictProcessor *testProcessor;
};
 
/**
 * @brief 测试处理函数，结果存入columns
 * @begin_version 
**/
TEST_F(test_DictProcessor_process_suite, case_name1)
{
    testProcessor->process("1\t2\t3");
    ASSERT_EQ(3, testProcessor->get_columns().size());
}
 
/**
 * @brief 
**/
class test_DictProcessor_get_suite : public ::testing::Test
{
protected:
    test_DictProcessor_get_suite(){};
    virtual ~test_DictProcessor_get_suite(){};
    virtual void SetUp() 
    {
        //Called befor every TEST_F(test_DictProcessor_get_suite, *)
        testProcessor = new cm::DictProcessor;
        testProcessor->process("1\tcstring\t3,4,5");
    };
    virtual void TearDown() 
    {
        //Called after every TEST_F(test_DictProcessor_get_suite, *)
        delete testProcessor;
    };
    cm::DictProcessor *testProcessor;
};
 
/**
 * @brief 测试获得 第一列 int 值
 * @begin_version 
**/
TEST_F(test_DictProcessor_get_suite, case_name1)
{
    int a = 0;
    cm::ErrorCode ret = testProcessor->get_column_value<int>(0, &a);
    ASSERT_EQ(1, a);
    ASSERT_EQ(0, ret);
}
 
/**
 * @brief 测试获得 cstring
 * @begin_version 
**/
TEST_F(test_DictProcessor_get_suite, case_name2)
{
    boost::shared_ptr<char> p;
    size_t size;
    cm::ErrorCode ret = testProcessor->get_column_value<char>(1, &p, &size);
    ASSERT_STREQ("cstring", p.get());
    ASSERT_EQ(0, ret);
}
 
/**
 * @brief 测试获得 超出范围列
 * @begin_version 
**/
TEST_F(test_DictProcessor_get_suite, case_name3)
{
    //TODO
    boost::shared_ptr<int> p;
    size_t size;
    cm::ErrorCode ret = testProcessor->get_column_value<int>(4, &p, &size);
    ASSERT_EQ(cm::OUT_OF_BOUNDS, ret);
}

/**
 * @brief 测试获得build-in数组
 * @begin_version 
**/
TEST_F(test_DictProcessor_get_suite, case_name4)
{
    //TODO
    boost::shared_ptr<int> p;
    size_t size;
    cm::ErrorCode ret = testProcessor->get_column_value<int>(2, &p, &size);
    ASSERT_EQ(3, size);
    ASSERT_EQ(0, ret);
}
 
/**
 * @brief 
**/
class test_DictProcessor_getLine_suite : public ::testing::Test
{
protected:
    test_DictProcessor_getLine_suite(){};
    virtual ~test_DictProcessor_getLine_suite(){};
    virtual void SetUp() 
    {
        //Called befor every TEST_F(test_DictProcessor_getLine_suite, *)
        testProcessor = new cm::DictProcessor;
        testProcessor->process("1\tcstring\t3,4,5");
    };
    virtual void TearDown() 
    {
        //Called after every TEST_F(test_DictProcessor_getLine_suite, *)
        delete testProcessor;
    };
    cm::DictProcessor *testProcessor;
};
 
/**
 * @brief 测试获得处理后的数据
 * @begin_version 
**/
TEST_F(test_DictProcessor_getLine_suite, case_name1)
{
    const std::vector<std::string>& column_vector = testProcessor->get_columns();
    ASSERT_EQ(3, column_vector.size());
}
