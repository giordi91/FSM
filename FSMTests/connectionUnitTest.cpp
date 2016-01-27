#include <gmock/gmock.h> 
#include <string>
#include "fixtures.h"
#include <memory>
#include "Condition.h"
#include "Connection.h"
#include <State.h>
using namespace testing;
using FSM::DoubleVarCondition;
using FSM::TypedCondition;
using FSM::DataType;
using FSM::Operation;
using FSM::Connection;
using FSM::Condition;
using std::unique_ptr;
using FSM::State;


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

TEST_F(connectionCreation, serializing_connection)
{
	
	
	MockState state1("rocking") ;
	MockState state2("brick") ;
	Connection conn((State*)&state1, (State*)&state2);


	EXPECT_CALL(state1, get_name())
		.WillOnce(Return("rocking"));
	conn.add_condition(static_cast<FSM::Condition*>(tp1.get()));
	conn.add_condition(static_cast<FSM::Condition*>(tp2.get()));
	
	Connection conn2(&state1, &state2);
	conn2.add_condition(static_cast<FSM::Condition*>(dv1.get()));
	conn2.add_condition(static_cast<FSM::Condition*>(dv2.get()));
	//ASSERT_EQ(conn2.evaluate(), true);
	std::cout << conn.serialize() << std::endl;
	//conn2.add_condition(static_cast<FSM::Condition*>(tp1.get()));
	//conn2.add_condition(static_cast<FSM::Condition*>(tp2.get()));
	//ASSERT_EQ(conn2.evaluate(), true);

	//dt.set_value(s1, true);
	//ASSERT_EQ(conn2.evaluate(), false);
}