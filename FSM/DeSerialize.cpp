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
		};

	}
}