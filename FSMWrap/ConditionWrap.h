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
	public:
		TypedConditionFloatWrap(FiniteStateMachineWrap^ finiteM,
								String^ key_name,
								float compare_value,
								int op)
		{

			std::string key_n = msclr::interop::marshal_as<std::string>(key_name);
			_cond = new FSM::TypedCondition<float>(finiteM->_data,
													key_n,
													compare_value,
													FSM::Operation::EQUAL
													);
		};

		bool evaluate()
		{
			return _cond->evaluate();
		}

		~TypedConditionFloatWrap()
		{
			delete _cond;
			_cond = nullptr;
		}
	};
		
}
