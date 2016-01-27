#include <gmock/gmock.h> 
#include <string>
#include <memory>
#include "State.h"
#include "FSM.h"
#include "fixtures.h"
using namespace testing;
using FSM::GenericState;
using FSM::FiniteStateMachine;
using std::unique_ptr;




struct fsmStateFixture: public Test
{
	FSM::DataStorage dt;
	unique_ptr<FiniteStateMachine> fsm;

	MockState ducking;
	MockState standing;
	GenericState jumping;
	GenericState diving;

	
	fsmStateFixture(): 
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

TEST_F(fsmStateFixture, assert_no_curr_state)
{
	ASSERT_EQ(fsm->get_states_count(), 0);
	ASSERT_EQ(fsm->get_current_state(), nullptr);
	ASSERT_EQ(fsm->get_current_state_name(), "");
}

TEST_F(fsmStateFixture, assert_state_current_after_insertion)
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

TEST_F(fsmStateFixture, simple_state_transition)
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