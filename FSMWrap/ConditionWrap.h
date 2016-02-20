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

		~TypedConditionFloatWrap()
		{
			delete _cond;
			_cond = nullptr;
		}
	};
		
}
