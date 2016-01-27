#pragma once

#include <gmock/gmock.h> 
#include <string>
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
using FSM::State;



struct connectionCreation : public Test
{
	FSM::DataStorage dt;
	unique_ptr<TypedCondition<bool>> tp1;
	unique_ptr<TypedCondition<float>> tp2;
	unique_ptr<DoubleVarCondition<float>> dv1;
	unique_ptr<DoubleVarCondition<int>> dv2;
	string s1, s2, s3, s4, s5, s6;
	virtual void SetUp() override
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

		tp1 = std::make_unique<TypedCondition<bool> >(&dt, s1, false, Operation::EQUAL);
		tp2 = std::make_unique<TypedCondition<float> >(&dt, s2, 10.0f, Operation::LESS);
		dv1 = std::make_unique<DoubleVarCondition<float>>(&dt, s3, s4, Operation::GREATHER);
		dv2 = std::make_unique<DoubleVarCondition<int>>(&dt, s5, s6, Operation::EQUAL);
	}
};


class MockState: public State 
{
	
public:
	MockState(string name) :State(name) {}
	MOCK_METHOD0(transition, State*());
	MOCK_METHOD0(get_name, string());
};
