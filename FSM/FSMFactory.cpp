#include "FSMFactory.h"

namespace FSM
{
	FSMFactory::FSMFactory()
	{
	}


	FSMFactory::~FSMFactory()
	{
	}

	Condition * FSMFactory::generate_condtition(string data)
	{
		string type = FSM::Serialize::extract_type(data);
		//auto fun_obj = FSM::Serialize::ConditionsMap.;
		auto fun_it = FSM::Serialize::condition_map.find(type);
		if (fun_it != FSM::Serialize::condition_map.end())
		{
			//fun_it->second()
			string args_string;

		}
		else
		{
			return nullptr;

		}
	}

}