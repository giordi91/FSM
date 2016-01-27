#include <gmock/gmock.h> 
#include <string>
#include "fixtures.h"
#include <memory>
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
	
	
	FSM::GenericState state1("rocking") ;
	FSM::GenericState state2("brick") ;
	Connection conn((State*)&state1, (State*)&state2);

	conn.add_condition(static_cast<FSM::Condition*>(tp1.get()));
	conn.add_condition(static_cast<FSM::Condition*>(tp2.get()));
	string check= conn.serialize();
	string expected("<< Connection ### rocking , brick >>\n"
		"<< TypedCondition<bool> ### x , 0 , equal >>\n"
		"<< TypedCondition<float> ### y , 10.00000 , less >>\n"
		"<<< CONNECTIONS >>>\n");
	ASSERT_EQ(expected, check);
	
	Connection conn2(&state1, &state2);
	conn2.add_condition(static_cast<FSM::Condition*>(dv1.get()));
	conn2.add_condition(static_cast<FSM::Condition*>(dv2.get()));

	check= conn2.serialize();
	expected =("<< Connection ### rocking , brick >>\n"
			   "<< DoubleVarCondition<float> ### z , w , greather >>\n"
			   "<< DoubleVarCondition<int> ### h , i , equal >>\n"
			   "<<< CONNECTIONS >>>\n");
	ASSERT_EQ(expected, check);

}

