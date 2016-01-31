#include "DeSerialize.h"

namespace FSM
{
	namespace Serialize
	{
		
		string extract_type(string& data)
		{
			std::smatch type_match;
			std::regex_search(data, type_match, REG_TYPE_EXTRACTOR);
			if (type_match.size() != 2)
			{
				return string();
			}
			else
			{
				return type_match[1];
			}
		}

		ClassArgs extract_args(string & data)
		{
			
			//first pass in extracting args only full string
			std::smatch type_match;
			std::regex_search(data, type_match, REG_ARGS_EXTRACTOR);
			
			//second pass we find all the matches for single argumenets
			std::smatch type_match2;
			string data2 = type_match[1];
			auto it = std::sregex_iterator(data2.begin(), data2.end(), REG_SINGLE_ARG_EXTRACTOR);
			auto end = std::sregex_iterator();

			ClassArgs args;
			while (it != end)
			{
				args.push_back(it->str());
				++it;
			}

			return args;
		}
	}
}