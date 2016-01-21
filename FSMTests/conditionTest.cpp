
#include <gmock/gmock.h> 
#include <string>
#include <fstream>
#include <iostream>
#include "Condition.h"
using namespace testing;
using FSM::DoubleVarCondition;
using FSM::DataType;
using FSM::Operation;

TEST(condition_test, float_testing)
{
	DataStorage tmp;
	string k1 = "x";
	string k2 = "y";
	tmp.set_value(k1, 10.0f);
	tmp.set_value(k2, 20.12f);
	DoubleVarCondition<float> cond(&tmp,k1, k2, Operation::GREATHER);
	ASSERT_EQ(cond.evaluate(), false);


	tmp.set_value(k1, 2.2f);
	tmp.set_value(k2, 0.2f);
	DoubleVarCondition<float> cond2(&tmp,k1, k2, Operation::LESS);
	ASSERT_EQ(cond2.evaluate(), false);
	
	tmp.set_value(k1, -0.2f);
	tmp.set_value(k2, 999.2f);
	DoubleVarCondition<float> cond3(&tmp,k1, k2, Operation::EQUAL);
	ASSERT_EQ(cond3.evaluate(), false);
	
	tmp.set_value(k1, 13.2f);
	tmp.set_value(k2, 13.0f);
	DoubleVarCondition<float> cond4(&tmp,k1, k2, Operation::EQUAL);
	DoubleVarCondition<float> cond5(&tmp,k1, k2, Operation::GREATHEREQUAL);
	DoubleVarCondition<float> cond6(&tmp,k1, k2, Operation::LESSEQUAL);
	ASSERT_EQ(cond4.evaluate(), false);
	ASSERT_EQ(cond5.evaluate(), true);
	ASSERT_EQ(cond6.evaluate(), false);
}



TEST(condition_test, mixed)
{
	DataStorage tmp;
	string k1 = "x";
	string k2 = "y";
	tmp.set_value(k1, 10.0f);
	tmp.set_value(k2, 20.0f);
	DoubleVarCondition<float> cond(&tmp,k1, k2, Operation::GREATHER);
	ASSERT_EQ(cond.evaluate(), false);


	tmp.set_value(k1, 0);
	tmp.set_value(k2, 0);
	DoubleVarCondition<int> cond2(&tmp,k1, k2, Operation::EQUAL);
	DoubleVarCondition<int> cond3(&tmp,k1, k2, Operation::LESS);
	ASSERT_EQ(cond2.evaluate(), true);
	ASSERT_EQ(cond3.evaluate(), false);
}

