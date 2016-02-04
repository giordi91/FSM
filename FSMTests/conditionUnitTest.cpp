
#include <gmock/gmock.h> 
#include <string>
#include "Condition.h"
#include "DeSerialize.h"
using namespace testing;
using FSM::DoubleVarCondition;
using FSM::TypedCondition;
using FSM::DataType;
using FSM::Operation;

TEST(double_var_condition_test, float_testing)
{
	DataStorage tmp;
	string k1 = "x";
	string k2 = "y";
	tmp.set_value(k1, 10.0f);
	tmp.set_value(k2, 20.12f);
	DoubleVarCondition<float> cond(&tmp,k1, k2, Operation::GREATHER);
	ASSERT_EQ(cond.evaluate(), false);


	tmp.set_value(k1, 2.2f);
	tmp.set_value(k2, 0.2f);
	DoubleVarCondition<float> cond2(&tmp,k1, k2, Operation::LESS);
	ASSERT_EQ(cond2.evaluate(), false);
	
	tmp.set_value(k1, -0.2f);
	tmp.set_value(k2, 999.2f);
	DoubleVarCondition<float> cond3(&tmp,k1, k2, Operation::EQUAL);
	ASSERT_EQ(cond3.evaluate(), false);
	
	tmp.set_value(k1, 13.2f);
	tmp.set_value(k2, 13.0f);
	DoubleVarCondition<float> cond4(&tmp,k1, k2, Operation::EQUAL);
	DoubleVarCondition<float> cond5(&tmp,k1, k2, Operation::GREATHEREQUAL);
	DoubleVarCondition<float> cond6(&tmp,k1, k2, Operation::LESSEQUAL);
	ASSERT_EQ(cond4.evaluate(), false);
	ASSERT_EQ(cond5.evaluate(), true);
	ASSERT_EQ(cond6.evaluate(), false);
}



TEST(double_var_condition_test, mixed)
{
	DataStorage tmp;
	string k1 = "x";
	string k2 = "y";
	tmp.set_value(k1, 10.0f);
	tmp.set_value(k2, 20.0f);
	DoubleVarCondition<float> cond(&tmp,k1, k2, Operation::GREATHER);
	ASSERT_EQ(cond.evaluate(), false);


	tmp.set_value(k1, 0);
	tmp.set_value(k2, 0);
	DoubleVarCondition<int> cond2(&tmp,k1, k2, Operation::EQUAL);
	DoubleVarCondition<int> cond3(&tmp,k1, k2, Operation::LESS);
	ASSERT_EQ(cond2.evaluate(), true);
	ASSERT_EQ(cond3.evaluate(), false);
}

TEST(DoubleVarCondition, serialization)
{

	DataStorage tmp;
	string k1 = "x";
	string k2 = "y";
	DoubleVarCondition<float> cond(&tmp,k1, k2, Operation::GREATHER);
	string cond_str=  cond.serialize() ;
	string to_check("<< DoubleVarCondition<float> ### x , y , 1 >>");
	ASSERT_EQ(cond_str, to_check);
	
	 k1 = "jump";
	 k2 = "air_time";
	DoubleVarCondition<float> cond2(&tmp,k1, k2, Operation::GREATHER);
	cond_str=  cond2.serialize() ;
	to_check = ("<< DoubleVarCondition<float> ### jump , air_time , 1 >>");
	ASSERT_EQ(cond_str, to_check);
	
	 k1 = "swim";
	 k2 = "down";
	DoubleVarCondition<bool> cond3(&tmp,k1, k2, Operation::EQUAL);
	cond_str=  cond3.serialize() ;
	to_check = ("<< DoubleVarCondition<bool> ### swim , down , 0 >>");
	ASSERT_EQ(cond_str, to_check);
}

