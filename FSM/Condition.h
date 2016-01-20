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
class TypedCondition
{
public :

	TypedCondition(DataStorage * data)
	{
		__check_key_type<T>(m_key_type_1);
		__check_key_type<R>(m_key_type_2);
	};
	virtual ~TypedCondition()=default;
	inline DataType get_key_1_type() const
	{
		return m_key_type_1;
	}

	inline DataType get_key_2_type() const
	{
		return m_key_type_2;
	}

private:
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

private:

	DataType m_key_type_1;
	DataType m_key_type_2;
};

