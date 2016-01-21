#pragma once
#include <string>
#include "DataStorage.h"
using std::string;
using FSM::DataStorage;
using FSM::DataType;


namespace FSM
{
	enum class Operation
	{
		EQUAL = 0,
		GREATHER,
		LESS,
		GREATHEREQUAL,
		LESSEQUAL,

	};

	class Condition
	{
	public:
		Condition(DataStorage * data) : m_data(data) {}
		virtual bool evaluate() = 0;
		virtual ~Condition() = default;

	protected:
		DataStorage * m_data;

	};


	template <typename T>
	class DoubleVarCondition: public Condition
	{
	public:

		DoubleVarCondition(DataStorage * data,
			string& key_1_name,
			string& key_2_name,
			Operation op) :
			Condition(data),
			m_key_1_name(key_1_name),
			m_key_2_name(key_2_name),
			m_op(op)
		{ };
		virtual ~DoubleVarCondition() = default;

		bool evaluate() override
		{
			__update_values();
			switch (m_op)
			{
			case Operation::EQUAL:
			{ return m_key_1_value == m_key_2_value; }
			case Operation::GREATHER:
			{ return m_key_1_value > m_key_2_value; }
			case Operation::LESS:
			{ return m_key_1_value < m_key_2_value; }
			case Operation::GREATHEREQUAL:
			{ return m_key_1_value >= m_key_2_value; }
			case Operation::LESSEQUAL:
			{ return m_key_1_value <= m_key_2_value; }
			default:
			{return true; }
			}
		}

		inline T get_value_1()
		{
			m_data->get_value(m_key_1_name, m_key_1_value);
			return m_key_1_value;
		}

		inline T get_value_2()
		{
			m_data->get_value(m_key_2_name, m_key_2_value);
			return m_key_2_value;
		}


	private:
		inline void __update_values()
		{
			m_data->get_value(m_key_1_name, m_key_1_value);
			m_data->get_value(m_key_2_name, m_key_2_value);
		}
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
		T m_key_2_value;
		string m_key_1_name;
		string m_key_2_name;
		Operation m_op;

	};
	
	template <typename T>
	class TypedCondition: public Condition
	{
	public:
	
		TypedCondition(DataStorage * data,
			string& key_name,
			T compare_to_value,
			Operation op) :
			Condition(data),
			m_key_name(key_name),
			m_compare_to_value(m_compare_to_value),
			m_op(op)
		{ };
		virtual ~TypedCondition() = default;

		inline T get_value()
		{
			m_data->get_value(m_key_name, m_key_value);
			return m_key_value;
		}
		bool evaluate() override
		{
			m_data->get_value(m_key_name, m_key_value);
			switch (m_op)
			{
			case Operation::EQUAL:
			{ return m_key_value == m_compare_to_value; }
			case Operation::GREATHER:
			{ return m_key_value > m_compare_to_value; }
			case Operation::LESS:
			{ return m_key_value < m_compare_to_value; }
			case Operation::GREATHEREQUAL:
			{ return m_key_value >= m_compare_to_value; }
			case Operation::LESSEQUAL:
			{ return m_key_value <= m_compare_to_value; }
			default:
			{return true; }
			}
		}
	private:
		T m_key_value;
		string m_key_name;
		T m_compare_to_value;
		Operation m_op;
	};
}