#include <gmock/gmock.h> 
#include <fstream>
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


struct fsmIntegrationFixture: public Test
{
	FSM::DataStorage dt;
	unique_ptr<FiniteStateMachine> fsm;

	GenericState ducking;
	GenericState standing;
	GenericState jumping;
	GenericState diving;
	
	unique_ptr<TypedCondition<bool>>is_ducking;
	unique_ptr<TypedCondition<bool>>is_standing;
	unique_ptr<TypedCondition<bool>>is_jumping;
	unique_ptr<TypedCondition<bool>>is_diving;
	

	unique_ptr<Connection>ducking_standing;
	unique_ptr<Connection>standing_ducking;
	unique_ptr<Connection>standing_jumping;
	unique_ptr<Connection>jumping_diving;
	
	fsmIntegrationFixture(): 
					ducking("ducking"),
					standing("standing"),
					jumping("jumping"),
					diving("diving")
	{}

	virtual void SetUp() override
	{
		//make fsm
		fsm = std::make_unique<FiniteStateMachine>("fsm", &dt);

		//make  conditions
		is_ducking= std::make_unique<TypedCondition<bool>>(&dt,
			"ducking",
			true,
			Operation::EQUAL);
			
		is_standing= std::make_unique<TypedCondition<bool>>(&dt,
			"standing",
			true,
			Operation::EQUAL);
		
		is_jumping= std::make_unique<TypedCondition<bool>>(&dt,
			"jumping",
			true,
			Operation::EQUAL);
		
		is_diving= std::make_unique<TypedCondition<bool>>(&dt,
			"diving",
			true,
			Operation::EQUAL);
		
		//make connections 
		ducking_standing = std::make_unique<Connection>(&ducking,
			&standing);

		standing_ducking= std::make_unique<Connection>(&standing,
			&ducking);
		
		standing_jumping= std::make_unique<Connection>(&standing,
			&jumping);

		jumping_diving= std::make_unique<Connection>(&jumping,
			&diving);

		//populate connections
		ducking_standing->add_condition(is_standing.get());
		standing_ducking->add_condition(is_ducking.get());
		standing_jumping->add_condition(is_jumping.get());
		//jumping_diving->add_condition(is_jumping.get());
		jumping_diving->add_condition(is_diving.get());

		//populate states
		ducking.add_connection(ducking_standing.get());
		standing.add_connection(standing_ducking.get());
		standing.add_connection(standing_jumping.get());
		jumping.add_connection(jumping_diving.get());

		//populate fsm
		fsm->add_state(&standing);
		fsm->add_state(&ducking);
		fsm->add_state(&jumping);
		fsm->add_state(&diving);
	}
};


TEST_F(fsmIntegrationFixture, to_ducking_transition)
{
	dt.set_value("ducking", true);
	fsm->update();
	ASSERT_EQ(fsm->get_current_state(), &ducking);

}

TEST_F(fsmIntegrationFixture, ducking_standing_transition)
{
	dt.set_value("ducking", true);
	fsm->update();
	ASSERT_EQ(fsm->get_current_state(), &ducking);
	dt.set_value("ducking", false);
	dt.set_value("standing", true);
	fsm->update();
	ASSERT_EQ(fsm->get_current_state(), &standing);
}

TEST_F(fsmIntegrationFixture, jumping_transition)
{
	dt.set_value("jumping", true);
	dt.set_value("ducking", false);
	fsm->update();
	ASSERT_EQ(fsm->get_current_state(), &jumping);
}

TEST_F(fsmIntegrationFixture, diving_transition)
{
	dt.set_value("jumping", true);
	fsm->update();
	dt.set_value("diving", true);
	fsm->update();
	ASSERT_EQ(fsm->get_current_state(), &diving);
}

TEST_F(fsmIntegrationFixture, complex_serialization)
{
	dt.set_value("ducking", true);
	fsm->update();
	dt.set_value("standing", true);
	dt.set_value("ducking", true);
	fsm->update();
	ASSERT_EQ(fsm->get_current_state(), &standing);
	dt.set_value("jumping", true);
	dt.set_value("standing", false);
	dt.set_value("ducking", false);
	fsm->update();
	ASSERT_EQ(fsm->get_current_state(), &jumping);
	dt.set_value("jumping", true);
	dt.set_value("diving", true);
	fsm->update();
	ASSERT_EQ(fsm->get_current_state(), &diving);
}

TEST_F(fsmIntegrationFixture, complex_iterations)
{
	string check = fsm->serialize();
	//std::cout << check << std::endl;
	
	//under visual studio path is set relative to the root might
	//need to find a better way to have relative path to the test file
	std::ifstream t("../FSMTests/data/serialized1.txt");
	std::stringstream buffer;
	buffer << t.rdbuf();
	string expected = buffer.str();
	ASSERT_EQ(check, expected);
}
