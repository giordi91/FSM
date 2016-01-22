#pragma once
#include <vector>
using std::vector;
namespace FSM
{
	class Condition;

	class State
	{
	public:
		State()=default;
		~State() = default;
	
	private:
		vector<Condition*> condtitions;
	};

}

