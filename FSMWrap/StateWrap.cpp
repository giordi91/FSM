#include "stdafx.h"
#include "StateWrap.h"
#include "ConnectionWrap.h"

namespace FSMWrapper
{

		void StateWrapper::add_connection(ConnectionWrap^ conn)
		{
			_state->add_connection(conn->_conn);
		}

		ConnectionWrap^ StateWrapper::get_connection_at_index(int index)
		{
			auto conn = _state->get_connection_at_index(index);
			ConnectionWrap^ connWrap = gcnew ConnectionWrap();
			connWrap->_conn = conn;
			return connWrap;
		}
}