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
using FSM::State;
using std::unique_ptr;
using FSM::FiniteStateMachine;

struct fsmCreation: public Test
{
	FSM::DataStorage dt;
	unique_ptr<FiniteStateMachine> fsm;

	State ducking;
	State standing;
	State jumping;
	State diving;

	unique_ptr<TypedCondition<bool>> tp1;
	unique_ptr<TypedCondition<float>> tp2;
	unique_ptr<DoubleVarCondition<float>> dv1;
	unique_ptr<DoubleVarCondition<int>> dv2;
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
