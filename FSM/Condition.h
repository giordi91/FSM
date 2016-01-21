#pragma once
#include <string>
#include "DataStorage.h"
using std::string;
using FSM::DataStorage;
using FSM::DataType;

enum class Operation
{
	GREATHER=0,
	LESS,
	EUQUAL,
	GREATHEREQUAL,
	LESSEQUAL,

};

class Condition
{
public:
	Condition( DataStorage * data);
	virtual bool evaluate() = 0;
	virtual ~Condition()=default;

protected:
	DataStorage * m_data;

};


template <typename T,typename R>
class TypedCondition: public Condition
{
public :

	TypedCondition(DataStorage * data,
				   string& key_1_name,
				   string& key_2_name): 
				   Condition(data),
				   m_key_1_name(key_1_name),
				   m_key_2_name(key_2_name)
	{ };
	virtual ~TypedCondition()=default;
	
	bool evaluate() override
	{
		return (get_value_1() > get_value_2());
	}

	inline T get_value_1()
	{
		m_data->get_value(m_key_1_name, m_key_1_value);
		return m_key_1_value;
	}

	inline R get_value_2()
	{
		m_data->get_value(m_key_2_name, m_key_2_value);
		return m_key_2_value;
	}
private:
	
	/*
	template<typename X>
	inline void __check_key_type(DataType& type)
	{
		if (typeid(X) == typeid(bool))
		{
			type = DataType::BOOL;
		}
		else if (typeid(X) == typeid(int))
		{
			type = DataType::INT;
		}
		else if (typeid(X) == typeid(float))
		{
			type = DataType::FLOAT;
		}
		else
		{
			type = DataType::BOOL;
		}
	}
	*/

private:
	T m_key_1_value;
	R m_key_2_value;
	string m_key_1_name;
	string m_key_2_name;

};
