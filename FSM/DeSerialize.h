#pragma once
#include "Serialize.h"
#include <unordered_map>
#include <string>
#include "Condition.h"
using std::regex;

namespace FSM
{
	namespace Serialize
	{ 
		const string TYPE_EXTRACTOR = OPEN_TAG + " *([a-zA-Z]+?[<>a-zA-Z>]*) *" +TYPE_SEP ;  
		const regex REG_TYPE_EXTRACTOR = regex(TYPE_EXTRACTOR);
		

		//typedef for a constructor condition function
		typedef unique_ptr<Condition>(*ConditionFunction)(DataStorage*, ClassArgs&); 
		//typedef for a map of condition function
		typedef std::unordered_map < string, ConditionFunction> ConditionsMap;
		static const  ConditionsMap condition_map{
			{"DoubleVarCondition<bool>", DoubleVarCondition<bool>::de_serialize},
			{"DoubleVarCondition<bool>", DoubleVarCondition<int>::de_serialize},
			{"DoubleVarCondition<bool>", DoubleVarCondition<float>::de_serialize}
		};



		string extract_type(string& data);
		
	}

}
