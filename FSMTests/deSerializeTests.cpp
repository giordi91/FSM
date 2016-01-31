#include <gmock/gmock.h> 
#include <string>
#include "DeSerialize.h"
using namespace testing;


TEST(deserialize, conditions_type)
{
	string temp = "<< TypedCondition<bool> ### ducking , 1 , equal >>";
	string t = FSM::Serialize::extract_type(temp);
	ASSERT_EQ(t , "TypedCondition<bool>");

	string crap = "sjfslfjslj";
	t = FSM::Serialize::extract_type(crap);
	ASSERT_EQ(t , "");
	
	temp = "<< DoubleVarCondition<int> ### ducking , 1 , equal >>";
	t = FSM::Serialize::extract_type(temp);
	ASSERT_EQ(t , "DoubleVarCondition<int>");
}

TEST(deserialize, conditions_args)
{
	string temp = "<< TypedCondition<bool> ### ducking , 1 , equal >>";
	ClassArgs found = FSM::Serialize::extract_args(temp);
	ClassArgs expected = { "ducking","1","equal" };
	
	ASSERT_EQ(found, expected);
	//wrong on purpose just checking if finds all
	temp = "<< DoubleVarCondition<int> ### swimming, false, running , equal >>";
	found = FSM::Serialize::extract_args(temp);
	expected = { "swimming","false","running", "equal" };
	ASSERT_EQ(expected, found);
	
	temp = "<< DoubleVarCondition<int> ### jumping, running , less >>";
	found = FSM::Serialize::extract_args(temp);
	expected = { "jumping","running","less" };
	ASSERT_EQ(expected, found);

	string crap = "sjfslfjslj";
	found = FSM::Serialize::extract_args(crap);
	expected = {};
	ASSERT_EQ(found , expected);
	
}
