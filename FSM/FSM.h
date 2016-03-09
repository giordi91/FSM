#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "State.h"
#include "DataStorage.h"


using std::string;
using std::vector;
using FSM::State;
using FSM::DataStorage;


namespace FSM
{
	class FiniteStateMachine
	{
	public:
		__declspec(dllexport)
		FiniteStateMachine(string name,
			DataStorage* dt) :
			m_name(name),
			m_data(dt),
			m_current(nullptr) {}

		~FiniteStateMachine() = default;

		inline void add_state(State *st)
		{
			if (nullptr == m_current)
			{
				m_current = st;
			}
			m_states.push_back(st);
		}

		inline void update()
		{
			if (m_current != nullptr)
			{
				m_current=m_current->transition();
			}

		}

		inline size_t get_states_count() const
		{
			return m_states.size();
		}

		inline State * get_current_state() const
		{
			return m_current;
		}

		inline string get_current_state_name() const
		{
			if (m_current !=nullptr)
			{
				return m_current->get_name();
			}
			else
			{
				return string("");
			}
		}
		bool set_current_state(string state_name)
		{
			for (auto s : m_states)
			{
				if (s->get_name() == state_name)
				{
					m_current = s;
					return true;
				}
			}
			return false;
		}

		inline State* get_state_at_index(int index)
		{
			return m_states[index];
		}

		__declspec(dllexport)
		const string serialize() const;
	private:
		static const string m_class_name;
		string m_name;
		DataStorage* m_data;
		State * m_current;
		vector<State *> m_states;
	};

}
