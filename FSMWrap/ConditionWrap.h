#pragma once
#include "Condition.h"
#include "FiniteStateMachineWrap.h"
#include "State.h"
#include <string>
#include <iostream>

#include <msclr\marshal_cppstd.h>
using namespace System;


namespace FSMWrapper
{
	//Generic interface
	generic<typename T> 
	public interface class ITypedCondition
	{
	public:
		T   get_compare_value();
		void set_compare_value(T value);
		bool evaluate();
		T get_value();
		String^ get_key_name();
		void  set_key_name(String^ key);
		int get_operation();
		void set_operation(int op);
	};

	//specific type
	template<typename T> 
	public ref class TypedConditionWrap : ITypedCondition<T>
	{
	public:
		FSM::TypedCondition<T>* _cond;
	public:

		TypedConditionWrap(FiniteStateMachineWrap^ finiteM,
			String^ key_name,
			T compare_value,
			int op)
		{

			std::string key_n = msclr::interop::marshal_as<std::string>(key_name);
			_cond = new FSM::TypedCondition<T>(finiteM->_data,
				key_n,
				compare_value,
				FSM::Operation::LESSEQUAL
				);
		}

		TypedConditionWrap()
		{}
		
		virtual T get_compare_value()
		{
			return _cond->get_compare_value();
		}

		virtual bool evaluate()
		{
			return _cond->evaluate();
		}

		virtual T get_value()
		{
			return _cond->get_value();
		}

		virtual String^ get_key_name()
		{
			String^ name = msclr::interop::marshal_as<String^>(_cond->get_key_name());
			return name;
		}

		virtual void  set_key_name(String^ key)
		{
			std::string name = msclr::interop::marshal_as<std::string>(key);
			_cond->set_key_name(name);

		}
		virtual int get_operation() 
		{
			return (int)_cond->get_operation();
		}
		
		virtual void set_operation(int op)
		{
			FSM::Operation convert_op = (FSM::Operation)op;
			_cond->set_operation(convert_op);
		}

			
		virtual void set_compare_value(T value)
		{
			_cond->set_compare_value(value);
		}
	
	};

	//factory class
	generic<typename T>
	public ref class ConditionFactory 
	{
	public:
		generic<typename T> static ITypedCondition<T>^ Create(FiniteStateMachineWrap^ finiteM,
			String^ key_name,
			float compare_value,
			int op)
		{
			if (T::typeid == float::typeid)
			{
				return (ITypedCondition<T>^)
					gcnew TypedConditionWrap<float>(finiteM, key_name, (float)compare_value, op);
			}
			else if (T::typeid == int::typeid)
			{
				return (ITypedCondition<T>^)
					gcnew TypedConditionWrap<int>(finiteM, key_name, (int)compare_value, op);
			}
			else if (T::typeid == bool::typeid)
			{
				return (ITypedCondition<T>^)
					gcnew TypedConditionWrap<bool>(finiteM, key_name, compare_value != 0, op);
			}
			else
			{ 
				return nullptr;
			}
		}
	};
		
	//Generic interface
	generic<typename T> 
	public interface class IDoubleCondition
	{
	public:
		bool evaluate();
		T get_value_1();
		T get_value_2();
		String^ get_key_name_1();
		String^ get_key_name_2();
		void  set_key_name_1(String^ key);
		void  set_key_name_2(String^ key);
		int get_operation();
		void set_operation(int op);
	};

	//specific type
	template<typename T> 
	public ref class DoubleConditionWrap: IDoubleCondition<T>
	{
	public:
		FSM::DoubleVarCondition<T>* _cond;
	public:
		
		DoubleConditionWrap(FiniteStateMachineWrap^ finiteM,
			String^ key_name_1,
			String^ key_name_2,
			int op)
		{
			
			std::string key_n_1 = msclr::interop::marshal_as<std::string>(key_name_1);
			std::string key_n_2 = msclr::interop::marshal_as<std::string>(key_name_2);
			_cond = new FSM::DoubleVarCondition<T>(finiteM->_data,
				key_n_1,
				key_n_2,
				FSM::Operation::LESSEQUAL
				);
		}

		DoubleConditionWrap()
		{}

		
		virtual bool evaluate()
		{
			return _cond->evaluate();
		}

		virtual T get_value_1()
		{
			return _cond->get_value_1();
		}
		virtual T get_value_2()
		{
			return _cond->get_value_2();
		}

		virtual String^ get_key_name_1()
		{
			String^ name = msclr::interop::marshal_as<String^>(_cond->get_key_name_1());
			return name;
		}
		virtual String^ get_key_name_2()
		{
			String^ name = msclr::interop::marshal_as<String^>(_cond->get_key_name_2());
			return name;
		}

		virtual void  set_key_name_1(String^ key)
		{
			std::string name = msclr::interop::marshal_as<std::string>(key);
			_cond->set_key_name_1(name);
		}
		virtual void  set_key_name_2(String^ key)
		{
			std::string name = msclr::interop::marshal_as<std::string>(key);
			_cond->set_key_name_2(name);
		}

		virtual int get_operation() 
		{
			return (int)_cond->get_operation();
		}
		
		virtual void set_operation(int op)
		{
			FSM::Operation convert_op = (FSM::Operation)op;
			_cond->set_operation(convert_op);
		}
	
	};

	//factory class
	generic<typename T>
	public ref class DoubleConditionFactory 
	{
	public:
		generic<typename T> static IDoubleCondition<T>^ Create(FiniteStateMachineWrap^ finiteM,
			String^ key_name_1,
			String^ key_name_2,
			int op)
		{
			if (T::typeid == float::typeid)
			{
				return (IDoubleCondition<T>^)
					gcnew DoubleConditionWrap<float>(finiteM, key_name_1, key_name_2, op);
			}
			else if (T::typeid == int::typeid)
			{
				return (IDoubleCondition<T>^)
					gcnew DoubleConditionWrap<int>(finiteM, key_name_1, key_name_2, op);
			}
			else if (T::typeid == bool::typeid)
			{
				return (IDoubleCondition<T>^)
					gcnew DoubleConditionWrap<bool>(finiteM, key_name_1, key_name_2, op);
			}
			else
			{ 
				return nullptr;
			}
		}
	};
}
