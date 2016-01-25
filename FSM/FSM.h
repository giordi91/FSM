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

	private:
		string m_name;
		DataStorage* m_data;
		State * m_current;
		vector<State *> m_states;
	};

}
