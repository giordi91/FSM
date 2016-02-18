
// ConsoleApplication2.cpp : main project file.

#include "stdafx.h"
#include "State.h"
#include <string>
#include <iostream>
#include <msclr\marshal_cppstd.h>
using namespace System;


namespace FSMWrapper
{
	public ref class StateWrapper
	{
	private:
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
			//_state->set_name(msclr::interop::marshal_as<std::string>(name));
		}
		int getInt()
		{
			return 10;
		}

	};

}
