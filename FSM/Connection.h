#pragma once
#include <vector>

using std::vector;

namespace FSM
{
	class State;
	class Condition;
	class Connection
	{
	public:
		Connection(
			State* source,
			State* destination
			) : m_source(source), m_destination(destination) {};
		~Connection() = default;

	private:
		State* m_source;
		State* m_destination;
		vector<Condition*> m_condtitions;
	};
}

