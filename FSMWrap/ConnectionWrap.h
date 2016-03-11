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

		ConnectionWrap() {
			_conn = nullptr;
		}

		ConnectionWrap(StateWrapper^ source, StateWrapper^ destination)
		{
			_conn= new FSM::Connection(source->_state, destination->_state);
		}

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
			else if (T::typeid == int::typeid)
			{
				auto cond_cast = (TypedConditionWrap<int>^)cond;
				_conn->add_condition(cond_cast->_cond);
			}
			else if (T::typeid == bool::typeid)
			{
				auto cond_cast = (TypedConditionWrap<bool>^)cond;
				_conn->add_condition(cond_cast->_cond);
			}
		}
		generic<typename T>
		void add_conditions(IDoubleCondition<T>^ cond)
		{
			if (T::typeid == float::typeid)
			{
				auto cond_cast = (DoubleConditionWrap<float>^)cond;
				_conn->add_condition(cond_cast->_cond);
			}
			else if (T::typeid == int::typeid)
			{
				auto cond_cast = (DoubleConditionWrap<int>^)cond;
				_conn->add_condition(cond_cast->_cond);
			}
			else if (T::typeid == bool::typeid)
			{
				auto cond_cast = (DoubleConditionWrap<bool>^)cond;
				_conn->add_condition(cond_cast->_cond);
			}
		}

		String^ get_source_name()
		{
			auto n = _conn->get_source()->get_name();
			String^ name = msclr::interop::marshal_as<String^>(n);
			return name;

		}
		
		String^ get_destination_name()
		{
			auto n = _conn->get_destination()->get_name();
			String^ name = msclr::interop::marshal_as<String^>(n);
			return name;

		}

		int get_condition_count()
		{
			return (int)_conn->conditions_count();

		}
		String^ get_condition_type_at_index(int index)
		{
			string type = _conn->get_condition_by_index(index)->get_class_name();
			String^ name = msclr::interop::marshal_as<String^>(type);
			return name;
		}

		int get_condition_template_type_at_index(int index)
		{
			return _conn->get_condition_by_index(index)->get_template_type();
		}

		generic<typename T>
		ITypedCondition<T>^ get_Typed_at_index(int index )
		{
			Condition* cond= _conn->get_condition_by_index(index);
			int type = cond->get_template_type();
			if (type == 0)
			{
				auto cond_t = gcnew TypedConditionWrap<int>();
				cond_t->_cond = reinterpret_cast<FSM::TypedCondition<int>*>(cond);
				return (ITypedCondition<T>^)cond_t;
			}
			else if (type == 1)
			{
				auto cond_t = gcnew TypedConditionWrap<float>();
				cond_t->_cond = reinterpret_cast<FSM::TypedCondition<float>*>(cond);
				return (ITypedCondition<T>^)cond_t;
			}
			else 
			{
				auto cond_t = gcnew TypedConditionWrap<bool>();
				cond_t->_cond = reinterpret_cast<FSM::TypedCondition<bool>*>(cond);
				return (ITypedCondition<T>^)cond_t;
			}

		}

		generic<typename T>
		IDoubleCondition<T>^ get_Double_at_index(int index )
		{
			Condition* cond= _conn->get_condition_by_index(index);
			int type = cond->get_template_type();
			if (type == 0)
			{
				auto cond_t = gcnew DoubleConditionWrap<int>();
				cond_t->_cond = reinterpret_cast<FSM::DoubleVarCondition<int>*>(cond);
				return (IDoubleCondition<T>^)cond_t;
			}
			else if (type == 1)
			{
				auto cond_t = gcnew DoubleConditionWrap<float>();
				cond_t->_cond = reinterpret_cast<FSM::DoubleVarCondition<float>*>(cond);
				return (IDoubleCondition<T>^)cond_t;
			}
			else 
			{
				auto cond_t = gcnew DoubleConditionWrap<bool>();
				cond_t->_cond = reinterpret_cast<FSM::DoubleVarCondition<bool>*>(cond);
				return (IDoubleCondition<T>^)cond_t;
			}
		}
	};

}
