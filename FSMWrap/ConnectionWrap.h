#pragma once
#include "stdafx.h"
#include "Connection.h"
#include <string>
#include <iostream>
#include <msclr\marshal_cppstd.h>
#include "ConditionWrap.h"
using namespace System;


namespace FSMWrapper
{
	
	public ref class ConnectionWrap 
	{
	public:
		FSM::Connection* _conn;
	public:
		ConnectionWrap(StateWrapper^ source, StateWrapper^ destination)
		{
			_conn= new FSM::Connection(source->_state, destination->_state);
		};

		~ConnectionWrap()
		{
			delete _conn;
			_conn= nullptr;
		}

		generic<typename T>
		void add_conditions(ITypedCondition<T>^ cond)
		{
			if (T::typeid == float::typeid)
			{
				auto cond_cast = (TypedConditionWrap<float>^)cond;
				_conn->add_condition(cond_cast->_cond);
			}
		}

	};

}
