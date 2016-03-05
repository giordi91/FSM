#pragma once
#include "stdafx.h"
#include "FSM.h"
#include "StateWrap.h"
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
	public:
		FSM::DataStorage* _data;
	public:
		FiniteStateMachineWrap()
		{
			_data = new FSM::DataStorage();
			_data->set_value("test", false);
			_data->set_value("is_it?", true);
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


		Dictionary<String^, bool>^ get_bool_dict()
		{
			auto map = _data->get_map_bool();
			auto h_result = gcnew Dictionary<String^, bool>(map.size());

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
			auto h_result = gcnew Dictionary<String^, float>(map.size());

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
			auto h_result = gcnew Dictionary<String^, int>(map.size());

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

		
	};

}
