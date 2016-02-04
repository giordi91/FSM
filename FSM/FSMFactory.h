#pragma once
#include <unordered_map>
#include <vector>
#include <memory>
#include <stack>
#include "Condition.h"
#include "DeSerialize.h"
#include "DataStorage.h"

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
		FSMFactory();
		~FSMFactory();
		
		inline DataStorage * get_data_storage()
		{
			return &m_dt;
		}
		Condition* generate_condtition(string data);

	private:
		DataStorage m_dt;
		stack<unique_ptr<Condition>> m_conditions;


	};

}

