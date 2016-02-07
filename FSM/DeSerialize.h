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
		const regex REG_END_CONNECTION = regex(CONNECTIONS_TAG);
		const regex REG_END_CONDITIONS= regex(CONDITIONS_TAG);
		const regex REG_END_STATES= regex(STATES_TAG);

		string extract_type(string& data);
		ClassArgs extract_args(string& data);
		void read_conditions_from_file(std::ifstream& file, 
										std::vector<string>& data);
		
		void read_connection_from_file(std::ifstream& file, vector<string>& connection_data,
			vector<vector<string>>& condition_data);
	}

}
