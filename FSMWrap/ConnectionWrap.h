#pragma once
#include "stdafx.h"
#include "Connection.h"
#include "State.h"
#include <string>
#include <iostream>
#include <msclr\marshal_cppstd.h>
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
		/*
		String^ get_name()
		{
			return msclr::interop::marshal_as<String^>(_state->get_name());
		}

		void set_name(String^ name)
		{
			_state->set_name(msclr::interop::marshal_as<std::string>(name));
		}
		*/

	};

}
