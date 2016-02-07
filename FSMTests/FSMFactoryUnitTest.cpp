#include <gmock/gmock.h> 
#include <string>
#include "DeSerialize.h"
#include "FSMFactory.h"
using namespace testing;


TEST(factory, full_double_var_condition)
{
	string temp = "<< DoubleVarCondition<bool> ### ducking , jumping , 0 >>";
	FSM::FSMFactory fact;
	auto dt = fact.get_data_storage();
	dt->set_value("ducking", true);
	dt->set_value("jumping", true);
	Condition * cond = fact.generate_condtition(temp);

	ASSERT_EQ(cond->evaluate(), true);
	dt->set_value("ducking", false);
	ASSERT_EQ(cond->evaluate(), false);

	temp = "<< DoubleVarCondition<int> ### swing , ball , 2 >>";
	cond = fact.generate_condtition(temp);
	dt->set_value("swing", 11);
	dt->set_value("ball", 23);

	auto condc = (FSM::DoubleVarCondition<int>*)cond;
	ASSERT_EQ(cond->evaluate(), true);

	dt->set_value("swing", 441);
	dt->set_value("ball", 23);
	ASSERT_EQ(cond->evaluate(), false);
}

TEST(factory, assert_null_double_condition)
{
	string t;
	FSM::FSMFactory fact;
	Condition * cond = fact.generate_condtition(t);
	ASSERT_EQ(cond, nullptr);
	
	t= "<< DoubleVarCondition<char> ### ducking , jumping , 0 >>";
	cond = fact.generate_condtition(t);
	ASSERT_EQ(cond, nullptr);
}

TEST(factory, full_typed_var_condition)
{
	string temp = "<< TypedCondition<bool> ### hacking , 0 , 0 >>";
	FSM::FSMFactory fact;
	auto dt = fact.get_data_storage();
	dt->set_value("hacking", false);
	Condition * cond = fact.generate_condtition(temp);

	ASSERT_EQ(cond->evaluate(), true);
	dt->set_value("hacking", true);
	ASSERT_EQ(cond->evaluate(), false);

	temp = "<< TypedCondition<float> ### lacking , 1.32345 , 2 >>";
	cond = fact.generate_condtition(temp);
	dt->set_value("lacking", 12.2f);
	ASSERT_EQ(cond->evaluate(), false);

	dt->set_value("lacking", 0.12012f);
	ASSERT_EQ(cond->evaluate(), true);
}

TEST(factory, assert_null_typed_condition)
{
	FSM::FSMFactory fact;
	string t= "<< TypedCondition<char> ### ducking , jumping , 0 >>";
	auto cond = fact.generate_condtition(t);
	ASSERT_EQ(cond, nullptr);
}

TEST(factory, get_not_existing_states)
{
	FSM::FSMFactory fact;
	FSM::State * s = fact.get_state("swimming");
	FSM::State * s1 = fact.get_state("jumping");
	FSM::State * s2 = fact.get_state("rotating");
	FSM::State * s3 = fact.get_state("swimming");

	ASSERT_EQ(s->get_name(), "swimming");
	ASSERT_EQ(s1->get_name(), "jumping");
	ASSERT_EQ(s2->get_name(), "rotating");
	ASSERT_EQ(s3->get_name(), "swimming");
	ASSERT_EQ(s3, s);
}


TEST(factory, generate_connection)
{
	FSM::FSMFactory fact;
	string conn = "<< Connection ### standing , ducking >>";
	string cond1 ="<< TypedCondition<bool> ### ducking , 1 , 0 >>";
	string cond2= "<< DoubleVarCondition<bool> ### ducking , jumping , 0 >>";

	DataStorage *dt = fact.get_data_storage();
	dt->set_value("ducking", true);
	dt->set_value("jumping", true);

	std::vector < string > data;
	data.push_back(conn);
	data.push_back(cond1);
	data.push_back(cond2);
	auto connection = fact.generate_connection(data);

	ASSERT_EQ(connection->evaluate(), true);

}
	
TEST(factory, generate_state)
{
	FSM::FSMFactory fact;
	string state = "<< GenericState ### standing >>";
	string conn = "<< Connection ### standing , ducking >>";
	string cond1 = "<< TypedCondition<bool> ### ducking , 1 , 0 >>";
	string cond2 = "<< DoubleVarCondition<bool> ### ducking , jumping , 0 >>";
	

	std::vector < string > data;
	data.push_back(conn);
	data.push_back(cond1);
	data.push_back(cond2);

	DataStorage *dt = fact.get_data_storage();
	dt->set_value("ducking", true);
	dt->set_value("jumping", true);
	
	std::vector<vector<string>> compound;
	compound.push_back(data);

	FSM::State * s = fact.generate_state(state, compound);

	FSM::State * destination = fact.get_state("ducking");

	FSM::State * after_transitoin = s->transition();

	ASSERT_EQ(destination, after_transitoin);
	

}

TEST(factory, generate_fsm_from_file)
{
	string path = "../FSMTests/data/serialized1.txt";
	FSM::FSMFactory fact;
	auto fsm = fact.generate_fsm_from_file(path);
	auto& dt = *(fact.get_data_storage());
	auto standing = fact.get_state("standing");
	auto jumping = fact.get_state("jumping");
	auto diving = fact.get_state("diving");

	dt.set_value("ducking", true);
	fsm->update();
	dt.set_value("standing", true);
	dt.set_value("ducking", true);
	fsm->update();
	ASSERT_EQ(fsm->get_current_state(), standing);
	dt.set_value("jumping", true);
	dt.set_value("standing", false);
	dt.set_value("ducking", false);
	fsm->update();

	ASSERT_EQ(fsm->get_current_state(), jumping);
	dt.set_value("jumping", true);
	dt.set_value("diving", true);
	fsm->update();
	ASSERT_EQ(fsm->get_current_state(), diving);
}