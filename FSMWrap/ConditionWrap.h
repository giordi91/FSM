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
	//template<typename T>
	/*
	public ref class TypedConditionFloatWrap
	{
	public:
		FSM::TypedCondition<float>* _cond;
		TypedConditionFloatWrap(FiniteStateMachineWrap^ finiteM,
			String^ key_name,
			float compare_value,
			int op)
		{

			std::string key_n = msclr::interop::marshal_as<std::string>(key_name);
			_cond = new FSM::TypedCondition<float>(finiteM->_data,
				key_n,
				compare_value,
				FSM::Operation::LESSEQUAL
				);
		};

		bool evaluate()
		{
			return _cond->evaluate();
		}

		float get_value()
		{
			return _cond->get_value();
		}

		String^ get_key_name()
		{
			String^ name = msclr::interop::marshal_as<String^>(_cond->get_key_name());
			return name;
		}

		void  set_key_name(String^ key)
		{
			std::string name = msclr::interop::marshal_as<std::string>(key);
			_cond->set_key_name(name);

		}
	public:
		int get_operation()
		{
			return (int)_cond->get_operation();
		}
		
		void set_operation(int op)
		{
			FSM::Operation convert_op = (FSM::Operation)op;
			_cond->set_operation(convert_op);
		}

		float get_compare_value()
		{
			return _cond->get_compare_value();
		}
			
		void set_compare_value(float value)
		{
			_cond->set_compare_value(value);
		}
	
		~TypedConditionFloatWrap()
		{
			delete _cond;
			_cond = nullptr;
		}
	};
	*/
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
	public ref class TypedConditionWrap: ITypedCondition<T>
	{
	public:
		FSM::TypedCondition<T>* _cond;
	public:
		
		TypedConditionWrap(FiniteStateMachineWrap^ finiteM,
			String^ key_name,
			float compare_value,
			int op)
		{
			
			std::string key_n = msclr::interop::marshal_as<std::string>(key_name);
			_cond = new FSM::TypedCondition<float>(finiteM->_data,
				key_n,
				compare_value,
				FSM::Operation::LESSEQUAL
				);
		}
		
		virtual T get_compare_value()
		{
			return _cond->get_compare_value();
		}

		virtual bool evaluate()
		{
			return _cond->evaluate();
		}

		virtual float get_value()
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
					gcnew TypedConditionWrap<float>(finiteM, key_name, compare_value, op);
			}
			else
			{
				return nullptr;
			}
		}
	};
		
}
