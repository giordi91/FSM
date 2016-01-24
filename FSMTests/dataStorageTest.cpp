
#include <gmock/gmock.h> 
#include <string>
#include "DataStorage.h"
using namespace testing;

struct dataStorageFixture: public Test
{
	FSM::DataStorage dt;
	virtual void SetUp() override
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

TEST_F(dataStorageFixture, rewrite_same_key)
{
	std::string key  = "testInt";
	dt.set_value(key, 10);
	int value;
	dt.get_value(key, value);

	ASSERT_EQ(value,10);
	dt.set_value(key, 44);
	dt.get_value(key, value);
	ASSERT_EQ(value,44);

}

TEST_F(dataStorageFixture, bool_getter)
{
	bool value;
	FSM::Status s = dt.get_value("notExisting", value);
	ASSERT_EQ(s , FSM::Status::Failure);

	dt.set_value("exists", true);
	value = false;
	s = dt.get_value("exists", value);
	ASSERT_EQ(s , FSM::Status::Succes);
	ASSERT_EQ(value , true);
}

TEST_F(dataStorageFixture, int_getter)
{
	int value;
	FSM::Status s = dt.get_value("notExisting", value);
	ASSERT_EQ(s , FSM::Status::Failure);

	dt.set_value("exists", 134972);
	value = 0;
	s = dt.get_value("exists", value);
	ASSERT_EQ(s , FSM::Status::Succes);
	ASSERT_EQ(value, 134972);
}

TEST_F(dataStorageFixture, float_getter)
{
	float value;
	FSM::Status s = dt.get_value("notExisting", value);
	ASSERT_EQ(s , FSM::Status::Failure);

	dt.set_value("exists", 3.14f);
	value = 0;
	s = dt.get_value("exists", value);
	ASSERT_EQ(s , FSM::Status::Succes);
	ASSERT_EQ(value, 3.14f);
}
TEST_F(dataStorageFixture, getter_all)
{
	bool b_value;
	FSM::Status s = dt.get_value("notExisting", b_value);
	ASSERT_EQ(s, FSM::Status::Failure);

	dt.set_value("exists", true);
	b_value = false;
	s = dt.get_value("exists", b_value);
	ASSERT_EQ(s, FSM::Status::Succes);
	ASSERT_EQ(b_value, true);

	int i_value;
	s = dt.get_value("notExisting", i_value);
	ASSERT_EQ(s, FSM::Status::Failure);

	dt.set_value("exists", 134972);
	i_value = 0;
	s = dt.get_value("exists", i_value);
	ASSERT_EQ(s, FSM::Status::Succes);
	ASSERT_EQ(i_value, 134972);

	float f_value;
	s = dt.get_value("notExisting", f_value);
	ASSERT_EQ(s, FSM::Status::Failure);

	dt.set_value("exists", 3.14f);
	f_value = 0;
	s = dt.get_value("exists", f_value);
	ASSERT_EQ(s, FSM::Status::Succes);
	ASSERT_EQ(f_value, 3.14f);
}