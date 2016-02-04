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
		const string ARGS_EXTRACTOR = TYPE_SEP + " *([a-zA-Z0-9 ,\\.]+) *" +CLOSE_TAG;  
		const string SINGLE_ARG_EXTRACTOR = "([a-zA-Z0-9\\.]+)";  
		const regex REG_TYPE_EXTRACTOR = regex(TYPE_EXTRACTOR);
		const regex REG_ARGS_EXTRACTOR = regex(ARGS_EXTRACTOR);
		const regex REG_SINGLE_ARG_EXTRACTOR = regex(SINGLE_ARG_EXTRACTOR);
		



		string extract_type(string& data);
		ClassArgs extract_args(string& data);
	}

}
