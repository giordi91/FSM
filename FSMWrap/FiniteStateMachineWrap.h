#pragma once
#include "stdafx.h"
#include "FSM.h"
#include "StateWrap.h"
#include <string>
#include <iostream>
#include <msclr\marshal_cppstd.h>
using namespace System;


namespace FSMWrapper
{
	public ref class FiniteStateMachineWrap
	{
	private:
		FSM::FiniteStateMachine* _fsm;
	public:
		FSM::DataStorage* _data;
	public:
		FiniteStateMachineWrap()
		{
			_data = new FSM::DataStorage();
			std::string name("generateFsm");
			_fsm= new FSM::FiniteStateMachine(name,_data);
		};

		~FiniteStateMachineWrap()
		{
			delete _data;
			delete _fsm;
			_fsm= nullptr;
			_data = nullptr;
		}

		void add_state(StateWrapper^ state)
		{
			_fsm->add_state(state->_state);
		}

		String^ serialize()
		{
			std::string data = _fsm->serialize();
			return msclr::interop::marshal_as<String^>(data);
		}


	};

}
