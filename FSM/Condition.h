#pragma once
#include "DataStorage.h"
#include "Serialize.h"
#include <memory>
#include <unordered_map>
#include <vector>
using std::string;
using FSM::DataStorage;
using FSM::DataType;
using std::vector;
using std::unordered_map;
using std::unique_ptr;

typedef vector<string> ClassArgs;

namespace FSM
{
	/**
	@brief enum stating the comparison operation to perform
	*/
	
	enum class Operation
	{
		EQUAL = 0,
		GREATHER,
		LESS,
		GREATHEREQUAL,
		LESSEQUAL,

	};

	
	const unordered_map< Operation, string> OperationMap
	{
		{ Operation::EQUAL,			"equal"},
		{ Operation::GREATHER,		"greather"},
		{ Operation::LESS,			"less"},
		{ Operation::GREATHEREQUAL, "greaterequal"},
		{ Operation::EQUAL,			"lessequal"}
	};
	/**
	@brief, base class for all the condition classes
	A condition class encapsulate a comparison between two values,
	this class is used as a poliformic base used inside the state machine.
	*/
	class Condition
	{
	public:
		/**
		@brief constructor
		@param data: Pointer to a data storage class, the condition
					 will use it internally to query the value and 
					 evaluate the condition.
		*/
		Condition(DataStorage * data) : m_data(data) {}
		/**
		Pure virtual function returning the result of the condition
		*/
		virtual bool evaluate() = 0;
		virtual const string serialize() const =0;
		virtual ~Condition() = default;

	protected:
		//pointer to the data storage
		DataStorage * m_data;

	};

	/**
	@brief implements evaluatoin between two different keys	
	The comparison operation will be triggered between the two provided
	key, both keys resides in the data storage, aka two variables
	*/
	template <typename T>
	class DoubleVarCondition : public Condition
	{
	public:
		/**
		@brief Constructor
		@param data: pointer to the data storage
		@param key_1_name: the name of the first key of the condition
		@param key_2_name: the name of the second key of the condition
		@param op: the operation we want to perform, greather , equal etc
		*/
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

		/**
		@briefThis function evaluates the condition and returns wheter
		is true or not
		@returns bool, the result of the condition
		*/
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


		virtual const string serialize() const override
		{
			auto t = typeid(T).name();
			string s = (FSM::Serialize::OPEN_TAG + m_class_name);
			s += "<";
			s += t;
			s += ">";
			s += FSM::Serialize::TYPE_SEP;
			s += m_key_1_name;
			s += " , ";
			s += m_key_2_name;
			s += " , ";
			s += OperationMap.find(m_op)->second;
			s += FSM::Serialize::CLOSE_TAG;

			return s;
		}

		static unique_ptr<Condition> de_serialize(DataStorage* dt, 
												  ClassArgs& args)
		{
			unique_ptr<Condition> ptr = std::make_unique<DoubleVarCondition<T>>( dt,
																args[0],
																args[1],
																Operation::EQUAL);
			return ptr;
		}
		/**
		@brief getter function for the first key value
		@returns T value of the key
		*/
		inline T get_value_1()
		{
			m_data->get_value(m_key_1_name, m_key_1_value);
			return m_key_1_value;
		}

		/**
		@brief getter function for the second key value
		@returns T value of the key
		*/
		inline T get_value_2()
		{
			m_data->get_value(m_key_2_name, m_key_2_value);
			return m_key_2_value;
		}


	private:
		/*
		Private method for updating both key values
		*/
		inline void __update_values()
		{
			m_data->get_value(m_key_1_name, m_key_1_value);
			m_data->get_value(m_key_2_name, m_key_2_value);
		}

	public :
		static const string m_class_name;
	private:
		//the two key value storages when evaluated
		T m_key_1_value;
		T m_key_2_value;
		//storage for the two key names
		string m_key_1_name;
		string m_key_2_name;
		//storage for the operation type
		Operation m_op;

	};
	template <typename T>
	const string DoubleVarCondition<T>::m_class_name("DoubleVarCondition");

	/**
	@brief implements evaluation between a key and a static value 
	*/
	template <typename T>
	class TypedCondition: public Condition
	{
	public:
	
		/**
		@brief Constructor
		@param data: pointer to the data storage	
		@param key_name: the name of the first key of the condition
		@param compare_to_value: the value we want to compair against
		@param op: the operation we want to perform, greather , equal etc
		*/
		TypedCondition(DataStorage * data,
			string key_name,
			T compare_to_value,
			Operation op) :
			Condition(data),
			m_key_name(key_name),
			m_compare_to_value(compare_to_value),
			m_op(op)
		{ };
		/**
		Destructor
		*/
		virtual ~TypedCondition() = default;

		/**
		Getter function for the key value
		@returns: the T value for the key 
		*/
		inline T get_value()
		{
			m_data->get_value(m_key_name, m_key_value);
			return m_key_value;
		}

		/**
		@briefThis function evaluates the condition and returns wheter
		is true or not
		@returns bool, the result of the condition
		*/
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
		
		virtual const string serialize() const override 
		{
			auto t = typeid(T).name();
			string s = (FSM::Serialize::OPEN_TAG + m_class_name);
			s += "<";
			s += t;
			s += ">";
			s += FSM::Serialize::TYPE_SEP ;
			s += m_key_name;
			s += Serialize::ARGS_SEP;
			s += Serialize::number_to_string<T>(m_compare_to_value);
			s += Serialize::ARGS_SEP;
			s += OperationMap.find(m_op)->second;
			s += FSM::Serialize::CLOSE_TAG;
				
			return s;
		}
	
	private:
		static const string m_class_name;
		//storage for the key value
		T m_key_value;
		//storage for the key nane
		string m_key_name;
		//storage for the comparison value
		T m_compare_to_value;
		//storage for the operation
		Operation m_op;
	};
	
	template <typename T>
	const string TypedCondition<T>::m_class_name("TypedCondition");
}
//keeping this around just because I am curious to see 
//if the compiler is able to optimize the branches out
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
