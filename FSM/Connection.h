#pragma once
#include <vector>
#include "Condition.h"
using std::vector;

namespace FSM
{
	class State;

	class Connection
	{
	public:
		Connection(
			State* source,
			State* destination
			) : m_source(source), m_destination(destination) {};
		~Connection() = default;

		inline bool evaluate()
		{
			bool val = true;
			for (auto c : m_condtitions)
			{
				val = val && c->evaluate();
			}
			return val;
		};

		inline void add_condition(Condition * condition)
		{ m_condtitions.push_back(condition); }

		inline size_t conditions_count()  const
		{ return m_condtitions.size(); }

	private:
		State* m_source;
		State* m_destination;
		vector<Condition*> m_condtitions;
	};
}

