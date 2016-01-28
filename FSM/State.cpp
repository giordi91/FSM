#include "State.h"
#include "Connection.h"

namespace FSM
{
	const string GenericState::m_class_name = "GenericState";
	State * GenericState::transition() 
	{
		for (auto con : m_connections)
		{
			if (con->evaluate())
			{
				return con->get_destination();
			}
		}
		return this;
	};
	
	const string GenericState::serialize() const
	{
			string s = (FSM::Serialize::OPEN_TAG + m_class_name );
			s += FSM::Serialize::TYPE_SEP ;
			s += m_name;
			s += FSM::Serialize::CLOSE_TAG;
			s += "\n";
			for(auto conn: m_connections)
			{
				s += conn->serialize();
				s += "\n";
			}
			s += Serialize::CONNECTIONS_TAG;
			return s;
	
	
	}

}