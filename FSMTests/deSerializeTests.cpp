#include <gmock/gmock.h> 
#include <string>
#include "DeSerialize.h"
using namespace testing;


TEST(deserialize, conditions_type)
{
	string temp = "<< TypedCondition<bool> ### ducking , 1 , 0 >>";
	string t = FSM::Serialize::extract_type(temp);
	ASSERT_EQ(t , "TypedCondition<bool>");

	string crap = "sjfslfjslj";
	t = FSM::Serialize::extract_type(crap);
	ASSERT_EQ(t , "");
	
	temp = "<< DoubleVarCondition<int> ### ducking , 1 , 0 >>";
	t = FSM::Serialize::extract_type(temp);
	ASSERT_EQ(t , "DoubleVarCondition<int>");
}

TEST(deserialize, conditions_args)
{
	string temp = "<< TypedCondition<bool> ### ducking , 1 , 0 >>";
	ClassArgs found = FSM::Serialize::extract_args(temp);
	ClassArgs expected = { "ducking","1","0" };
	
	ASSERT_EQ(found, expected);
	//wrong on purpose just checking if finds all
	temp = "<< DoubleVarCondition<int> ### swimming , false, running , 0 >>";
	found = FSM::Serialize::extract_args(temp);
	expected = { "swimming","false","running", "0" };
	ASSERT_EQ(expected, found);
	
	temp = "<< DoubleVarCondition<int> ### jumping , running , 2 >>";
	found = FSM::Serialize::extract_args(temp);
	expected = { "jumping","running","2" };
	ASSERT_EQ(expected, found);

	string crap = "sjfslfjslj";
	found = FSM::Serialize::extract_args(crap);
	expected = {};
	ASSERT_EQ(found , expected);



	temp = "<< TypedCondition<float> ### lacking , 1.32345 , 2 >>";
	found = FSM::Serialize::extract_args(temp);
	
	std::smatch type_match;
	std::regex_search(temp, type_match, FSM::Serialize::REG_ARGS_EXTRACTOR);
	string res= type_match[0];
	expected = {"lacking", "1.32345", "2"};
	ASSERT_EQ(found , expected);
}
