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
		ClassArgs args = FSM::Serialize::extract_args(data);
		
		auto fun_it = FSM::condition_map.find(type);
		if (fun_it != FSM::condition_map.end())
		{
			auto cond = fun_it->second(&m_dt, args);
			m_conditions.push(std::move(cond));
			auto ptr = m_conditions.top().get();
			return ptr;
		}
		else
		{
			return nullptr;

		}
	}

}