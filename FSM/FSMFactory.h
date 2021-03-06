#pragma once
#include <unordered_map>
#include <vector>
#include <memory>
#include <stack>
#include "Condition.h"
#include "Connection.h"
#include "DeSerialize.h"
#include "DataStorage.h"
#include "FSM.h"

using FSM::Condition;
using std::unordered_map;
using std::unique_ptr;
using std::string;
using std::stack;


namespace FSM
{
		//typedef for a constructor condition function
		typedef unique_ptr<Condition>(*ConditionFunction)(DataStorage*, ClassArgs&); 
		//typedef for a map of condition function
		typedef std::unordered_map < string, ConditionFunction> ConditionsMap;
		
		static const  ConditionsMap condition_map{
			{"DoubleVarCondition<bool>", DoubleVarCondition<bool>::de_serialize},
			{"DoubleVarCondition<int>", DoubleVarCondition<int>::de_serialize},
			{"DoubleVarCondition<float>", DoubleVarCondition<float>::de_serialize},
			{"TypedCondition<bool>" , TypedCondition<bool>::de_serialize},
			{"TypedCondition<int>"  , TypedCondition<int>::de_serialize},
			{"TypedCondition<float>", TypedCondition<float>::de_serialize}
		};
	class FSMFactory
	{
	public:
		__declspec(dllexport)
		FSMFactory();
		__declspec(dllexport)
		~FSMFactory();
		
		inline DataStorage * get_data_storage()
		{
			return &m_dt;
		}

		inline State * get_state(string name) 
		{
			auto res = m_states.find(name);
			if (res != m_states.end())
			{
				return res->second.get();
			}
			else
			{
				//we create the state and push it
				auto myState= std::make_unique<GenericState>(name);
				State * p = myState.get();
				m_states[name] = std::move(myState);
				return p;
			}
		}

		Condition* generate_condtition(string data);
		//data = fist the connection , all the other rows a conditions
		Connection* generate_connection(vector<string>& data);
		State *  generate_state(string& state_data, 
								vector<vector<string>>& conn_data);

		__declspec(dllexport)
		FiniteStateMachine * generate_fsm_from_file(string path);
		__declspec(dllexport)
		FiniteStateMachine * generate_empty(string name)
		{
			auto finite_state = std::make_unique<FiniteStateMachine>(name, &m_dt);
			auto ptr = finite_state.get();
			m_machines[name] = std::move(finite_state);
			return ptr;
		};
	private:
		DataStorage m_dt;
		stack<unique_ptr<Condition>> m_conditions;
		stack<unique_ptr<Connection>> m_connections;
		unordered_map<string, unique_ptr<State>> m_states;
		
		unordered_map<string, unique_ptr<FiniteStateMachine>> m_machines;
	};

}

