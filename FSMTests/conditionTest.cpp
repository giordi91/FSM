
#include <gmock/gmock.h> 
#include <string>
#include <fstream>
#include <iostream>
#include "Condition.h"
using namespace testing;
using FSM::DataType;

TEST(condition_test, float_testing)
{
	DataStorage tmp;
	string k1 = "x";
	string k2 = "y";
	tmp.set_value(k1, 10.0f);
	tmp.set_value(k2, 20.12f);
	TypedCondition<float, float> cond(&tmp,k1, k2);
	ASSERT_EQ(cond.evaluate(), false);
}



