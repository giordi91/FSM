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

	auto condc = (FSM::DoubleVarCondition<int>*)cond;
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