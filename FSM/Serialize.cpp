#include "Serialize.h"
using std::regex;

namespace FSM
{
	namespace Serialize

	{
		void decode_condition() 
		{

			string regex_str = "<< *([a-zA-Z]+?[<>a-zA-Z>]*) *### *([a-zA-z0-9]+) *, *([a-zA-z0-9]+) *, *([a-zA-Z]+) *>>";
			
			
			/*			
			string temp = "<< TypedCondition<bool> ### ducking , 1 , equal >>";
			regex reg1(regex_str);
			std::smatch cm;    // same as std::match_results<const char*> cm;
			std::smatch cm2;
			std::regex_search(temp, cm2, REG_TYPE_EXTRACTOR);
			std::cout << cm2[1] << std::endl;
			/*
			bool found = std::regex_search(temp, cm, reg1);
			std::cout << found << std::endl;
			std::cout << cm.size()<< std::endl;
			std::cout << "regex result -------------#########################" << std::endl;
			for (int i = 0; i < cm.size(); i++)
			{
				std::cout << cm[i] << std::endl;
			}
			*/
		}

	}


}