TEST(DoubleVarCondition, deserialization)
{
	string temp = "<< DoubleVarCondition<bool> ### ducking , swim , 0 >>";
	DataStorage* dt = nullptr;
	auto args = FSM::Serialize::extract_args(temp);
	auto cond  = DoubleVarCondition<bool>::de_serialize(dt,args);
	auto cond_pt = static_cast<DoubleVarCondition<bool>*>(cond.get());

	ASSERT_EQ(cond_pt->get_operation(), Operation::EQUAL);
	ASSERT_EQ(cond_pt->get_key_name_1(), string("ducking"));
	ASSERT_EQ(cond_pt->get_key_name_2(), string("swim"));
	
	temp = "<< DoubleVarCondition<int> ### lolling , crapping , 2 >>";
	args = FSM::Serialize::extract_args(temp);
	cond  = DoubleVarCondition<int>::de_serialize(dt,args);
	auto cond_pt2 = static_cast<DoubleVarCondition<int>*>(cond.get());

	ASSERT_EQ(cond_pt2->get_operation(), Operation::LESS);
	ASSERT_EQ(cond_pt2->get_key_name_1(), string("lolling"));
	ASSERT_EQ(cond_pt2->get_key_name_2(), string("crapping"));
}

TEST(typed_condition_test, bool_testing)
{
	DataStorage tmp;
	string k1 = "x";
	string k2 = "y";
	tmp.set_value(k1, false);
	tmp.set_value(k2, true);
	TypedCondition<bool> cond(&tmp,k1, true, Operation::EQUAL);
	ASSERT_EQ(cond.evaluate(), false);
	
	tmp.set_value(k1, true);
	TypedCondition<bool> cond2(&tmp,k1, true, Operation::EQUAL);
	ASSERT_EQ(cond2.evaluate(), true);
}


TEST(typed_condition_test, serialization)
{

	DataStorage tmp;
	string k1 = "x";
	string k2 = "y";
	TypedCondition<float> cond(&tmp, k1, 1.0f, Operation::GREATHER);
	string cond_str = cond.serialize();
	string to_check("<< TypedCondition<float> ### x , 1.00000 , 1 >>");
	ASSERT_EQ(cond_str, to_check);
	
	k1 = "jump";
	TypedCondition<bool> cond2(&tmp, k1, false , Operation::EQUAL);
	cond_str = cond2.serialize();
	to_check=("<< TypedCondition<bool> ### jump , 0 , 0 >>");
	ASSERT_EQ(cond_str, to_check);
}
TEST(typed_condition_test, deserialization)
{
	string temp = "<< TypedCondition<bool> ### ducking , 1 , 0 >>";
	DataStorage* dt = nullptr;
	auto args = FSM::Serialize::extract_args(temp);
	auto cond  = TypedCondition<bool>::de_serialize(dt,args);
	auto cond_pt = static_cast<TypedCondition<bool>*>(cond.get());
	ASSERT_EQ(cond_pt->get_operation(), Operation::EQUAL);
	ASSERT_EQ(cond_pt->get_key_name(), string("ducking"));
	ASSERT_EQ(cond_pt->get_compare_value(), true);

	temp = "<< TypedCondition<int> ### lolling , 12 , 2 >>";
	args = FSM::Serialize::extract_args(temp);
	cond  = TypedCondition<int>::de_serialize(dt,args);
	auto cond_pt2 = static_cast<TypedCondition<int>*>(cond.get());

	ASSERT_EQ(cond_pt2->get_operation(), Operation::LESS);
	ASSERT_EQ(cond_pt2->get_key_name(), string("lolling"));
	ASSERT_EQ(cond_pt2->get_compare_value(), 12 );
	
	temp = "<< TypedCondition<int> ### testing , 0 , 1 >>";
	args = FSM::Serialize::extract_args(temp);
	cond  = TypedCondition<bool>::de_serialize(dt,args);
	auto cond_pt3 = static_cast<TypedCondition<bool>*>(cond.get());

	ASSERT_EQ(cond_pt3->get_operation(), Operation::GREATHER);
	ASSERT_EQ(cond_pt3->get_key_name(), string("testing"));
	ASSERT_EQ(cond_pt3->get_compare_value(), false );

}
