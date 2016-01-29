#include "FSM.h"
#include "Serialize.h"
namespace FSM
{
	const string FiniteStateMachine::m_class_name="FiniteStateMachine";
	const string FiniteStateMachine::serialize() const
	{
			string s = (FSM::Serialize::OPEN_TAG + m_class_name );
			s += FSM::Serialize::TYPE_SEP ;
			s += m_name;
			s += FSM::Serialize::CLOSE_TAG;
			s += "\n";
			for(auto state: m_states)
			{
				s += state->serialize();
				s += "\n";
			}
			s += Serialize::STATES_TAG;
			return s;
	}
}