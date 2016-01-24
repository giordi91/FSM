#pragma once
#include <vector>
#include "Condition.h"
using std::vector;

namespace FSM
{
	class State;

	/**
	@brief class that represent a connection between two states 
	This calss will be associated with a state, a source, and 
	it will have a destination, the source right now might be useless
	but might be usefull for other user if they want to extend the behavior.
	connection are one way, source->destination
	*/
	class Connection
	{
	public:
		/**
		@brief constructor
		@param source: pointer to the source state
		@param destination: pointer to the destination state
		*/
		Connection(
			State* source,
			State* destination
			) : m_source(source), m_destination(destination) {};
		~Connection() = default;

		/**
		@brief evaluate the condition and wether should transition
		@returns bool, wether the combined result of the condition is
					   true or false, if no condition are present
					   returns true
		*/
		inline bool evaluate()
		{
			bool val = true;
			for (auto c : m_condtitions)
			{
				val = val && c->evaluate();
			}
			return val;
		};
		/**
		@brief add a condition to the connection
		@param condition: pointer to the condition to add
		*/
		inline void add_condition(Condition * condition)
		{
			m_condtitions.push_back(condition);
		}

		/**
		@brief returns number of condition in the connection
		This returns the number of condtion that have been added to the c
		connection, it is mainly for debug purpose
		*/
		inline size_t conditions_count()  const
		{
			return m_condtitions.size();
		}
		/**
		@brief getter function for destination state
		@returns: the destination state pointer
		*/
		inline State * get_destination() const
		{
			return m_destination;
		}

		/**
		@brief getter function for source state
		@returns: the source state pointer
		*/
		inline State * get_source() const
		{
			return m_source;
		}
	private:
		//internal storage for the pointers
		State* m_source;
		State* m_destination;
		//vector of pointers for the conditions
		vector<Condition*> m_condtitions;
	};
}

