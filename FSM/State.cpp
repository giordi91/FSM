#include "State.h"
#include "Connection.h"

namespace FSM
{
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
		return string();
	
	
	}

}