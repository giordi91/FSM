#include <gmock/gmock.h> 
#include <string>
#include <memory>
#include "fixtures.h" 
#include "Condition.h"
#include "Connection.h"
#include "State.h"
using namespace testing;
using FSM::DoubleVarCondition;
using FSM::TypedCondition;
using FSM::DataType;
using FSM::Operation;
using FSM::Connection;
using FSM::Condition;
using FSM::State;
using std::unique_ptr;



TEST_F(connectionCreation, evaluating_state)
{
	FSM::State state1 = State("state1");
	FSM::State state2 = State("state2");

	Connection conn(&state1, &state2);
	conn.add_condition(tp1.get());
	state1.add_connection(&conn);

	ASSERT_EQ(state1.transition(), &state2);

	Connection conn2(&state1, &state2);
	conn.add_condition(tp2.get());
	dt.set_value(s2, 12.0f);
	state2.add_connection(&conn2);
	
	ASSERT_EQ(state2.transition(), &state2);
}