
#include <gmock/gmock.h> 
#include <string>
#include <fstream>
#include <iostream>
#include "Condition.h"
using namespace testing;
using FSM::DataType;

TEST(condition_test, key_type_identification)
{
	DataStorage tmp;
	TypedCondition<float, float> cond(&tmp);
	ASSERT_EQ(cond.get_key_1_type(), DataType::FLOAT);
	ASSERT_EQ(cond.get_key_2_type(), DataType::FLOAT);


	TypedCondition<int, bool> cond2(&tmp);
	ASSERT_EQ(cond2.get_key_1_type(), DataType::INT);
	ASSERT_EQ(cond2.get_key_2_type(), DataType::BOOL);
	
	TypedCondition<bool, int> cond3(&tmp);
	ASSERT_EQ(cond3.get_key_1_type(), DataType::BOOL);
	ASSERT_EQ(cond3.get_key_2_type(), DataType::INT);

	TypedCondition<bool, float> cond4(&tmp);
	ASSERT_EQ(cond4.get_key_1_type(), DataType::BOOL);
	ASSERT_EQ(cond4.get_key_2_type(), DataType::FLOAT);
	
	TypedCondition<int, int> cond5(&tmp);
	ASSERT_EQ(cond5.get_key_1_type(), DataType::INT);
	ASSERT_EQ(cond5.get_key_2_type(), DataType::INT);
}
