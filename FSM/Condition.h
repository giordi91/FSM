#pragma once
#include "DataStorage.h"
#include "Serialize.h"
#include <memory>
#include <unordered_map>
#include <vector>
#include <type_traits>

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
	
	/**
	@brief, base class for all the condition classes
	A condition class encapsulate a comparison between two values,
	this class is used as a poliformic base used inside the state machine.
	*/
	class 	Condition
	{
	public:
		/**
		@brief constructor
		@param data: Pointer to a data storage class, the condition
					 will use it internally to query the value and 
					 evaluate the condition.
		*/
		Condition(DataStorage * data, Operation op) : m_data(data), m_op(op) {}
		/**
		Pure virtual function returning the result of the condition
		*/
		virtual bool evaluate() = 0;
		virtual const string serialize() const =0;
		virtual ~Condition() = default;

		/**
		@brief getter function for operation, mainly debug purpose 
		@returns Operation 
		*/
		inline Operation get_operation()
		{
			return m_op;
		}

		inline void set_operation( Operation op)
		{
			m_op = op;
		}
	protected:
		//pointer to the data storage
		DataStorage * m_data;
		Operation m_op;

	};

	/**
	@brief implements evaluatoin between two different keys	
	The comparison operation will be triggered between the two provided
	key, both keys resides in the data storage, aka two variables
	*/
	template<typename T  >
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
		__declspec(dllexport)
		DoubleVarCondition(DataStorage * data,
			string& key_1_name,
			string& key_2_name,
			Operation op) :
			Condition(data, op),
			m_key_1_name(key_1_name),
			m_key_2_name(key_2_name)
			{ };
		virtual ~DoubleVarCondition() = default;

		/**
		@briefThis function evaluates the condition and returns wheter
		is true or not
		@returns bool, the result of the condition
		*/
		__declspec(dllexport)
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
			s += Serialize::number_to_string<int>(static_cast<int>(m_op));
			s += FSM::Serialize::CLOSE_TAG;

			return s;
		}

		static unique_ptr<Condition> de_serialize(DataStorage* dt, 
												  ClassArgs& args)
		{
			
			int op_int = std::stoi(args[2]);
			Operation op = static_cast<Operation>(op_int);
			unique_ptr<Condition> ptr = std::make_unique<DoubleVarCondition<T>>( dt,
																args[0],
																args[1],
																op);
			return ptr;
		}
		/**
		@brief getter function for the first key value
		@returns T value of the key
		*/
		__declspec(dllexport)
		inline T get_value_1()
		{
			m_data->get_value(m_key_1_name, m_key_1_value);
			return m_key_1_value;
		}

		/**
		@brief getter function for the second key value
		@returns T value of the key
		*/
		__declspec(dllexport)
		inline T get_value_2()
		{
			m_data->get_value(m_key_2_name, m_key_2_value);
			return m_key_2_value;
		}

		__declspec(dllexport)
		inline const string& get_key_name_1() const
		{
			return m_key_1_name;
		}
		
		__declspec(dllexport)
		inline const string& get_key_name_2() const
		{
			return m_key_2_name;
		}
		__declspec(dllexport)
		inline void set_key_name_1( string& name)
		{
			m_key_1_name = name;
		}

		__declspec(dllexport)
		inline void set_key_name_2( string& name)
		{
			m_key_2_name = name;
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

	};

	//template < typename T,
	//	typename = std::enable_if<std::is_arithmetic<T>::value, T>::type
	//>
	template<typename T>
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
		__declspec(dllexport)
		TypedCondition(DataStorage * data,
			string key_name,
			T compare_to_value,
			Operation op) :
			Condition(data, op),
			m_key_name(key_name),
			m_compare_to_value(compare_to_value)
			{ };
		/**
		Destructor
		*/
		virtual ~TypedCondition() = default;

		/**
		Getter function for the key value
		@returns: the T value for the key 
		*/
		__declspec(dllexport)
		inline T get_value()
		{
			m_data->get_value(m_key_name, m_key_value);
			return m_key_value;
		}
		__declspec(dllexport)
		inline const string& get_key_name() const
		{
			return m_key_name;
		}

		__declspec(dllexport)
		inline const T get_compare_value() const
		{
			return m_compare_to_value;
		
		}
		
		__declspec(dllexport)
		inline void set_compare_value( T  value) 
		{
			m_compare_to_value = value;
		}

		__declspec(dllexport)
		inline void set_key_name( string  value) 
		{
			m_key_name= value;
		}

		/**
		@briefThis function evaluates the condition and returns wheter
		is true or not
		@returns bool, the result of the condition
		*/
		__declspec(dllexport)
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
			s += Serialize::number_to_string<int>(static_cast<int>(m_op));
			s += FSM::Serialize::CLOSE_TAG;
				
			return s;
		}
	
		static unique_ptr<Condition> de_serialize(DataStorage* dt, 
												  ClassArgs& args)
		{
			int op_int = std::stoi(args[2]);
			Operation op = static_cast<Operation>(op_int);

			T value = Serialize::string_to_number<T>(args[1]);
			unique_ptr<Condition> ptr = std::make_unique<TypedCondition<T>>( dt,
																args[0],
																value,
																op);
			return ptr;
		}
	private:
		static const string m_class_name;
		//storage for the key value
		T m_key_value;
		//storage for the key nane
		string m_key_name;
		//storage for the comparison value
		T m_compare_to_value;
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
