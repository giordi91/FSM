#include "Connection.h"
		
namespace FSM
{
	const string Connection::m_class_name("Connection");

	const string Connection::serialize() const
	{
			string s = (FSM::Serialize::OPEN_TAG + m_class_name );
			s += FSM::Serialize::TYPE_SEP ;
			s += m_source->get_name();
			s += Serialize::ARGS_SEP;
			s += m_destination->get_name();
			s += FSM::Serialize::CLOSE_TAG;
			s += "\n";
			for (auto cond : m_condtitions)
			{
				s += cond->serialize();
				s += "\n";
			}
			s += Serialize::CONDITIONS_TAG;
			return s;
	}
}