#include <gmock/gmock.h> 
#include <string>
#include <memory>
#include "fixtures.h" 
#include "Condition.h"
#include "Connection.h"
#include "State.h"

using namespace testing;
using FSM::GenericState;
using std::string;



TEST_F(connectionCreation, evaluating_state)
{
	GenericState state1("state1");
	GenericState state2("state2");

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


TEST_F(connectionCreation, serialize_state)
{
	GenericState state1("state1");
	GenericState state2("state2");

	Connection conn(&state1, &state2);
	conn.add_condition(tp1.get());
	state1.add_connection(&conn);
	
	string check = state1.serialize();
	string expected("<< GenericState ### state1 >>\n"
					"<< Connection ### state1 , state2 >>\n"
					"<< TypedCondition<bool> ### x , 0 , 0 >>\n"
					"<<< CONDITIONS >>>\n"
					"<<< CONNECTIONS >>>");


	ASSERT_EQ(check, expected);
	

	Connection conn2(&state1, &state2);
	conn2.add_condition(tp2.get());
	conn2.add_condition(dv1.get());
	state1.add_connection(&conn2);

	check = state1.serialize();
	expected = ("<< GenericState ### state1 >>\n"
				"<< Connection ### state1 , state2 >>\n"
				"<< TypedCondition<bool> ### x , 0 , 0 >>\n"
				"<<< CONDITIONS >>>\n"
				"<< Connection ### state1 , state2 >>\n"
				"<< TypedCondition<float> ### y , 10.00000 , 2 >>\n"
				"<< DoubleVarCondition<float> ### z , w , 1 >>\n"
				"<<< CONDITIONS >>>\n"
				"<<< CONNECTIONS >>>" );
	ASSERT_EQ(check, expected);
}


