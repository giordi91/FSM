#pragma once
#include "Serialize.h"

using std::regex;

namespace FSM
{
	namespace Serialize
	{ 
		const string TYPE_EXTRACTOR = OPEN_TAG + " *([a-zA-Z]+?[<>a-zA-Z>]*) *" +TYPE_SEP ;  
		const regex REG_TYPE_EXTRACTOR = regex(TYPE_EXTRACTOR);

		string extract_type(string& data);
		
		const	
	}

}
