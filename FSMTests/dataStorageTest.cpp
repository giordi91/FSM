
#include <gmock/gmock.h> 
#include <string>
#include <fstream>
#include <iostream>
#include "DataStorage.h"
using namespace testing;

struct dataStorageFixture: public Test
{
	FSM::DataStorage dt;
	virtual void SetUp()
	{
		
	}

};


TEST_F(dataStorageFixture, set_bool)
{
	std::string key = "testBool";
	dt.set_value(key, false);
	ASSERT_EQ(dt.size(FSM::DataType::BOOL), 1);

	key = "secondBool";
	dt.set_value(key, true);
	ASSERT_EQ(dt.size(FSM::DataType::BOOL), 2);
}

TEST_F(dataStorageFixture, set_float)
{
	std::string key = "testFloat";
	dt.set_value(key, 2.03f);
	ASSERT_EQ(dt.size(FSM::DataType::FLOAT), 1);

	key = "secondFloat";
	dt.set_value(key, 23452.44f);
	ASSERT_EQ(dt.size(FSM::DataType::FLOAT), 2);
}

TEST_F(dataStorageFixture, set_int)
{
	std::string key = "testInt";
	dt.set_value(key, 39);
	ASSERT_EQ(dt.size(FSM::DataType::INT), 1);

	key = "secondBool";
	dt.set_value(key, 41);
	ASSERT_EQ(dt.size(FSM::DataType::INT), 2);
}

TEST_F(dataStorageFixture, set_all)
{
	std::string key = "testBool";
	dt.set_value(key, false);
	ASSERT_EQ(dt.size(FSM::DataType::BOOL), 1);

	key = "secondBool";
	dt.set_value(key, true);
	ASSERT_EQ(dt.size(FSM::DataType::BOOL), 2);
	
	key = "testFloat";
	dt.set_value(key, 2.03f);
	ASSERT_EQ(dt.size(FSM::DataType::FLOAT), 1);

	key = "secondFloat";
	dt.set_value(key, 23452.44f);
	ASSERT_EQ(dt.size(FSM::DataType::FLOAT), 2);
	
	key = "testInt";
	dt.set_value(key, 39);
	ASSERT_EQ(dt.size(FSM::DataType::INT), 1);

	key = "secondBool";
	dt.set_value(key, 41);
	ASSERT_EQ(dt.size(FSM::DataType::INT), 2);
	ASSERT_EQ(dt.total_size(), 6);

	

}
