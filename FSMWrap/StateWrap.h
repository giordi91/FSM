#pragma once
#include "stdafx.h"
#include "State.h"
#include <string>
#include <iostream>
#include <msclr\marshal_cppstd.h>
//#include "ConnectionWrap.h"
using namespace System;


namespace FSMWrapper
{
	ref class ConnectionWrap;
	public ref class StateWrapper
	{
	public:
		FSM::State * _state;
	public:
		StateWrapper()
		{
			_state = new FSM::GenericState("Fuffa");
		};

		~StateWrapper()
		{
			delete _state;
			_state = nullptr;
		}

		String^ get_name()
		{
			return msclr::interop::marshal_as<String^>(_state->get_name());
		}

		void set_name(String^ name)
		{
			_state->set_name(msclr::interop::marshal_as<std::string>(name));
		}

		void add_connection(ConnectionWrap^ conn);

	};

}
