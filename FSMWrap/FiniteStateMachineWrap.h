#pragma once
#include "stdafx.h"
#include "FSM.h"
#include "StateWrap.h"
#include "FSMFactory.h"
#include <string>
#include <iostream>
#include <msclr\marshal_cppstd.h>
using namespace System::Collections::Generic;
using namespace System;


namespace FSMWrapper
{
	public ref class FiniteStateMachineWrap
	{
	private:
		FSM::FiniteStateMachine* _fsm;
		FSM::FSMFactory* _fsmfac;
	public:
		FSM::DataStorage* _data;
	public:
		FiniteStateMachineWrap()
		{
			std::string name("generateFsm");
			//_fsm= new FSM::FiniteStateMachine(name,_data);
			_fsmfac= new FSM::FSMFactory();
			_fsm = _fsmfac->generate_empty(name);
			_data = _fsmfac->get_data_storage();
			//_data->set_value("test", false);
			//_data->set_value("is_it?", true);
			//_data->set_value("float", 1.3453f);
			//_data->set_value("int", 15);
		};

		~FiniteStateMachineWrap()
		{
			delete(_fsmfac);
			_fsmfac= nullptr;
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


		Dictionary<String^, bool>^ get_bool_dict()
		{
			auto map = _data->get_map_bool();
			auto h_result = gcnew Dictionary<String^, bool>((int)map.size());

			for (auto kvp : map)
			{
				String^ name = msclr::interop::marshal_as<String^>(kvp.first);
				h_result->Add(name, kvp.second);
			}
			return h_result;
		}
		
		Dictionary<String^, float>^ get_float_dict()
		{
			auto map = _data->get_map_float();
			auto h_result = gcnew Dictionary<String^, float>((int)map.size());

			for (auto kvp : map)
			{
				String^ name = msclr::interop::marshal_as<String^>(kvp.first);
				h_result->Add(name, kvp.second);
			}
			return h_result;
		}
		
		Dictionary<String^, int>^ get_int_dict()
		{
			auto map = _data->get_map_int();
			auto h_result = gcnew Dictionary<String^, int>((int)map.size());

			for (auto kvp : map)
			{
				String^ name = msclr::interop::marshal_as<String^>(kvp.first);
				h_result->Add(name, kvp.second);
			}
			return h_result;
		}

		bool get_bool_value(String^ key)
		{
				std::string name = msclr::interop::marshal_as<std::string>(key);
				bool value;
				_data->get_value(name, value);
				return value;
		}
		float get_float_value(String^ key)
		{
				std::string name = msclr::interop::marshal_as<std::string>(key);
				float value;
				_data->get_value(name, value);
				return value;
		}
		int get_int_value(String^ key)
		{
				std::string name = msclr::interop::marshal_as<std::string>(key);
				int value;
				_data->get_value(name, value);
				return value;
		}
		
		void set_bool_value(String^ key, bool value)
		{
			std::string name = msclr::interop::marshal_as<std::string>(key);
			_data->set_value(name, value);

		}
		void set_float_value(String^ key, float value)
		{
			std::string name = msclr::interop::marshal_as<std::string>(key);
			_data->set_value(name, value);

		}
		void set_int_value(String^ key, int value)
		{
			std::string name = msclr::interop::marshal_as<std::string>(key);
			_data->set_value(name, value);

		}

		bool set_current_state(String^ state_name)
		{
			std::string name = msclr::interop::marshal_as<std::string>(state_name);
			return _fsm->set_current_state(name);
		}

		void evaluate()
		{
			_fsm->update();
		}

		String^ get_current_state_name()
		{
			String^ name = msclr::interop::marshal_as<String^>(_fsm->get_current_state()->get_name());
			return name;
		}

		void from_file(String^ path)
		{
		
			std::string name = msclr::interop::marshal_as<std::string>(path);
			_fsmfac = new FSM::FSMFactory();
			_fsm = _fsmfac->generate_fsm_from_file(name);
		}


		int get_state_count()
		{
			return (int) _fsm->get_states_count();
		}

		StateWrapper^ get_state_at_index(int index)
		{
			StateWrapper^ state = gcnew StateWrapper();
			state->_state = _fsm->get_state_at_index(index);
			return state;
		}

	};

}
