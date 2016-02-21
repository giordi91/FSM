#include "stdafx.h"
#include "StateWrap.h"
#include "ConnectionWrap.h"

namespace FSMWrapper
{

		void StateWrapper::add_connection(ConnectionWrap^ conn)
		{
			_state->add_connection(conn->_conn);
		}

}