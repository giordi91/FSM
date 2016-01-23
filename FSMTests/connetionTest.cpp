#include <gmock/gmock.h> 
#include <string>
#include <fstream>
#include <iostream>
#include <memory>
#include "Condition.h"
#include "Connection.h"
using namespace testing;
using FSM::DoubleVarCondition;
using FSM::TypedCondition;
using FSM::DataType;
using FSM::Operation;
using FSM::Connection;
using FSM::Condition;
using std::unique_ptr;


class FSM::State;
struct connectionCreation: public Test
{
	FSM::DataStorage dt;
	unique_ptr<TypedCondition<bool>> tp1;
	unique_ptr<TypedCondition<float>> tp2;
	unique_ptr<DoubleVarCondition<float>> dv1;
	unique_ptr<DoubleVarCondition<int>> dv2;
	string s1, s2, s3, s4, s5, s6;
	virtual void SetUp()
	{
		s1 = "x";
		s2 = "y";
		s3 = "z";
		s4 = "w";
		s5 = "h";
		s6 = "i";

		dt.set_value(s1, false);
		dt.set_value(s2, 1.012f);
		dt.set_value(s3, 5.5f);
		dt.set_value(s4, 3.2f);
		dt.set_value(s5, 10);
		dt.set_value(s6, 10);

		tp1 = std::make_unique<TypedCondition<bool> >(&dt,s1, false, Operation::EQUAL);
		tp2 = std::make_unique<TypedCondition<float> >(&dt,s2, 10.0f, Operation::LESS);
		dv1 = std::make_unique<DoubleVarCondition<float>>(&dt,s3,s4 ,Operation::GREATHER);
		dv2 = std::make_unique<DoubleVarCondition<int>>(&dt,s5,s6 ,Operation::EQUAL);
	}
};


TEST_F(connectionCreation, adding_connetions)
{
	FSM::State* state1 = nullptr;
	FSM::State* state2 = nullptr;
	Connection conn(state1, state2);
	conn.add_condition(static_cast<FSM::Condition*>(tp1.get()));
	conn.add_condition(static_cast<FSM::Condition*>(tp2.get()));
	
	ASSERT_EQ(conn.conditions_count(), 2);
	
	conn.add_condition(static_cast<FSM::Condition*>(dv1.get()));
	conn.add_condition(static_cast<FSM::Condition*>(dv2.get()));
	ASSERT_EQ(conn.conditions_count(), 4);

	conn.add_condition(static_cast<FSM::Condition*>(dv1.get()));
	conn.add_condition(static_cast<FSM::Condition*>(dv2.get()));
	ASSERT_EQ(conn.conditions_count(), 6);
}

TEST_F(connectionCreation, evaluating_connection)
{
	FSM::State* state1 = nullptr;
	FSM::State* state2 = nullptr;
	Connection conn(state1, state2);
	conn.add_condition(static_cast<FSM::Condition*>(tp1.get()));
	conn.add_condition(static_cast<FSM::Condition*>(tp2.get()));
	
	Connection conn2(state1, state2);
	conn2.add_condition(static_cast<FSM::Condition*>(dv1.get()));
	conn2.add_condition(static_cast<FSM::Condition*>(dv2.get()));
	ASSERT_EQ(conn2.evaluate(), true);

	conn2.add_condition(static_cast<FSM::Condition*>(tp1.get()));
	conn2.add_condition(static_cast<FSM::Condition*>(tp2.get()));
	ASSERT_EQ(conn2.evaluate(), true);

	dt.set_value(s1, true);
	ASSERT_EQ(conn2.evaluate(), false);
}