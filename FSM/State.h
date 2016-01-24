#pragma once
#include <vector>
#include "Connection.h"
using std::vector;
using std::string;

namespace FSM
{

	class State
	{
	public:
		/**
		@bief constructor
		@param name: string represeting the name
		*/
		State(string& name) :m_name(name) {}
		/**
		@bief constructor
		@param name: string represeting the name
		*/
		State(string name) :m_name(name) {}

		/**
		@brief adds a connection to the state
		@param conn: pointer to the connection we wish to add
		*/
		inline void add_connection(Connection * conn)
		{
			m_connections.push_back(conn);
		};
		~State() = default;

		/**
		@brief evaluates wheter there is need for a transition
		This function is going to evaluate all the connecitions and
		if one evaluate to true will return that a pointer to the next
		state. The order in which connections are added gives precedence.
		@returns : returns a pointer to the next state, if none of the
		connections evaluate to true will return a pointer to itself
		*/
		inline State * transition()
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

		/**
		@brief Getter method for the state name
		@returns a const ref to the name
		*/
		inline const string& get_name()const
		{
			return m_name;
		}

	private:
		//storagfe for the connection pointers
		vector<Connection*> m_connections;
		//the state name
		string m_name;
	};

}

