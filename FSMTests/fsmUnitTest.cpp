#include <gmock/gmock.h> 
#include <string>
#include <memory>
#include "fixtures.h" 
#include "Condition.h"
#include "Connection.h"
#include "State.h"
#include "FSM.h"
using namespace testing;
using FSM::DoubleVarCondition;
using FSM::TypedCondition;
using FSM::DataType;
using FSM::Operation;
using FSM::Connection;
using FSM::Condition;
using FSM::GenericState;
using FSM::State;
using std::unique_ptr;
using FSM::FiniteStateMachine;


class MockState: public State 
{
	
public:
	MockState(string name) :State(name) {}
	MOCK_METHOD0(transition, State*());


};


struct fsmCreation: public Test
{
	FSM::DataStorage dt;
	unique_ptr<FiniteStateMachine> fsm;

	MockState ducking;
	MockState standing;
	GenericState jumping;
	GenericState diving;

	//MockConditon * tp1;
	//MockConditon tp2;
	//MockConditon dv1;
	//MockConditon dv2;
	string s1, s2, s3, s4, s5, s6;
	
	fsmCreation(): 
					ducking("ducking"),
					standing("standing"),
					jumping("jumping"),
					diving("diving")
	{}

	virtual void SetUp() override
	{
		fsm = std::make_unique<FiniteStateMachine>("fsm", &dt);
	}
};

TEST_F(fsmCreation, assert_no_curr_state)
{
	ASSERT_EQ(fsm->get_states_count(), 0);
	ASSERT_EQ(fsm->get_current_state(), nullptr);
	ASSERT_EQ(fsm->get_current_state_name(), "");
}

TEST_F(fsmCreation, assert_state_current_after_insertion)
{
	fsm->add_state(&ducking);
	
	ASSERT_EQ(fsm->get_states_count(), 1);
	ASSERT_EQ(fsm->get_current_state(), &ducking);
	ASSERT_EQ(fsm->get_current_state_name(), "ducking");

	fsm->add_state(&standing);
	fsm->add_state(&jumping);
	
	ASSERT_EQ(fsm->get_states_count(), 3);
	ASSERT_EQ(fsm->get_current_state(), &ducking);
	ASSERT_EQ(fsm->get_current_state_name(), "ducking");
	
	fsm->add_state(&diving);
	
	ASSERT_EQ(fsm->get_states_count(), 4);
	ASSERT_EQ(fsm->get_current_state(), &ducking);
	ASSERT_EQ(fsm->get_current_state_name(), "ducking");
}

TEST_F(fsmCreation, simple_state_transition)
{
	EXPECT_CALL(standing, transition())
		.WillOnce(Return(&ducking));

	fsm->add_state(&standing);
	fsm->add_state(&ducking);
	fsm->update();
	ASSERT_EQ(fsm->get_current_state(), &ducking);

	EXPECT_CALL(ducking, transition())
		.WillOnce(Return(&ducking));
	fsm->update();
	ASSERT_EQ(fsm->get_current_state(), &ducking);
	
	EXPECT_CALL(ducking, transition())
		.WillOnce(Return(&standing));
	fsm->update();
	ASSERT_EQ(fsm->get_current_state(), &standing);
}